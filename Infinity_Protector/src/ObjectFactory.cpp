#include "stdafx.h"

#include "ObjectFactory.hpp"
#include "ColliderComponent.hpp"
#include "GameObjectEvents.hpp"
#include "PhysicsManager.hpp"
#include "PlayerMoveComponent.hpp"
#include "ObeliskHealthComponent.hpp" 
#include "PlayerShootComponent.hpp"
#include "SpriteRenderComponent.hpp"
#include "EnemieMovementComponent.hpp"
#include "Tileson.hpp"
#include "EnemyStateManager.hpp"
#include "AnimationComponent.hpp"
#include "GameObjectManager.hpp"
#include "EnemyShootComponent.hpp"
#include "HealthComponent.hpp"
#include "string" 
#include "AnimatedSprite.hpp"
#include "Animation.hpp" 

namespace mmt_gd
{
static GameObject::Ptr loadSprite(tson::Object&        object,
                                  const std::string&   layer,
                                  const fs::path&      resourcePath,
                                  const SpriteManager& spriteManager,
                                  bool                 addHealthComponent,
                                  bool                 isPlayer,
                                  bool                 isMeele)
{
    auto gameObject = GameObject::create(object.getName());

    gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));

    // Parse data from file
    sf::IntRect textureRect{};
    textureRect.width  = object.getSize().x;
    textureRect.height = object.getSize().y;

    fs::path spriteTexture;
    fs::path bulletTexture;
    auto     input     = false;
    auto     shoot     = false;
    auto     playerIdx = 0;
    auto enemyIdx = 1;
    auto enemie = false;
    auto player = false;


    for (const auto* property : object.getProperties().get())
    {
        if (auto name = property->getName(); name == "Texture")
        {
            spriteTexture = resourcePath / std::any_cast<std::string>(property->getValue());
        }
        else if (name == "BulletTexture")
        {
            bulletTexture = resourcePath / std::any_cast<std::string>(property->getValue());
        }
        else if (name == "TextureRectLeft")
        {
            textureRect.left = std::any_cast<int>(property->getValue());
        }
        else if (name == "TextureRectTop")
        {
            textureRect.top = std::any_cast<int>(property->getValue());
        }
        else if (name == "InputPlayerIdx")
        {
            input     = true;
            shoot     = true;
            player    = true;
            playerIdx = std::any_cast<int>(property->getValue());
        }
        else if (name == "InputEnemyIdx")
        {
            input    = false;
            enemie   = true;
            shoot    = false;
            enemyIdx = std::any_cast<int>(property->getValue());
        }

        else if (name == "Mass")
        {
            auto mass = std::any_cast<float>(property->getValue());
        }
    }


    if (addHealthComponent)
    {
        int health = 0;
        for (const auto* property : object.getProperties().get())
        {
            if (auto name = property->getName(); name == "Health")
            {
                health = std::any_cast<int>(property->getValue());
                break;
            }
        }
        gameObject->addComponent<HealthComponent>(*gameObject, health, isPlayer, isMeele);
      
    }

    
    if (spriteTexture.string().length() > 0)
    {
        const auto renderComp = gameObject->addComponent<SpriteRenderComponent>(*gameObject,
                                                                                spriteManager.getWindow(),
                                                                                spriteTexture.string(),
                                                                                layer);
        renderComp->getSprite().setTextureRect(textureRect);

        gameObject->addComponent<AnimationComponent>(*gameObject, playerIdx, textureRect, renderComp, isPlayer);
        if (isPlayer)
        {
            std::cout << " Are you a Player?" << std::endl;
        }
        //
        

        
    }
    if (shoot)
    {
        if (bulletTexture.string().length() > 0)
        {
            gameObject->addComponent<PlayerShootComponent>(*gameObject,
                                                           5,
                                                           spriteManager.getWindow(),
                                                           bulletTexture.string(),
                                                           textureRect,
                                                           sf::FloatRect{0, 0, 49, 22},
                                                           0.1F,
                                                           layer);
        }
    }
    const auto rigidComp = gameObject->addComponent<RigidBodyComponent>(*gameObject, b2_dynamicBody);
    rigidComp->getB2Body()->SetFixedRotation(true);

    b2PolygonShape polygonShape;
    const auto     size = PhysicsManager::t2b(object.getSize(), true);
    polygonShape.SetAsBox(size.x / 2, size.y / 2, b2Vec2{size.x / 2, size.y / 2}, 0);
    b2FixtureDef fixtureDef{};
    fixtureDef.shape   = &polygonShape;
    fixtureDef.density = 1; //TOdo load from tiled
    gameObject->addComponent<ColliderComponent>(*gameObject, *rigidComp, fixtureDef);  

    if (enemie)
    {
        gameObject->addComponent<EnemieMovementComponent>(*gameObject, *rigidComp, enemyIdx);
        gameObject->addComponent<EnemyShootComponent>(*gameObject,
                                                           5,
                                                           spriteManager.getWindow(),
                                                           bulletTexture.string(),
                                                           textureRect,
                                                           sf::FloatRect{0, 0, 49, 22},
                                                           0.1F,
                                                           layer,
                                                           enemyIdx);
    }
    if (input)
    {
        //gameObject->addComponent<HealthComponent>(*gameObject, playerh); 
        gameObject->addComponent<PlayerMoveComponent>(*gameObject, *rigidComp, playerIdx);
    }
    
    

    if (!gameObject->init())
    {
        sf::err() << "Could not initialize go " << gameObject->getId() << " in TileMap " << std::endl;
    }

    EventBus::getInstance().fireEvent(std::make_shared<GameObjectCreateEvent>(gameObject));

    return gameObject;
}

