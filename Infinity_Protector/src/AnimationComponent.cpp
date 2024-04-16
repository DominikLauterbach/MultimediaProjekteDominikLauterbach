#include "stdafx.h"

#include "GameObject.hpp"
#include "InputManager.hpp"
#include "AnimationComponent.hpp"
#include <SFML/Window/Joystick.hpp>

#include <cmath>
#include <iostream>

namespace mmt_gd
{
AnimationComponent::AnimationComponent(
    GameObject&                                    gameObject,
    int                                            playerIndx,
    sf::IntRect                                    textureRect,
    std::shared_ptr<mmt_gd::SpriteRenderComponent> renderComp,
    bool                                           isPlayer) :
IComponent(gameObject),
m_playerIndx(playerIndx),
m_health(playerIndx),
m_textureRect(textureRect),
m_renderComp(renderComp),

m_animationTimer(0.f),
m_animationInterval(0.4f),
m_currentFrame(0),
m_frameWidth(32),   //32
m_frameHeight(44), //44
m_numFrames(4),
m_isPlayer(isPlayer),
m_lastDirection(IDLE) 
{
}
bool AnimationComponent::init()
{
    return true;
}

void AnimationComponent::update(const float deltaTime)
{
    m_animationTimer += deltaTime;

    if (m_animationTimer >= m_animationInterval)
    {
        m_animationTimer -= m_animationInterval;
        m_currentFrame = (m_currentFrame + 1) % m_numFrames;

        if (m_isPlayer)
        {
            // Use controller input from the left stick
            float xAxis = sf::Joystick::getAxisPosition(m_playerIndx, sf::Joystick::X);
            float yAxis = sf::Joystick::getAxisPosition(m_playerIndx, sf::Joystick::Y);

            // Calculate the angle in radians
            float angle = atan2(yAxis, xAxis);

            // Convert the angle to degrees
            #ifndef M_PI
            #define M_PI 3.14159265358979323846
            #endif
            float angleDeg = angle * 180.0f / M_PI;

            // Check if the player is idle
            bool isIdle = (std::abs(xAxis) < 10 && std::abs(yAxis) < 10);
            if (isIdle)
            {
                switch (m_lastDirection)
                {
                    case AnimationComponent::LEFT:
                        std::cout << "left" << std::endl;
                        m_textureRect.top = m_playerIndx * m_frameHeight + 64;
                        break;
                    case AnimationComponent::RIGHT:
                        std::cout << "right" << std::endl;
                        m_textureRect.top = m_playerIndx * m_frameHeight;
                        break;
                    case AnimationComponent::UP:
                        std::cout << "up" << std::endl;
                        m_textureRect.top = m_playerIndx * m_frameHeight + 64;
                        break;
                    case AnimationComponent::DOWN:
                        std::cout << "down" << std::endl;
                        m_textureRect.top = m_playerIndx * m_frameHeight;
                        break;
                    default:
                        break;
                }
                m_textureRect.left = m_currentFrame * m_frameWidth;
            }
            else
            {
                 if (std::abs(xAxis) > std::abs(yAxis))
                {
                    // Move horizontally
                    if (xAxis > 0)
                    {
                        // Facing right
                        m_textureRect.top = m_playerIndx * m_frameHeight + 32;
                        m_lastDirection   = RIGHT;
                    }
                    else
                    {
                        // Facing left
                        m_textureRect.top = m_playerIndx * m_frameHeight + 64;
                        m_lastDirection   = LEFT;
                    }
                }
                else
                {
                    // Move vertically
                    if (yAxis > 0)
                    {
                        // Facing down
                        m_textureRect.top = m_playerIndx * m_frameHeight + 64;
                        m_lastDirection   = DOWN;
                    }
                    else
                    {
                        // Facing up
                        m_textureRect.top = m_playerIndx * m_frameHeight + 32;
                        m_lastDirection   = UP;
                    }
                }
            }
        }
        else
        {
            m_textureRect.top  = m_playerIndx * m_frameHeight;
        }
        m_textureRect.left = m_currentFrame * m_frameWidth;

        m_renderComp->getSprite().setTextureRect(m_textureRect);
    }
}
} // namespace mmt_gd
