#include "stdafx.h"

#include "GameStateManager.hpp"

#include "Debug.hpp"
#include "GameState.hpp"

#include <utility>

namespace mmt_gd
{
void GameStateManager::registerState(const std::string& name, GameState::Ptr state)
{
    PROFILE_FUNCTION();

    m_states[name] = std::move(state);
}

void GameStateManager::setState(const std::string& stateName)
{
    PROFILE_FUNCTION();

    GameState* state = findState(stateName);
    ffAssertMsg(state != nullptr, "State could not be found")

        m_futureState = state;
}

void GameStateManager::changeState(GameState* stateName)
{
    PROFILE_FUNCTION();

    if (stateName != m_currentState)
    {
        if (m_currentState != nullptr)
        {
            m_currentState->exit();
        }

        m_currentState = stateName;

        if (m_currentState != nullptr)
        {
            m_currentState->init();
        }
    }
}

void GameStateManager::update(float deltaTime)
{
    PROFILE_FUNCTION();

    if (m_futureState != nullptr)
    {
        changeState(m_futureState);
        m_futureState = nullptr;
    }

    if (m_currentState != nullptr)
    {
        m_currentState->update(deltaTime);
    }
}

void GameStateManager::draw() const
{
    PROFILE_FUNCTION();

    if (m_currentState != nullptr)
    {
        m_currentState->draw();
    }
}

void GameStateManager::shutdown() const
{
    PROFILE_FUNCTION();

    if (m_currentState != nullptr)
    {
        m_currentState->exit();
    }
}

GameState* GameStateManager::getState() const
{
    PROFILE_FUNCTION();

    return m_currentState;
}

GameState* GameStateManager::findState(const std::string& stateName)
{
    PROFILE_FUNCTION();

    const auto state = m_states.find(stateName);
    if (state != m_states.end())
    {
        return state->second.get();
    }
    return nullptr;
}
} // namespace mmt_gd