static GameObject::Ptr loadCollider(const tson::Object& object, const std::string& layer)
{
    auto gameObject = GameObject::create(object.getName());
    gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));

    const auto rigidComp = gameObject->addComponent<RigidBodyComponent>(*gameObject, b2_staticBody);

    b2PolygonShape polygonShape{};
    const auto     size = PhysicsManager::t2b(object.getSize());
    polygonShape.SetAsBox(size.x / 2, size.y / 2, b2Vec2{size.x / 2, size.y / 2}, 0);

    b2FixtureDef fixtureDef{};
    fixtureDef.shape = &polygonShape;

    gameObject->addComponent<ColliderComponent>(*gameObject, *rigidComp, fixtureDef);

    if (!gameObject->init())
    {
        sf::err() << "Could not initialize go " << gameObject->getId() << " in TileMap " << std::endl;
    }

    EventBus::getInstance().fireEvent(std::make_shared<GameObjectCreateEvent>(gameObject));

    return gameObject;
}

static GameObject::Ptr loadTrigger(const tson::Object& object, const std::string& layer)
{
    auto gameObject = GameObject::create(object.getName());
    gameObject->setPosition(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y));

    const auto rb = gameObject->addComponent<RigidBodyComponent>(*gameObject, b2_staticBody);

    b2PolygonShape polygonShape{};
    const auto     size = PhysicsManager::t2b(object.getSize());
    polygonShape.SetAsBox(size.x / 2, size.y / 2, b2Vec2{size.x / 2, size.y / 2}, 0);


    b2FixtureDef fixtureDef{};
    fixtureDef.shape    = &polygonShape;
    fixtureDef.isSensor = true;

    gameObject->addComponent<ColliderComponent>(*gameObject, *rb, fixtureDef);

    if (!gameObject->init())
    {
        sf::err() << "Could not initialize go " << gameObject->getId() << " in TileMap " << std::endl;
    }

    EventBus::getInstance().fireEvent(std::make_shared<GameObjectCreateEvent>(gameObject));

    return gameObject;
}
GameObject::Ptr ObjectFactory::processTsonObject(tson::Object& object,
                                                 const tson::Layer& layer,
                                                 const fs::path& path,
                                                 const SpriteManager& spriteManager)

{
    if (object.getType() == "Sprite")
    {
        bool addHealthComponent = false;
        for (const auto* property : object.getProperties().get())
        {
            if (auto name = property->getName(); name == "AddHealthComponent")
            {
                addHealthComponent = std::any_cast<bool>(property->getValue());
            }
        }

        bool isPlayer = false;
        for (const auto* property : object.getProperties().get())
        {
            if (auto name = property->getName(); name == "IsPlayer")
            {
                isPlayer = std::any_cast<bool>(property->getValue());
            }
        }
        bool isMeele = false;
        for (const auto* property : object.getProperties().get())
        {
            if (auto name = property->getName(); name == "IsMeele")
            {
                isMeele = std::any_cast<bool>(property->getValue());
            }
        }
        auto sprite = loadSprite(object, layer.getName(), path, spriteManager, addHealthComponent, isPlayer, isMeele);
    }
    if (object.getType() == "Collider")
    {
        auto collider = loadCollider(object, layer.getName());
    }
    if (object.getType() == "Trigger")
    {
        auto trigger = loadTrigger(object, layer.getName());
    }
    return {};
}
} // namespace mmt_gd
