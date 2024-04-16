#include "stdafx.h"

#include "MainState.hpp"
#include "CameraRenderComponent.hpp"
#include "ColliderComponent.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "TileMapLoader.hpp"
#include "Tileson.hpp"
#include "TransformAnimationComponent.hpp"
#include "TransformAnimationSmoothFollow.hpp"
#include "ObjectFactory.hpp"
#include "ObeliskHealthComponent.hpp" 
#include "CountEvent.hpp"
#include "GameStateManager.hpp"
#include "HealthComponent.hpp"

#include <memory> 
#include <thread>

namespace mmt_gd
{
MainState::MainState(GameStateManager* gameStateManager, Game* game) :
GameState(gameStateManager, game),
m_spriteManager(game->getWindow()),
m_elapsedTime(0.0f),
yourScore(0)

{
    
}

void MainState::init()
{
    PROFILE_FUNCTION();

    m_startTime = std::chrono::high_resolution_clock::now();

    m_gameObjectManager.init();
    m_spriteManager.init();
    m_physicsManager.init();

    EventBus::getInstance().addListener(CountEvent::type, [this](const IEvent::Ptr& event)
                                        {
                                            auto countEvent = std::static_pointer_cast<CountEvent>(event);
                                            countEvent->getData();
                                            m_enemydead++;
                                            std::cout << "Enemy dead counter LOL" << std::endl;
                                            std::cout << "Enemiekillcount:" << m_enemydead << std::endl;
                                            if (m_enemydead == 13)
                                            {
                                                m_gameStateManager->setState("EndState");
                                                
                                            }
                                        });
    

  
    

    
    
   

    m_view = m_game->getWindow().getView();

    m_isInit = true;


    // load tile map/level
    {
        PROFILE_SCOPE("Load Tile Map");
        const auto resourcePath = fs::path{"../"} / "assets";
        const auto mapPath      = resourcePath / "game.tmj";

        tson::Tileson t;
        if (const std::unique_ptr<tson::Map> map = t.parse(mapPath); map->getStatus() == tson::ParseStatus::OK)
        {
            TileMapLoader::loadTileLayers(map, resourcePath, m_spriteManager);
            TileMapLoader::loadObjectLayers(map, resourcePath, m_spriteManager);
        }
        else
        {
            std::cerr << "Error loading " << mapPath << std::endl;
        }
    }

    const auto player = m_gameObjectManager.getGameObject("Player0");

    // Moving camera
    {
        const auto camera = GameObject::create("Camera");

        const auto renderComp = camera->addComponent<CameraRenderComponent>(*camera,
                                                                            m_game->getWindow(),
                                                                            m_game->getWindow().getView());

        camera->addComponent<TransformAnimationComponent>(*camera,
                                                          std::make_shared<mmt::TransformAnimationSmoothFollow>(player, 10.F));


        if (!camera->init())
            ffErrorMsg("Could not initialize camera");

        m_gameObjectManager.addGameObject(camera);
        m_spriteManager.setCamera(renderComp.get());
    }
    // Trigger
    const auto trigger = m_gameObjectManager.getGameObject("Trigger");
    obeliskHealth = trigger->addComponent<ObeliskHealthComponent>(*trigger, 100);

    if (trigger)
    {
        if (auto triggerComponent = trigger->getComponent<ColliderComponent>())
        {
            triggerComponent->registerOnCollisionFunction(
                [this, trigger](ColliderComponent& a, ColliderComponent& b)
                {
                    std::cout << " Trigger: " << a.getGameObject().getId() << " | GO: " << b.getGameObject().getId()
                              << std::endl;


                    if (obeliskHealth)
                    {
                            if (a.getGameObject().getId() == "Player0" || b.getGameObject().getId() == "Player0" ||
                                     a.getGameObject().getId() == "Bullet_0" ||
                                     b.getGameObject().getId() == "Bullet_0" ||
                                     a.getGameObject().getId() == "Bullet_1" ||
                                     b.getGameObject().getId() == "Bullet_1" ||
                                     a.getGameObject().getId() == "Bullet_2" ||
                                     b.getGameObject().getId() == "Bullet_2" ||
                                     a.getGameObject().getId() == "Bullet_3" ||
                                     b.getGameObject().getId() == "Bullet_3" ||
                                     a.getGameObject().getId() == "Bullet_4" || b.getGameObject().getId() == "Bullet_4")
                            {
                                std::cout << "player hit obelisk" << std::endl;
                            }
                            else
                            {
                                obeliskHealth->reduceHealthOfObelisk();
								std::cout << "enemy hit obelisk" << std::endl;
                                if (obeliskHealth->getHealthOfObelisk() <= 0)
                                {
                                    m_gameStateManager->setState("LoseState");
                                    std::cout << "Obelisk destroyed!" << std::endl;
                                } 
                            }
                    }
                });
        }
    }
    // Define layer order manually here. Could come from custom file settings.
    m_spriteManager.setLayerOrder({"Floor", "Background", "Objects", "GameObjects", "Top"});

    

    if (!m_music.openFromFile("../assets/musicfox_loop_line.wav"))
    {
		std::cerr << "Could not load music file" << std::endl;
	}
    else
    {
		m_music.setLoop(true);
		m_music.play();
	}

}

void MainState::update(const float deltaTime)
{
    PROFILE_FUNCTION();
    if (InputManager::getInstance().isKeyPressed("Exit"))
    {
        m_gameStateManager->setState("EndState");
        return;
    }

    if (auto playerGameObject = m_gameObjectManager.getGameObject("Player0"))
    {
        auto playerHealthComponent = playerGameObject->getComponent<HealthComponent>();
        if (playerHealthComponent)
        {
            // Aufruf der update-Methode
            playerHealthComponent->update(deltaTime);

            // Überprüfen, ob die Gesundheit des Spielers 0 oder weniger ist
            if (playerHealthComponent->getHealth() <= 0)
            {
                // Zustand des Spiels auf den Endzustand ändern
                m_gameStateManager->setState("LoseState");
            }
        }
    }
    /*const float elapsedTime = getElapsedTime();
    std::cout << "Elapsed Time: " << elapsedTime << " seconds" << std::endl;*/

    EventBus::getInstance().processEvents(deltaTime);
    m_gameObjectManager.update(deltaTime);
   m_physicsManager.update(deltaTime);

   m_elapsedTime += deltaTime;
}

void MainState::draw()
{
    PROFILE_FUNCTION();
    m_spriteManager.draw();
    if (!m_font.loadFromFile("../assets/Megatech.ttf")) //black-and-white //stencilie
    {
        sf::err() << "Could not load font\n"; 
        return;
    }
    drawTime();
    drawLives();
    drawObeliskLives();
}

void MainState::drawTime()
{ 
    sf::RenderWindow& window   = m_game->getWindow();
    sf::View          view     = window.getView();
    sf::Vector2f      viewSize = view.getSize();

    sf::Text timerText;
    timerText.setFont(m_font);

    timerText.setCharacterSize(15);
    timerText.setFillColor(sf::Color::Red);
    // Set the position to the top-left corner of the view
    timerText.setPosition(view.getCenter().x - viewSize.x / 2.f + 5, view.getCenter().y - viewSize.y / 2.f + 25);

    yourScore = std::round(m_elapsedTime * 10.0f) / 10.0f;

    // Set the timer text using the elapsed time with one decimal place
    std::stringstream timerStringStream;
    timerStringStream << std::fixed << std::setprecision(1) << "Time: " << yourScore;
    std::string timerString = timerStringStream.str();

    timerText.setString(timerString);

    window.draw(timerText);
}

void MainState::drawLives()
{
    sf::RenderWindow& window   = m_game->getWindow();
    sf::View          view     = window.getView();
    sf::Vector2f      viewSize = view.getSize();

    sf::Text liveText;
    liveText.setFont(m_font);

    liveText.setCharacterSize(15);
    liveText.setFillColor(sf::Color::Red);
    // Set the position to the top-left corner of the view
    liveText.setPosition(view.getCenter().x - viewSize.x / 2.f + 5, view.getCenter().y - viewSize.y / 2.f + 60);

    if(auto playerGameObject = m_gameObjectManager.getGameObject("Player0"))
    {
        auto playerHealthComponent = playerGameObject->getComponent<HealthComponent>();
        int  HealthP = static_cast<int>(playerHealthComponent->getHealth());

        //liveText = 
        std::string liveString = "Lives: " + std::to_string(HealthP) + "%";
        liveText.setString(liveString);
        window.draw(liveText);

    }
}

void MainState::drawObeliskLives()
{
    sf::RenderWindow& window   = m_game->getWindow();
    sf::View          view     = window.getView();
    sf::Vector2f      viewSize = view.getSize();

    sf::Text obeliskText;
    obeliskText.setFont(m_font);

    obeliskText.setCharacterSize(15);
    obeliskText.setFillColor(sf::Color::Red);
    // Set the position to the top-left corner of the view
    obeliskText.setPosition(view.getCenter().x - viewSize.x / 2.f + 5, view.getCenter().y - viewSize.y / 2.f + (95));

    //const auto trigger = m_gameObjectManager.getGameObject("Trigger");
    //obeliskHealth      = trigger->addComponent<ObeliskHealthComponent>(*trigger, 100);

    int HealthP = static_cast<int>(obeliskHealth->getHealthOfObelisk());

    std::string obeliskString = "Obelsik: " + std::to_string(HealthP) + "%";
    obeliskText.setString(obeliskString);
    window.draw(obeliskText);
   
}

void MainState::savePointsToHighscoreFile(const std::string& filename, float score)
{
    // Load existing highscores
    loadHighscoresFromFile(filename);

    // Add the current score to highscores

    addScoreToHighscores(score);

    // Sort highscores in ascending order
    std::sort(highscores.begin(), highscores.end(), std::less<float>());

    // Truncate to keep only the top 5 highscores
    if (highscores.size() > 3)
    {
        highscores.resize(3);
    }

    // Save highscores to the file
    std::ofstream file(filename);

    if (file.is_open())
    {
        for (float score : highscores)
        {
            file << std::fixed << std::setprecision(1) << score << std::endl;
        }

        file.close();
    }
    else
    {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

void MainState::loadHighscoresFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (file.is_open())
    {
        float score;
        while (file >> score)
        {
            highscores.push_back(score);
        }

        file.close();
    }
}
void MainState::addScoreToHighscores(float score)
{
    highscores.push_back(std::round(score * 10.0f) / 10.0f);
}

float MainState::getYourScore() const
{
    return static_cast<float>(m_elapsedTime);
}

void MainState::displayHighscores()
{
    std::cout << "Bestenliste" << std::endl;
    for (int i = 0; i < highscores.size(); ++i)
    {
        std::cout << "Rank " << i + 1 << ": " << highscores[i] << std::endl;
    }
}

void MainState::saveCurrentScoreToFile(const std::string& filename) const
{
    std::ofstream file(filename);

    if (file.is_open())
    {
        if (m_enemydead <= 13)
        {
        std::cout << "Saving score to file: " << filename << std::endl;
        std::cout << "Score: " << yourScore << std::endl;
        file << std::fixed << std::setprecision(1) << yourScore << std::endl;
        file.close();

        }
        else
        {
			std::cout << "Saving score to file: " << filename << std::endl;
			std::cout << "Score: " << 0 << std::endl;
			file << std::fixed << std::setprecision(1) << 9999 << std::endl;
			file.close();
		}
    }
    else
    {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

void MainState::exit()
{
    PROFILE_FUNCTION();
    m_physicsManager.shutdown();
    m_spriteManager.shutdown();
    m_gameObjectManager.shutdown();
    savePointsToHighscoreFile("highscores.txt", yourScore);
    saveCurrentScoreToFile("score.txt");
    m_music.stop();

    displayHighscores();
    m_elapsedTime = 0;
}
} // namespace mmt_gd
