#pragma once

enum class BunnyHopMode {
    None,
    Manual
};

class BunnyHop {
public:
    BunnyHop() noexcept;
    void RunBunnyHop(Entity* pLocalPlayer, DWORD* pForceJump) const noexcept;

    void SetInterval(std::chrono::milliseconds& interval) noexcept;
    std::chrono::milliseconds GetInterval() const noexcept;

    void SetMode(BunnyHopMode mode) noexcept;
    BunnyHopMode GetMode() const noexcept;

private:
    BunnyHopMode m_Mode;
    std::chrono::milliseconds m_Interval;
};

