#pragma once

enum class AimbotMode {
    None,
    Distance,
    FOV,
    Mixed
};

class Aimbot {
public:
    Aimbot();
    void RunAimbot(EntityList* pEntityList, Entity* pLocalPlayer, Vector3* pViewAngles) const noexcept;

    void SetMode(AimbotMode mode) noexcept;
    AimbotMode GetMode() const noexcept;

    void SetAimbotDistance(float minDistance = 0.0f, float maxDistance = FLT_MAX) noexcept;
    void SetAimbotFOV(float deltaPitch = FLT_MAX, float deltaYaw = FLT_MAX) noexcept;

    static float GetDistance(const Vector3& src, const Vector3& dst) noexcept;
    static float GetPitch(const Vector3& src, const Vector3& dst, float hyp) noexcept;
    static float GetYaw(const Vector3& src, const Vector3& dst, float hyp) noexcept;

private:
    AimbotMode m_Mode;
    float m_MinDistance, m_MaxDistance;
    float m_DeltaPitch, m_DeltaYaw;
};

