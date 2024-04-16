#include "stdafx.h"

#include "GameObject.hpp"
#include "InputManager.hpp"
#include "ObeliskHealthComponent.hpp"
#include <iostream>

namespace mmt_gd
{
ObeliskHealthComponent::ObeliskHealthComponent(GameObject& gameObject,
                                             int           initialHealth):
IComponent(gameObject),
m_initialHealth(initialHealth),
m_health(initialHealth)
{
}
 
bool ObeliskHealthComponent::init()
{

    reduceHealthOfObelisk();
    return true;
}

void ObeliskHealthComponent::update(const float deltaTime)
{
}


int ObeliskHealthComponent::reduceHealthOfObelisk()
{
    std::cout << "Obelisk Health: " << m_initialHealth << std::endl;

    m_health = m_initialHealth -= 10;
    std::cout << "now Health: " << m_health << std::endl;

    if (m_health <= 0)
    {
        onDeath(*this);
    }
    return m_health;
}
int ObeliskHealthComponent::getHealthOfObelisk()
{
	return m_health;
}
void ObeliskHealthComponent::reduceHealthOfEnemy()
{

    std::cout << "Enemy Health: " << m_initialHealth << std::endl;

    int health = m_initialHealth -= 1;
    std::cout << "now Enemy Health: " << health << std::endl;

    if (health <= 0)
    {
        std::cout << "Enemy destroyed!" << std::endl;
    }
}

void ObeliskHealthComponent::onDeath(ObeliskHealthComponent& obelisk)
{
    obelisk.getGameObject().setActive(false);
    std::cout << "Obelisk destroyed!" << std::endl;

}
} // namespace mmt_gd
