#pragma once
#include "BulletPool.hpp"
#include "IComponent.hpp"


namespace mmt_gd
{
class EnemyShootComponent final : public IComponent
{
public:
    EnemyShootComponent(GameObject&        gameObject,
                         size_t             poolSize,
                         sf::RenderWindow&  renderWindow,
                         const std::string& textureFile,
                         sf::IntRect        textureRect,
                         sf::FloatRect      colliderRect,
                         float              bulletMass,
                         const std::string& layerName,
                         int enemyIdx);


    void shoot(sf::Vector2f directionSpeed, float deltaTime);
    bool init() override;
    void update(float deltaTime) override;

    BulletPool m_pool;
    float      m_timeSinceLastShot{};

private:
    int m_enemyIdx;
};
} // namespace mmt_gd
