#pragma once

#include "GameState.hpp"

#include <SFML/Graphics/Text.hpp>

namespace mmt_gd
{
class EndState final : public GameState
{
public:
    using GameState::GameState;

    void init() override;

    void update(float delta) override;
    void draw() override;
    void exit() override;
    void loadHighscoresFromFile(const std::string& filename);
    void loadScoreFromFile(const std::string& filename);

private:
    sf::Text m_text;
    sf::Font m_font;
    sf::View m_view;

    sf::Texture m_backgroundTexture;
    sf::Sprite  m_backgroundSprite;
    sf::Text    m_scoreText;
    sf::Text    m_highscoreText; // Text for Highscore
    sf::Music   m_music;
    
    float         yourScore;
    float         m_highscore = 0;

    std::vector<int> highscores;

    bool m_isInit = false;
};
} // namespace mmt_gd
