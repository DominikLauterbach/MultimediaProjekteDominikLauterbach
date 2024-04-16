#include "stdafx.h"
#include "ObjectFactory.hpp"
#include "GameObject.hpp"
#include "EnemyStateManager.hpp"

#include <vector>
#include <iostream>

  namespace mmt_gd
{

  EnemyStateManager::EnemyStateManager() : currentState(EnemyState::Patrol)
  {
    patrolPoints = {
        {64.f, 130.17}, 
        {166.f, 139.f}, 
        {300.f, 300.f}, 
        {400.f, 400.f}, 
        {500.f, 500.f}
    };
  }
  EnemyStateManager::~EnemyStateManager()
  {}

void EnemyStateManager::updateEnemyState(GameObject::Ptr enemy)
  {
    /*std::cout << "p" << std::endl;*/
      switch (currentState)
      {
          case EnemyState::Patrol:
              patrolState(enemy);
              break;
          case EnemyState::AttackPlayer:
              attackPlayerState(enemy);
              break;
          case EnemyState::FleePlayer:
              fleePlayerState(enemy);
              break;
      }
  }

void EnemyStateManager::patrolState(GameObject::Ptr enemy)
  {
      std::cout << "patrolState" << std::endl;
      sf::Vector2f moveDirection = calculateMove(enemy);
      enemy->move(moveDirection);
  }

  void EnemyStateManager::attackPlayerState(GameObject::Ptr enemy)
  {
      std::cout << "attackPlayerState" << std::endl;
  }

  void EnemyStateManager::fleePlayerState(GameObject::Ptr enemy)
  {
      std::cout << "fleePlayerState" << std::endl;
  }

  sf::Vector2f EnemyStateManager::calculateMove(GameObject::Ptr enemy)
  {
      if (patrolPoints.empty())
      {
          return sf::Vector2f(0.0f, 0.0f);
      }

      const sf::Vector2f& targetPoint = patrolPoints[0];
      sf::Vector2f direction = targetPoint - enemy->getPosition();
      float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
      if (distance > 0.0f)
      {
          direction /= distance;
      }

      
      const float  speed = 2.0f; 
      sf::Vector2f move  = direction * speed;

      const float thresholdDistance = 5.0f; 
      if (distance < thresholdDistance)
      {
          patrolPoints.erase(patrolPoints.begin());
          std::rotate(patrolPoints.begin(), patrolPoints.begin() + 1, patrolPoints.end());
      }

      return move;
  }


} // namespace mmt_gd