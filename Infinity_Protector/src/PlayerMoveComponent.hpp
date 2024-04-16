#pragma once

#include "IComponent.hpp"
#include "RigidBodyComponent.hpp"

namespace mmt_gd
{

class PlayerMoveComponent : public IComponent
{
public:
    using ptr = std::shared_ptr<PlayerMoveComponent>;

    PlayerMoveComponent(GameObject& gameObject, RigidBodyComponent& rigidBody, int playerIndex);

    bool init() override;
    void update(float deltaTime) override;

private:
    int m_playerIndex;
    //void                AnimamtionFunction();
    RigidBodyComponent& m_rigidBody;
    //Animation*          m_currentAnimation;
};
} // namespace mmt_gd
