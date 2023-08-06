#pragma once
struct Offsets {
    // Functions
    void UpdateOffsets();

    // Modules
    uintptr_t uClient;
    uintptr_t uEngine;

    // Game
    EntityList* pEntityList;
    Entity* pLocalPlayer;
    DWORD* pForceJump;
    DWORD* pAttack1;
    Vector3* pViewAngles;
};