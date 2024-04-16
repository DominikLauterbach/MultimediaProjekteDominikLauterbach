#pragma once

#include "IComponent.hpp"
#include "RigidBodyComponent.hpp"

namespace mmt_gd
{

class HealthComponent : public IComponent
{
public:
    using ptr = std::shared_ptr<HealthComponent>;

    HealthComponent(GameObject& gameObject, int initialHealth, bool isPlayer, bool isMeele);

    bool init() override;
    void update(float deltaTime) override;

    void reduceHealth();
    void reduceHealthOfPlayer(); 
    void reduceHealthOfEnemy(); 
    void reduceHealthByMeele(); 
    void onDeath();
    int  getHealthOfPlayer();
    int  EnemydeadCount(int m_enemydead);
    int getHealth();

private:
    int m_initialHealth;
    int m_currentHealth;
    bool m_isPlayer;
    bool isActive;
    int  m_enemydead;
    bool m_gameObjectToMove {false};
    bool m_isMeele;
};
} // namespace mmt_gd
