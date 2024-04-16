#include "stdafx.h"

#include "PlayerShootComponent.hpp"

#include "InputManager.hpp"
#include "PhysicsManager.hpp"
#include "RigidBodyComponent.hpp"

#include <SFML/System.hpp>
#include <SFML/Window/Joystick.hpp>
#include <iostream>
#include <SFML/Audio.hpp>

mmt_gd::PlayerShootComponent::PlayerShootComponent(
    GameObject&         gameObject,
    const size_t        poolSize,
    sf::RenderWindow&   renderWindow,
    const std::string&  textureFile,
    const sf::IntRect   textureRect,
    const sf::FloatRect colliderRect,
    const float         bulletMass,
    const std::string&  layerName) :
IComponent(gameObject),
m_pool(poolSize, textureFile, textureRect, layerName, renderWindow, colliderRect, bulletMass /*, onBulletCollision*/)
{
}

void mmt_gd::PlayerShootComponent::shoot(sf::Vector2f directionSpeed, float deltaTime)
{
    if (m_timeSinceLastShot > 0.5F)
    {
        m_shootSound.play();
        const auto& bullet = m_pool.get();

        bullet->setActive(true);
        bullet->getComponent<RigidBodyComponent>()->getB2Body()->SetEnabled(true);


        // Änderung des Offsets basierend auf der Richtung des Schusses
        float xOffset = (directionSpeed.x > 0) ? 30.0f : -60.0f;
        
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

bool mmt_gd::PlayerShootComponent::init()
{
    if (!m_shootSound.openFromFile("../assets/schusssoundDankeMatze.wav"))
    {
        std::cerr << "Could not load music file" << std::endl;
    }
    
    return true;
}



void mmt_gd::PlayerShootComponent::update(float deltaTime)
{
    m_timeSinceLastShot += deltaTime;

    // Use controller input from the right stick
    float rightStickX = sf::Joystick::getAxisPosition(0, sf::Joystick::U);


     //testcode
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
    {
        // Shoot to the left
        sf::Vector2f speed(-10.0f, 0.0f);
        shoot(speed, deltaTime);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
    {
        // Shoot to the right
        sf::Vector2f speed(10.0f, 0.0f);
        shoot(speed, deltaTime);
    }
    //testcode




    // Threshold to avoid small accidental movements
    if (std::abs(rightStickX) > 20.0f)
    {
       // m_shootSound.play();
        // Calculate the shooting direction based on right stick input
        sf::Vector2f direction = sf::Vector2f(rightStickX, 0.f); // Invert Y-axis for correct direction
        // Normalize the direction vector
        float length = std::sqrt(direction.x * direction.x);
        if (length > 0)
        {
            direction /= length;
            // Adjust the speed based on your needs
            sf::Vector2f speed = direction * 50.0f;
            // Call the shoot function with the calculated direction and speed
            shoot(speed, deltaTime);
            
        }
    }
}
