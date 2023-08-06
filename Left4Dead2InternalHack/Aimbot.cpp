#include "pch.h"
#include "AutoShoot.h"
#include "Aimbot.h"

Aimbot::Aimbot()
    : m_Mode(AimbotMode::None),
    m_MinDistance(0.0f), m_MaxDistance(FLT_MAX),
    m_DeltaPitch(360.0f), m_DeltaYaw(360.0f)
{
}

void Aimbot::RunAimbot(EntityList* pEntityList, Entity* pLocalPlayer, Vector3* pViewAngles) const noexcept
{
    // Early return if aimbot is off
    if (m_Mode == AimbotMode::None) return;
    
    // Validate pointers
    if (pEntityList && pLocalPlayer && pViewAngles)
    {
        // Store results
        Entity* pClosestEntity = nullptr;
        float fClosestDistance = FLT_MAX;
        float fSmallestPitch = 360.0f;
        float fSmallestYaw = 360.0f;

        // Iterate over entity list half list to remote useless iterations
        // List contains objects such as windows, guns, breakables, etc...
        for (uint16_t i = 5; i < ENTITY_LIST_SIZE/2; i++)
        {
            Entity* pEntity = pEntityList->arr[i].pEntity;

            if (pEntity && pEntity->iTeam == 3 && pEntity->iAlive && pEntity->pBoneMatrix)
            {
                // Set gun origin and target entity bone
                Vector3 vec3OriginGun = pLocalPlayer->vec3Origin + pLocalPlayer->vec3OriginOffset;
                Vector3 vec3TargetBone = Vector3{
                    pEntity->pBoneMatrix->arr[14].x,
                    pEntity->pBoneMatrix->arr[14].y,
                    pEntity->pBoneMatrix->arr[14].z
                };

                // Get distance, pitch, and yaw
                float fCurrentDistance = Aimbot::GetDistance(vec3OriginGun, vec3TargetBone);
                float fCurrentPitch = Aimbot::GetPitch(vec3OriginGun, vec3TargetBone, fCurrentDistance);
                float fCurrentYaw = Aimbot::GetYaw(vec3OriginGun, vec3TargetBone, fCurrentDistance);

                // Convert negative angles to positive
                float fLocalYaw = (pViewAngles->y < 0.0f) ? pViewAngles->y + 360.0f : pViewAngles->y;
                fCurrentYaw = (fCurrentYaw < 0.0f) ? fCurrentYaw + 360.0f : fCurrentYaw;

                // Get delta angles
                float deltaPitch = fCurrentPitch - pViewAngles->x;
                float deltaYaw = fCurrentYaw - fLocalYaw;

                // Check aimbot mode
                if (m_Mode == AimbotMode::Distance)
                {
                    // Sort by closest distance
                    if (fCurrentDistance < fClosestDistance)
                    {
                        fClosestDistance = fCurrentDistance;
                        pClosestEntity = pEntityList->arr[i].pEntity;
                    }
                }
                else if (m_Mode == AimbotMode::FOV)
                {
                    // Sort by smallest delta angle
                    if (sqrt(deltaPitch * deltaPitch + deltaYaw * deltaYaw) <
                        sqrt(fSmallestPitch * fSmallestPitch + fSmallestYaw * fSmallestYaw))
                    {
                        pClosestEntity = pEntityList->arr[i].pEntity;
                        fSmallestPitch = deltaPitch;
                        fSmallestYaw = deltaYaw;
                    }

                }
                else if (m_Mode == AimbotMode::Mixed)
                {
                    // Sort by closest distance but must be within deltaAngles and deltaDistance
                    if (fCurrentDistance < fClosestDistance &&
                        deltaPitch < m_DeltaPitch &&
                        deltaYaw < m_DeltaYaw &&
                        fCurrentDistance < m_MaxDistance &&
                        fCurrentDistance > m_MinDistance)
                    {
                        pClosestEntity = pEntityList->arr[i].pEntity;
                        fClosestDistance = fCurrentDistance;
                    }
                }
            }
        }

        // Re-calculate angles
        if (pLocalPlayer && pViewAngles && pClosestEntity && pClosestEntity->pBoneMatrix)
        {
            // Set gun origin and target entity bone
            Vector3 vec3OriginGun = pLocalPlayer->vec3Origin + pLocalPlayer->vec3OriginOffset;
            Vector3 vec3TargetBone = Vector3(
                pClosestEntity->pBoneMatrix->arr[14].x,
                pClosestEntity->pBoneMatrix->arr[14].y,
                pClosestEntity->pBoneMatrix->arr[14].z
            );

            // Set view angles
            if (GetAsyncKeyState(VK_MENU))
            {
                float distance = Aimbot::GetDistance(vec3OriginGun, vec3TargetBone);
                pViewAngles->x = Aimbot::GetPitch(vec3OriginGun, vec3TargetBone, distance);
                pViewAngles->y = Aimbot::GetYaw(vec3OriginGun, vec3TargetBone, distance);
            }
        }
    }
}

void Aimbot::SetMode(AimbotMode mode) noexcept
{
    m_Mode = mode;
}

AimbotMode Aimbot::GetMode() const noexcept
{
    return m_Mode;
}

void Aimbot::SetAimbotDistance(float minDistance, float maxDistance) noexcept
{
    m_MinDistance = minDistance;
    m_MaxDistance = maxDistance;
}

void Aimbot::SetAimbotFOV(float deltaPitch, float deltaYaw ) noexcept
{
    m_DeltaPitch = deltaPitch;
    m_DeltaYaw = deltaYaw;
}

float Aimbot::GetDistance(const Vector3& src, const Vector3& dst) noexcept
{
    return sqrt(
        (dst.x - src.x) * (dst.x - src.x) + (dst.y - src.y) * (dst.y - src.y) + (dst.z - src.z) * (dst.z - src.z)
    );
}

float Aimbot::GetPitch(const Vector3& src, const Vector3& dst, float hyp) noexcept
{
    return -asin(((dst.z - src.z) / hyp)) * 180 / PI;
}

float Aimbot::GetYaw(const Vector3& src, const Vector3& dst, float hyp) noexcept
{
    return atan2(dst.y - src.y, dst.x - src.x) * 180 / PI;
}
