#include "stdafx.h"

#include "BindingState.hpp"
#include "Game.hpp"
#include "GameStateManager.hpp"
#include "InputManager.hpp"
#include "MenuState.hpp"
#include "TGUI/TGUI.hpp"
#include "EndState.hpp"
#include "MainState.hpp"
#include "InputManager.hpp"
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>


namespace mmt_gd
{
using namespace std;

void EndState::init()
{
    PROFILE_FUNCTION();


    if (m_isInit)
    {
        return;
    }

    loadScoreFromFile("score.txt");

    // Load background image
    if (!m_backgroundTexture.loadFromFile("../assets/win.jpg"))
    {
        sf::err() << "Could not load background image\n";
        return;
    }

    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setScale(1.7F, 1.5F);
    m_backgroundSprite.setPosition(m_game->getWindow().getView().getCenter()); // Position des Hintergrunds auf (0,0)
    m_backgroundSprite.setOrigin(m_backgroundSprite.getLocalBounds().width * 0.5F,
                                 m_backgroundSprite.getLocalBounds().height * 0.5F);

    if (!m_font.loadFromFile("../assets/arial.TTF"))
    {
        sf::err() << "Could not load font\n";
        return;
    }

    //Score
    m_scoreText.setPosition(m_game->getWindow().getView().getCenter().x - 130,
                            m_game->getWindow().getView().getCenter().y); // ajust position
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(30);
    m_scoreText.setFillColor(sf::Color::Green);
    m_scoreText.setOrigin(m_scoreText.getLocalBounds().width * 0.5F, m_scoreText.getLocalBounds().height * 0.5F);
    sf::FloatRect textBounds   = m_text.getGlobalBounds();
    int           offsetHeight = 20;

    m_view = m_game->getWindow().getView();
    loadHighscoresFromFile("highscores.txt");

    if (!m_font.loadFromFile("../assets/Megatech.ttf"))
    {
        sf::err() << "Could not load font\n";
        return;
    }
    /*m_text.setPosition(m_game->getWindow().getView().getCenter());
    m_text.setString("Highscore: 420");
    m_text.setFillColor(sf::Color::Black);
    m_text.setFont(m_font);
    m_text.setOrigin(m_text.getLocalBounds().width * 0.5F, m_text.getLocalBounds().height * 0.5F);*/

    m_view = m_game->getWindow().getView();

    m_isInit = true;

}

void EndState::update(float delta)
{
    PROFILE_FUNCTION();


    if (InputManager::getInstance().isKeyPressed("Select") || sf::Joystick::isButtonPressed(0, 0))
    {
        m_gameStateManager->setState("MenuState");
    }
    
    m_game->getWindow().setView(m_view);
}

void EndState::loadScoreFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (file.is_open())
    {
        std::cout << "EndState: File opened successfully" << std::endl;
        file >> yourScore;
        file.close();

        // Update m_scoreText after loading the score
        m_scoreText.setString("Your Score " + std::to_string(yourScore));
    }
    else
    {
        sf::err() << "Error opening file: " << filename << std::endl;
    }
}

void EndState::loadHighscoresFromFile(const std::string& filename)
{
    std::cout << "EndState: LoadHighscorefromfile" << std::endl;
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

void EndState::draw()
{
    PROFILE_FUNCTION();

    m_game->getWindow().draw(m_backgroundSprite); // Hintergrundbild zeichnen
    m_game->getWindow().draw(m_text);             // Text zeichnen
    m_game->getWindow().draw(m_scoreText);        // Score-Text zeichnen


    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << yourScore;
    m_scoreText.setString("Your Score: " + ss.str());

    // Score-Texte f�r den Highscore und die Highscores zeichnen
    sf::Text highscoreHeaderText;
    highscoreHeaderText.setFont(m_font);
    highscoreHeaderText.setCharacterSize(30);
    highscoreHeaderText.setFillColor(sf::Color::Green);
    highscoreHeaderText.setString("Highscore");
    highscoreHeaderText.setOrigin(highscoreHeaderText.getLocalBounds().width * 0.5F, 0.0F);
    int offsetHeight = 50;
    highscoreHeaderText.setPosition(m_scoreText.getPosition().x + 140,
                                    m_scoreText.getPosition().y + m_scoreText.getGlobalBounds().height - 190);

    // Draw the highscore header text
    m_game->getWindow().draw(highscoreHeaderText);

    // Highscore-Text zeichnen
    sf::Text highscoreText;
    highscoreText.setFont(m_font);
    highscoreText.setCharacterSize(30);
    highscoreText.setFillColor(sf::Color::White);

    // Setze den Highscore-Text
    std::string highscoreString;
    for (size_t i = 0; i < highscores.size(); ++i)
    {
        highscoreString += "#" + std::to_string(i + 1) + ":" + std::to_string(highscores[i]) + "\n";
    }
    highscoreText.setString(highscoreString);

    // Position des Highscore-Textes festlegen
    highscoreText.setOrigin(highscoreText.getLocalBounds().width * 0.5F, 0.0F);
    int offsetHeightHighscoreText = 10;
    highscoreText.setPosition(highscoreHeaderText.getPosition().x + 50,
                              highscoreHeaderText.getPosition().y + highscoreHeaderText.getGlobalBounds().height);

    // Draw the highscore text
    m_game->getWindow().draw(highscoreText);
}

void EndState::exit()
{
    PROFILE_FUNCTION();


    m_game->getGui().removeAllWidgets();
}
} // namespace mmt_gd
