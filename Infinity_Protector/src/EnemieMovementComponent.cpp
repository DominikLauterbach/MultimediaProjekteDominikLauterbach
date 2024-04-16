#include "stdafx.h"

#include "EnemieMovementComponent.hpp"

#include "GameObject.hpp"
#include "RigidBodyComponent.hpp"

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

namespace mmt_gd
{
EnemieMovementComponent::EnemieMovementComponent(GameObject& gameObject, RigidBodyComponent& rigidBody, const int enemyIdx) :
IComponent(gameObject),
m_enemyIdx(enemyIdx),
m_rigidBody(rigidBody),
m_targetPositionL(579.17f, 660.f),
m_targetPositionT(668.86f, 633.89f),
m_targetPositionR(672.11f, 674.89f),

m_targetPositionS(260.87f, 512.6f),
m_targetPositionS2(192.21f, 831.94f),
m_targetPositionS3(1024.21f, 405.27f),
m_targetPositionS4(986.87f, 769.27f)
{
}

bool EnemieMovementComponent::init()
{
    return true;
}

void EnemieMovementComponent::update(const float deltaTime)
{
    const auto speed = 60.0F; // pixels/second

    if (m_enemyIdx == 1 || m_enemyIdx == 2 || m_enemyIdx == 3) //Enemies who spawn Left
    {
        // Calculate the direction vector from current position to the target position
        sf::Vector2f direction = m_targetPositionL - m_rigidBody.getPosition();

        // Normalize the direction vector
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 5.0f)
        {
            if (length !=0)
            direction /= length;
        }
        else
        {
            m_rigidBody.setPosition(m_targetPositionL);
            std::cout << "Enemy reached target position" << std::endl;
        }

        // Move the enemy towards the target position
        sf::Vector2f velocity = direction * speed * deltaTime;
        m_rigidBody.setPosition(m_rigidBody.getPosition() + velocity);
    }

    if (m_enemyIdx == 9 || m_enemyIdx == 10 || m_enemyIdx == 13) //Enemies who spawn Top
    {
        // Calculate the direction vector from current position to the target position
        sf::Vector2f direction = m_targetPositionT - m_rigidBody.getPosition();

        // Normalize the direction vector
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 5.0f)
        {
            if (length != 0)

            direction /= length;
        }
        else
        {
            m_rigidBody.setPosition(m_targetPositionT);
            std::cout << "Enemy reached target position" << std::endl;
        }

        // Move the enemy towards the target position
        sf::Vector2f velocity = direction * speed * deltaTime;
        m_rigidBody.setPosition(m_rigidBody.getPosition() + velocity);
    }

    if (m_enemyIdx == 8 || m_enemyIdx == 11 || m_enemyIdx == 12) //Enemies who spawn Right
    {
        // Calculate the direction vector from current position to the target position
        sf::Vector2f direction = m_targetPositionR - m_rigidBody.getPosition();

        // Normalize the direction vector
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 5.0f)
        {
            if (length != 0)
            direction /= length;
        }
        else
        {
            m_rigidBody.setPosition(m_targetPositionR);
            std::cout << "Enemy reached target position" << std::endl;
        }

        // Move the enemy towards the target position
        sf::Vector2f velocity = direction * speed * deltaTime;
        m_rigidBody.setPosition(m_rigidBody.getPosition() + velocity);
    }
    switch (m_enemyIdx)
    {
        case 4:
            m_rigidBody.setPosition(m_targetPositionS);
            break;
        case 5:
            m_rigidBody.setPosition(m_targetPositionS2);
            break;
        case 6:
            m_rigidBody.setPosition(m_targetPositionS3);
            break;
        case 7:
            m_rigidBody.setPosition(m_targetPositionS4);
            break;
        default:
            break;
    }
}
} // namespace mmt_gd
