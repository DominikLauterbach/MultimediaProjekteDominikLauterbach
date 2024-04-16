#include "stdafx.h"

#include "GameObjectManager.hpp"

#include "Debug.hpp"
#include "GameObjectEvents.hpp"

namespace mmt_gd
{
void GameObjectManager::init()
{
    PROFILE_FUNCTION();

    Instrumentor::instance().beginSession("runtime", "runtime.json");
    // subscribe to creation events
    {
        const EventBus::ListenerId
            id = EventBus::getInstance()
                     .addListener(GameObjectCreateEvent::Type,
                                  [this](const IEvent::Ptr& event)
                                  {
                                      const auto goCreateEvent = std::static_pointer_cast<GameObjectCreateEvent>(event);
                                      this->addGameObject(goCreateEvent->getData());
                                  });
        m_listeners.push_back(id);
    }
}

void GameObjectManager::shutdown()
{
    PROFILE_FUNCTION();

    Instrumentor::instance().endSession();
    m_gameObjects.clear();

    // unsubscribe from events
    for (const auto& listener : m_listeners)
    {
        EventBus::getInstance().removeListener(listener);
    }
    m_listeners.clear();
}

void GameObjectManager::update(const float deltaTime)
{
    PROFILE_FUNCTION();

    std::vector<GameObject::Ptr> gameObjectsToDelete{};

    for (const auto& goPair : getGameObjects())
    {
        if (goPair.second->isMarkedForDelete())
        {
            gameObjectsToDelete.push_back(goPair.second);
        }
        else if (goPair.second->isActive())
        {
            goPair.second->update(deltaTime);
        }
    }
    for (const auto& go : gameObjectsToDelete)
    {
        removeGameObject(go);
    }
}

void GameObjectManager::addGameObject(const GameObject::Ptr& gameObject)
{
    PROFILE_FUNCTION();

    ffAssertMsg(m_gameObjects.find(gameObject->getId()) == m_gameObjects.end(),
                "Game object with this m_id already exists " + gameObject->getId())

        m_gameObjects[gameObject->getId()] = gameObject;
}

GameObject::Ptr GameObjectManager::getGameObject(const std::string& id) const
{
    PROFILE_FUNCTION();

    const auto it = m_gameObjects.find(id);
    if (it == m_gameObjects.end())
    {
        ffErrorMsg("Could not find gameobject with m_id " + id) return nullptr;
    }
    return it->second;
}

void GameObjectManager::removeGameObject(const std::shared_ptr<GameObject>& go)
{
    PROFILE_FUNCTION();

    if (m_gameObjects.find(go->getId()) != m_gameObjects.end())
    {
        m_gameObjects.erase(go->getId());
    }
}
} // namespace mmt_gd
