#pragma once

enum class AutoShootMode {
    None,
    Manual
};

class AutoShoot {
public:
    AutoShoot();
    void RunAutoShoot(DWORD* pAction1) const noexcept;

    void SetInterval(const std::chrono::milliseconds& interval) noexcept;
    std::chrono::milliseconds GetInterval() const noexcept;

    void SetMode(AutoShootMode mode) noexcept;
    AutoShootMode GetMode() const noexcept;

private:
    AutoShootMode m_Mode;
    std::chrono::milliseconds m_Interval;
};

