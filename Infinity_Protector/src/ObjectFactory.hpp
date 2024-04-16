#pragma once
#include "GameObject.hpp"
#include "SpriteManager.hpp"
#include "GameObjectManager.hpp" 
#include "ColliderComponent.hpp"
#include "Tileson.hpp"

namespace tson
{
class Object;
}

namespace mmt_gd
{
enum class BulletType
{
    Player,
    Enemy
};

class ObjectFactory
{
public:
    static GameObject::Ptr processTsonObject(tson::Object&        object,
                                             const tson::Layer&   layer,
                                             const fs::path&      path,
                                             const SpriteManager& spriteManager);

private:

};
} //namespace mmt_gd
