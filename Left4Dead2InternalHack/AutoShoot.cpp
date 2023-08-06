#include "pch.h"
#include "AutoShoot.h"

AutoShoot::AutoShoot() 
    : m_Mode(AutoShootMode::None), m_Interval(1)
{
}

void AutoShoot::RunAutoShoot(DWORD* pAction1) const noexcept
{
    if (m_Mode == AutoShootMode::None) return;

    if (pAction1)
    {
        if (m_Mode == AutoShootMode::Manual && GetAsyncKeyState(VK_MENU))
        {
            *pAction1 = 4;
            std::this_thread::sleep_for(m_Interval);

            *pAction1 = 5;
            std::this_thread::sleep_for(m_Interval);

            *pAction1 = 4;
        }
    }
}

void AutoShoot::SetInterval(const std::chrono::milliseconds& interval) noexcept
{
    m_Interval = interval;
}

std::chrono::milliseconds AutoShoot::GetInterval() const noexcept
{
    return m_Interval;
}

void AutoShoot::SetMode(AutoShootMode mode) noexcept
{
    m_Mode = mode;
}

AutoShootMode AutoShoot::GetMode() const noexcept
{
    return m_Mode;
}
