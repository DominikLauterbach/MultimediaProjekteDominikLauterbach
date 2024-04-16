#include "stdafx.h"

#include "BindingState.hpp"
#include "LoseState.hpp"
#include "Game.hpp"
#include "GameStateManager.hpp"
#include "InputManager.hpp"
#include "MainState.hpp"
#include "MenuState.hpp"
#include "TGUI/TGUI.hpp"

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>


namespace mmt_gd
{
using namespace std;

void LoseState::init()
{
    PROFILE_FUNCTION();


    if (m_isInit)
    {
        return;
    }

    

    // Load background image
    if (!m_backgroundTexture.loadFromFile("../assets/EndState.jpeg"))
    {
        sf::err() << "Could not load background image\n";
        return;
    }

    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setScale(1.7F, 1.5F);
    m_backgroundSprite.setPosition(m_game->getWindow().getView().getCenter()); // Position des Hintergrunds auf (0,0)
    m_backgroundSprite.setOrigin(m_backgroundSprite.getLocalBounds().width * 0.5F,
                                 m_backgroundSprite.getLocalBounds().height * 0.5F);

    

    if (!m_font.loadFromFile("../assets/Megatech.ttf"))
    {
        sf::err() << "Could not load font\n";
        return;
    }
    m_text.setPosition(m_game->getWindow().getView().getCenter());
    m_text.setString("Game Over");
    m_text.setFillColor(sf::Color::Black);
    m_text.setFont(m_font);
    m_text.setOrigin(m_text.getLocalBounds().width * 0.5F, m_text.getLocalBounds().height * 0.5F);

    m_view = m_game->getWindow().getView();

    m_isInit = true; 

}

void LoseState::update(float delta)
{
    PROFILE_FUNCTION();


    if (InputManager::getInstance().isKeyPressed("Select") || sf::Joystick::isButtonPressed(0, 0))
    {
        m_gameStateManager->setState("MenuState");
    }

    m_game->getWindow().setView(m_view);
}




void LoseState::draw()
{
    PROFILE_FUNCTION();

    m_game->getWindow().draw(m_backgroundSprite); // Hintergrundbild zeichnen
    m_game->getWindow().draw(m_text);             // Text zeichnen
           // Score-Text zeichnen

   

    // Draw the highscore header text
 ;
}

void LoseState::exit()
{
    PROFILE_FUNCTION();


    m_game->getGui().removeAllWidgets();
}
} // namespace mmt_gd
