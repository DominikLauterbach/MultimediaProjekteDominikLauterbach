#include "stdafx.h"

#include "PlayerMoveComponent.hpp"

#include "GameObject.hpp"
#include "InputManager.hpp"
#include "AnimatedSprite.hpp"
#include "Animation.hpp"

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

namespace mmt_gd
{
PlayerMoveComponent::PlayerMoveComponent(GameObject& gameObject, RigidBodyComponent& rigidBody, const int playerIndex) :
IComponent(gameObject),
m_playerIndex(playerIndex),
m_rigidBody(rigidBody)
{
}

bool PlayerMoveComponent::init()
{
    return true;
}

void PlayerMoveComponent::update(const float deltaTime)
{
    const auto   speed = 3'000.0F; // pixels/second
    sf::Vector2f translation{};

    // Use controller input from the left stick
    float xAxis = sf::Joystick::getAxisPosition(m_playerIndex, sf::Joystick::X);
    float yAxis = sf::Joystick::getAxisPosition(m_playerIndex, sf::Joystick::Y);

    // Threshold to avoid small accidental movements
    if (std::abs(xAxis) > 20.0f)
    {
        translation.x += speed * xAxis * deltaTime / 100.0f;
    }

    if (std::abs(yAxis) > 20.0f)
    {
        translation.y += speed * yAxis * deltaTime / 100.0f;
    }

    // Check keyboard input
    if (InputManager::getInstance().isKeyDown("right", m_playerIndex))
    {
        translation.x += speed * deltaTime;
    }
    if (InputManager::getInstance().isKeyDown("left", m_playerIndex))
    {
        translation.x -= speed * deltaTime;
    }
    if (InputManager::getInstance().isKeyDown("up", m_playerIndex))
    {
        translation.y -= speed * deltaTime;
    }
    if (InputManager::getInstance().isKeyDown("down", m_playerIndex))
    {
        translation.y += speed * deltaTime;
    }


    // Check if there is any input
    if (std::abs(xAxis) > 20.0f || std::abs(yAxis) > 20.0f || sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_rigidBody.addVelocity(translation);
    }
    else
    {
        // If no input, set velocity to zero to stop the player immediately
        m_rigidBody.setVelocity(sf::Vector2f(0.0f, 0.0f));
    }

#if 1 // physics movement
    m_rigidBody.addVelocity(translation);
#else // no physics movement
    m_gameObject.GetTransform().translate(translation);
#endif
}
} // namespace mmt_gd
