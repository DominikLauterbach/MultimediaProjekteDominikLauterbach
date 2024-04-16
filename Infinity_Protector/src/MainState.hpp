#pragma once

#include "GameObjectManager.hpp"
#include "GameState.hpp"
#include "PhysicsManager.hpp"
#include "SpriteManager.hpp"
#include "ObeliskHealthComponent.hpp"
#include <chrono>
#include <memory>
#include <thread>

namespace mmt_gd
{
class FINALFRONTIER_API MainState final : public GameState
{
public:
    MainState(GameStateManager* gameStateManager, Game* game);


    void init() override;
    void exit() override;

    void update(float deltaTime) override;
    void draw() override;
    void drawTime();
    void drawLives();
    void drawObeliskLives();
    void savePointsToHighscoreFile(const std::string& filename, float score);
    void loadHighscoresFromFile(const std::string& filename);
    void addScoreToHighscores(float score);
    float  getYourScore() const;
    void displayHighscores();
    float  yourScore;
    void saveCurrentScoreToFile(const std::string& filename) const;




private:
    SpriteManager     m_spriteManager;
    GameObjectManager m_gameObjectManager;
    PhysicsManager    m_physicsManager;
    int               m_enemydead = 0;
    float             m_elapsedTime;
    std::shared_ptr<ObeliskHealthComponent> obeliskHealth=nullptr;
    
    sf::Music												   m_music;
    sf::Text                                                    m_text;
    sf::Font                                                    m_font;
    sf::View                                                    m_view;
    bool                                                        m_isInit = false;
    
    void  startTimer();
    float getElapsedTime() const;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
    bool                                                        m_timerRunning;
    std::vector<int>                                            highscores; // Variable für Highscores
};
} // namespace mmt_gd
