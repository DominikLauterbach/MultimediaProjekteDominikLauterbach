#include "stdafx.h"

#include "InputManager.hpp"
#include "PhysicsManager.hpp"
#include "EnemyShootComponent.hpp"
#include "RigidBodyComponent.hpp"

#include <SFML/System.hpp>
#include <SFML/Window/Joystick.hpp> // Include SFML Joystick header
#include <iostream>

mmt_gd::EnemyShootComponent::EnemyShootComponent(
    GameObject&         gameObject,
    const size_t        poolSize,
    sf::RenderWindow&   renderWindow,
    const std::string&  textureFile,
    const sf::IntRect   textureRect,
    const sf::FloatRect colliderRect,
    const float         bulletMass,
    const std::string&  layerName,
    const int           enemyIdx) :
IComponent(gameObject),
m_pool(poolSize, textureFile, textureRect, layerName, renderWindow, colliderRect, bulletMass /*, onBulletCollision*/),
m_enemyIdx(enemyIdx)
{
}

void mmt_gd::EnemyShootComponent::shoot(sf::Vector2f directionSpeed, float deltaTime)
{
    if (m_timeSinceLastShot > 0.8F)
    {
        const auto& bullet = m_pool.get();

        bullet->setActive(true);

        // Änderung des Offsets basierend auf der Richtung des Schusses
        float xOffset = (directionSpeed.x > 0) ? 30.0f : -30.0f;
        bullet->setPosition(m_gameObject.getPosition() + sf::Vector2f{xOffset, 0.F});

        bullet->update(0);

        const auto rb = bullet->getComponent<RigidBodyComponent>();
        rb->addVelocity(directionSpeed);
        rb->getB2Body()->SetFixedRotation(true);

        rb->getB2Body()->SetEnabled(true);
        rb->getB2Body()->SetTransform(PhysicsManager::s2b(bullet->getPosition()), 0.F);
        m_timeSinceLastShot = 0;
    }
}

bool mmt_gd::EnemyShootComponent::init()
{
    return true;
}


void mmt_gd::EnemyShootComponent::update(float deltaTime)
{
    m_timeSinceLastShot += deltaTime;

    // Use controller input from the right stick
    float rightStickX = sf::Joystick::getAxisPosition(0, sf::Joystick::U);


    //testcode
    if (m_enemyIdx == 4 || m_enemyIdx == 5)
        {
        sf::Vector2f speed(10.0f, 0.0f);
        shoot(speed, deltaTime);
    }
        if (m_enemyIdx == 6 || m_enemyIdx == 7)
        {
        sf::Vector2f speed(-10.0f, 0.0f);
        shoot(speed, deltaTime);
        }
}
