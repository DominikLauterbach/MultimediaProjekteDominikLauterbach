#pragma once
#include "BulletPool.hpp"
#include "IComponent.hpp"


namespace mmt_gd
{
class PlayerShootComponent final : public IComponent
{
public:
    PlayerShootComponent(GameObject&        gameObject,
                         size_t             poolSize,
                         sf::RenderWindow&  renderWindow,
                         const std::string& textureFile,
                         sf::IntRect        textureRect,
                         sf::FloatRect      colliderRect,
                         float              bulletMass,
                         const std::string& layerName);


    void shoot(sf::Vector2f directionSpeed, float deltaTime);
    bool init() override;
    void update(float deltaTime) override;


    sf::Music m_shootSound;
    //sf::Music  m_shootSoundBuffer;
    BulletPool m_pool;
    float      m_timeSinceLastShot{};
};
} // namespace mmt_gd
