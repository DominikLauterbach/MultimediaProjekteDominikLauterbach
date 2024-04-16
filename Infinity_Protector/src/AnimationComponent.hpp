#pragma once

#include "IComponent.hpp"
#include "RigidBodyComponent.hpp"
#include "SpriteRenderComponent.hpp"

#include <cmath>


namespace mmt_gd
{

class AnimationComponent : public IComponent
{
public:
    using ptr = std::shared_ptr<AnimationComponent>;

    AnimationComponent(GameObject & gameObject,
                             int                                            playerIndx,
                             sf::IntRect                                    textureRect,
                             std::shared_ptr<mmt_gd::SpriteRenderComponent> renderComp,
                             bool                                           isPlayer);

    bool init() override;
    void update(float deltaTime) override;


private:
    enum Direction
    {
        IDLE,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    Direction m_lastDirection;

    int m_initialHealth;
    int m_playerIndx;
    int m_health;
    sf::IntRect m_textureRect;
    std::shared_ptr<mmt_gd::SpriteRenderComponent> m_renderComp;

    float m_animationTimer; 
    float m_animationInterval;
    int m_currentFrame;
    int m_frameWidth;
    int m_frameHeight;
    int m_numFrames;
    bool  m_isPlayer;
};
} // namespace mmt_gd
