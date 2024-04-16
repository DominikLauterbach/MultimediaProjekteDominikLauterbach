#include "stdafx.h"

#include "BulletPool.hpp"

#include "ColliderComponent.hpp"
#include "EventBus.hpp"
#include "PhysicsManager.hpp"
#include "GameObjectEvents.hpp"
#include "RigidBodyComponent.hpp"
#include "SpriteRenderComponent.hpp"

#include <iostream>
#include <memory>

mmt_gd::BulletPool::BulletPool(
    const size_t size,
    const std::string& textureFile,
    sf::IntRect textureRect,
    const std::string& layerName,
    sf::RenderWindow& renderWindow,
    sf::FloatRect colliderRect,
    float mass/*,
    std::function<void(BoxColliderComponent& a, BoxColliderComponent& b)> collisionCallback*/) :
    m_pool(size, nullptr) /*,
m_collisionCallback(std::move(collisionCallback))*/
{
    int counter = 0;
    for (auto& gameObject : m_pool)
    {
        gameObject = std::make_shared<GameObject>("Bullet_" + std::to_string(m_globalBulletIdx++));
        gameObject->setPosition(-1000, -1000);
        const auto renderComp = gameObject->addComponent<SpriteRenderComponent>(*gameObject, renderWindow, textureFile, layerName);
        renderComp->getSprite().setTextureRect(textureRect);

        auto rigidBodyComponent = gameObject->addComponent<RigidBodyComponent>(*gameObject, b2_dynamicBody);

        auto fixtureDef    = b2FixtureDef{};
        fixtureDef.density = 0.1F;
        auto shape         = b2PolygonShape{};

        auto spriteBounds = renderComp->getSprite().getGlobalBounds();
        
        shape.SetAsBox(spriteBounds.width * .4f * PhysicsManager::UNRATIO,
                       spriteBounds.height * .2f * PhysicsManager::UNRATIO,
                       b2Vec2{spriteBounds.width * .5f * PhysicsManager::UNRATIO,
                              spriteBounds.height * .5f * PhysicsManager::UNRATIO},
                      0);

        fixtureDef.shape = &shape;

        auto boxColliderComponent = gameObject->addComponent<ColliderComponent>(*gameObject, *rigidBodyComponent, fixtureDef);
       // boxColliderComponent->registerOnCollisionFunction(m_collisionCallback);

        if (!gameObject->init())
        {
            sf::err() << "Could not initialize go " << gameObject->getId() << std::endl;
        }
        rigidBodyComponent->getB2Body()->SetEnabled(false);

        gameObject->setActive(false);
        EventBus::getInstance().fireEvent(std::make_shared<GameObjectCreateEvent>(gameObject));
        
    }

    //std::cout << "## pool-size: " << m_pool.size() << std::endl;
}

mmt_gd::GameObject::Ptr mmt_gd::BulletPool::get()
{
    return m_pool[m_counter++ % m_pool.size()];
}
