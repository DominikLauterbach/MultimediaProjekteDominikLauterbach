#pragma once

#include "IComponent.hpp"
#include "RigidBodyComponent.hpp"

namespace mmt_gd
{

class ObeliskHealthComponent : public IComponent
{
public:
    using ptr = std::shared_ptr<ObeliskHealthComponent>;

    ObeliskHealthComponent(GameObject& gameObject,
                          int                 initialHealth);

    bool init() override;
    void update(float deltaTime) override;

    int reduceHealthOfObelisk();
    void reduceHealthOfEnemy();
    void onDeath(ObeliskHealthComponent& obelisk); 
    int  getHealthOfObelisk();

private:
    int m_initialHealth;
    int m_health;
};
} // namespace mmt_gd
