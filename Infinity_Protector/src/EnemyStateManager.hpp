#pragma once

#include "stdafx.h"
#include "GameObject.hpp"

namespace mmt_gd
{

class EnemyStateManager
{
public:
    enum class EnemyState
    {
        Patrol,
        AttackPlayer,
        FleePlayer
    };

    EnemyStateManager();
    ~EnemyStateManager();

    void updateEnemyState(GameObject::Ptr enemy);

    private:
        EnemyState currentState;
        std::vector<sf::Vector2f> patrolPoints; 

        void patrolState(GameObject::Ptr enemy);
        void attackPlayerState(GameObject::Ptr enemy);
        void fleePlayerState(GameObject::Ptr enemy);

        sf::Vector2f calculateMove(GameObject::Ptr enemy);
};


} // namespace mmt_gd
