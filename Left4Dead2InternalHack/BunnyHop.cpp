#include "pch.h"
#include "BunnyHop.h"

BunnyHop::BunnyHop() noexcept 
    : m_Mode(BunnyHopMode::None),
    m_Interval(std::chrono::milliseconds(1))
{
}

void BunnyHop::RunBunnyHop(Entity* pLocalPlayer, DWORD* pForceJump) const noexcept
{
    // Skip if off
    if (m_Mode == BunnyHopMode::None) return;

    // Validate pointers
    if (pLocalPlayer && pForceJump)
    {
        // Check player state
        if (pLocalPlayer->iFlags == 129)
        {
            if (m_Mode == BunnyHopMode::Manual && GetAsyncKeyState(VK_SPACE))
            {
                *pForceJump = 4;
                std::this_thread::sleep_for(m_Interval);

                *pForceJump = 5;
                std::this_thread::sleep_for(m_Interval);

                *pForceJump = 4;
            }
        }
    }
}

void BunnyHop::SetInterval(std::chrono::milliseconds& interval) noexcept
{
    m_Interval = interval;
}

std::chrono::milliseconds BunnyHop::GetInterval() const noexcept
{
    return m_Interval;
}

void BunnyHop::SetMode(BunnyHopMode mode) noexcept
{
    m_Mode = mode;
}

BunnyHopMode BunnyHop::GetMode() const noexcept
{
    return m_Mode;
}
