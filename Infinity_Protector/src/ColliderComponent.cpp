#include "stdafx.h"

#include "ColliderComponent.hpp"
#include "DebugDraw.hpp"
#include "EventBus.hpp"
#include "GameObject.hpp"
#include "PhysicsComponentEvents.hpp"
#include "HealthComponent.hpp"
#include "iostream"

namespace mmt_gd
{
ColliderComponent::ColliderComponent(GameObject& gameObject, RigidBodyComponent& body, b2FixtureDef& def) :
IComponent(gameObject),
m_body(body),
m_fixture(nullptr),
m_bullets()
{
    def.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_fixture            = m_body.getB2Body()->CreateFixture(&def);
}

void ColliderComponent::update(float deltaTime)
{
    //auto box = m_fixture->GetAABB(0);
    //auto ex  = box.GetExtents();
    //DebugDraw::getInstance().drawRectangle(m_gameObject.getPosition(), {ex.x * 2, ex.y * 2}, sf::Color::Green);

    for (auto& bullet : m_bullets)
    {
		bullet->SetEnabled(false);
        
	}
    m_bullets.clear();

}

void ColliderComponent::registerOnCollisionFunction(const OnCollisionFunction& func)
{
    m_onCollisionFunctions.push_back(func);
}

void ColliderComponent::onCollision(ColliderComponent& collider)
{
    for (const auto& f : m_onCollisionFunctions)
    {
        f(*this, collider);
    }
    if (collider.m_gameObject.getId().substr(0, 6) == "Bullet") //check intersect
    {
        auto healthComponent = m_gameObject.getComponent<HealthComponent>();

        if (healthComponent)
        {
            healthComponent->reduceHealth();
        }
        collider.getGameObject().setActive(false);
        m_bullets.push_back(collider.getBody().getB2Body());

        //std::cout << "bullet deletet" << std::endl;
    }

    if (collider.m_gameObject.getId().substr(0, 5) == "Enemy") //check intersect
    {
        //std::cout << "hit..." << std::endl;
        auto healthComponent = m_gameObject.getComponent<HealthComponent>();

        if (healthComponent)
        {
            healthComponent->reduceHealthByMeele();
        }
    }
}
} // namespace mmt_gd
