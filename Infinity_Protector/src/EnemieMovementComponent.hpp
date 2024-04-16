#pragma once

#include "IComponent.hpp"
#include "RigidBodyComponent.hpp"

namespace mmt_gd
{
class EnemieMovementComponent : public IComponent
{
public:
    using ptr = std::shared_ptr<EnemieMovementComponent>;

    EnemieMovementComponent(GameObject& gameObject, RigidBodyComponent& rigidBody, int enemyIdx);

    bool init() override;
    void update(float deltaTime) override;

    // Set the target position for the enemy to move towards
    void setTargetPosition(const sf::Vector2f& targetPosition);

private:
    int                 m_enemyIdx;
    RigidBodyComponent& m_rigidBody;
    sf::Vector2f        m_targetPositionL;
    sf::Vector2f        m_targetPositionT;
    sf::Vector2f        m_targetPositionR;
    sf::Vector2f        m_targetPositionS;
    sf::Vector2f        m_targetPositionS2;
    sf::Vector2f        m_targetPositionS3;
    sf::Vector2f        m_targetPositionS4;
};
} // namespace mmt_gd
