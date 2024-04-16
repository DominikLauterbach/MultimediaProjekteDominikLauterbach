#include "stdafx.h"

#include "BindingState.hpp"
#include "MenuState.hpp"
#include "Game.hpp"
#include "GameStateManager.hpp"
#include "InputManager.hpp"
#include "TGUI/TGUI.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <iostream>

namespace mmt_gd
{
using namespace std;

void BindingState::init()
{
    PROFILE_FUNCTION();

    std::cout << "BindingState::init()" << std::endl;

    if (m_isInit)
    {
        return;
    }

    // Load background image
    if (!m_backgroundTexture.loadFromFile("../assets/Keybinding.png"))
    {
        sf::err() << "Could not load background image\n";
        return;
    }

    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setPosition(0, 0); // Position des Hintergrunds auf (0, 0) setzen oder anpassen
    m_backgroundSprite.setScale(m_game->getWindow().getView().getSize().x / m_backgroundTexture.getSize().x,
                                m_game->getWindow().getView().getSize().y / m_backgroundTexture.getSize().y);

    //Text
    if (!m_font.loadFromFile("../assets/arial.ttf"))
    {
        sf::err() << "Could not load font\n";
        return;
    }
    m_text.setPosition(m_game->getWindow().getView().getCenter());
    m_text.setString("Press space to continue");
    m_text.setFillColor(sf::Color::Black);
    m_text.setFont(m_font);
    m_text.setOrigin(m_text.getLocalBounds().width * 0.5F, m_text.getLocalBounds().height * 0.5F);

    m_view = m_game->getWindow().getView();

    m_isInit = true;


    // LoadGui
    m_game->getGui().loadWidgetsFromFile("../assets/demoTgui.txt");

    if (const auto btn = dynamic_pointer_cast<tgui::Button>(m_game->getGui().get("StartGameBtn")))
    {
        btn->onClick([&manager = m_gameStateManager] { manager->setState("MainState"); });
    }
}

void BindingState::update(float delta)
{
    PROFILE_FUNCTION();

    m_game->getWindow().setView(m_view);

    if (InputManager::getInstance().isKeyPressed("Select") || sf::Joystick::isButtonPressed(0, 0))
    {
        m_gameStateManager->setState("MainState");
    }
}

void BindingState::draw()
{
    PROFILE_FUNCTION();

    m_game->getWindow().draw(m_backgroundSprite);

    m_game->getWindow().draw(m_text);
}

void BindingState::exit()
{
    PROFILE_FUNCTION();

    m_game->getGui().removeAllWidgets();

}
} // namespace mmt_gd
