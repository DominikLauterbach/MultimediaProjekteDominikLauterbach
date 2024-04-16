#include "stdafx.h"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "HealthComponent.hpp"
#include "CountEvent.hpp"
#include "EventBus.hpp"
#include "RigidBodyComponent.hpp"
#include "PhysicsManager.hpp"

#include <iostream>

namespace mmt_gd
{
HealthComponent::HealthComponent(GameObject& gameObject, int initialHealth, bool isPlayer, bool isMeele) :
IComponent(gameObject),
m_initialHealth(initialHealth),
m_currentHealth(initialHealth),
m_isPlayer(isPlayer),
m_enemydead(0),
m_isMeele(isMeele)
{
    
}
 
bool HealthComponent::init()
{
    return true;
}

void HealthComponent::update(const float deltaTime)
{
    if (m_currentHealth <= 0)
    {
        m_gameObject.setActive(false);
        m_gameObject.getComponent<RigidBodyComponent>()->getB2Body()->SetEnabled(false);
    }

    if (m_gameObjectToMove)
    {
		m_gameObject.setPosition({100000.f, 100000.f});
		m_gameObjectToMove = false;
	}

  
}

void HealthComponent::reduceHealth()
{
    if (m_isPlayer)
    {
        reduceHealthOfPlayer();
    }
    else
    {
        reduceHealthOfEnemy();
    }
}
void HealthComponent::reduceHealthOfEnemy()
{
    //std::cout << "hallo ich bims enemie mit ie" << std::endl;
    m_currentHealth -= 20;
    //std::cout << "Enemy now Health: " << m_currentHealth << std::endl;
    if (m_currentHealth <= 0)
    {
        //std::cout << "Enemy dead + position 100000!" << std::endl;

        m_gameObjectToMove = true;

        EventBus::getInstance().fireEvent(std::make_shared<CountEvent>(1));
        //std::cout << "Enemy dead count" << std::endl;
    }
}
void HealthComponent::reduceHealthByMeele()
{

    if (m_isPlayer)
    {
        m_currentHealth -= 2;
        std::cout << m_currentHealth << std::endl;
       /* std::cout << "Meele hit something" << std::endl; */  
    }
    else
    {
        //std::cout << "No Meele hit" << std::endl;
    }
}

void HealthComponent::reduceHealthOfPlayer()
{
    m_currentHealth -= 5;
}

int HealthComponent::getHealth()
{
    return m_currentHealth;
}
} // namespace mmt_gd
