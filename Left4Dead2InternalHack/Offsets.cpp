#include "pch.h"
#include "Offsets.h"

void Offsets::UpdateOffsets()
{
    // Update module addresses
    uClient = (uintptr_t)GetModuleHandle("client.dll");
    uEngine = (uintptr_t)GetModuleHandle("engine.dll");

    // Update entity list
    pEntityList = (EntityList*)(uClient + 0x7384E0);

    // Update local player
    if (pEntityList) pLocalPlayer = pEntityList->arr[0].pEntity;

    // Update force jump
    pForceJump = (DWORD*)(uClient + 0x757DF0);

    // Update attack1
    pAttack1 = (DWORD*)(uClient + 0x757EC8);

    // Update view angles
    pViewAngles = (Vector3*)(*(uintptr_t*)(uEngine + 0x004268EC) + 0x4AAC);
}
