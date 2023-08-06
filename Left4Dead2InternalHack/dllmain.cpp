#include "pch.h"
#include "Offsets.h"
#include "Aimbot.h"
#include "AutoShoot.h"
#include "BunnyHop.h"



void Menu(AimbotMode aimbotMode, AutoShootMode autoShootMode, BunnyHopMode bunnyHopMode)
{
    system("cls");

    switch(aimbotMode)
    {
    case AimbotMode::None:
        printf("[F1] Aimbot > None <\n");
        break;
    case AimbotMode::Distance:
        printf("[F1] Aimbot > Distance <\n");
        break;
    case AimbotMode::FOV:
        printf("[F1] Aimbot > FOV <\n");
        break;
    case AimbotMode::Mixed:
        printf("[F1] Aimbot > Mixed <\n");
        break;
    }

    switch(autoShootMode)
    {
    case AutoShootMode::None:
        printf("[F2] Autoshoot > None <\n");
        break;
    case AutoShootMode::Manual:
        printf("[F2] Autoshoot > Manual <\n");
        break;
    }

    switch(bunnyHopMode)
    {
    case BunnyHopMode::None:
        printf("[F3] BunnyHop > None <\n");
        break;
    case BunnyHopMode::Manual:
        printf("[F3] BunnyHop > Manual <\n");
        break;
    }
}



DWORD WINAPI StartThread(HMODULE hModule)
{
    FILE* f;
    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);

    Offsets offsets{};
    Aimbot aimbot{};
    AutoShoot autoShoot{};
    BunnyHop bunnyHop{};

    Menu(aimbot.GetMode(), autoShoot.GetMode(), bunnyHop.GetMode());
    while (!GetAsyncKeyState(VK_INSERT))
    {
        // Toggle aimbot
        if (GetAsyncKeyState(VK_F1))
        {
            switch (aimbot.GetMode())
            {
            case AimbotMode::None:
                aimbot.SetMode(AimbotMode::Distance);
                break;
            case AimbotMode::Distance:
                aimbot.SetMode(AimbotMode::FOV);
                break;
            case AimbotMode::FOV:
                aimbot.SetMode(AimbotMode::Mixed);
                break;
            case AimbotMode::Mixed:
                aimbot.SetMode(AimbotMode::None);
                break;
            }
            Menu(aimbot.GetMode(), autoShoot.GetMode(), bunnyHop.GetMode());
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }

        // Toggle autoshoot
        if (GetAsyncKeyState(VK_F2))
        {
            switch (autoShoot.GetMode())
            {
            case AutoShootMode::None:
                autoShoot.SetMode(AutoShootMode::Manual);
                break;
            case AutoShootMode::Manual:
                autoShoot.SetMode(AutoShootMode::None);
                break;
            }
            Menu(aimbot.GetMode(), autoShoot.GetMode(), bunnyHop.GetMode());
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }

        // Toggle bunnyhop
        if (GetAsyncKeyState(VK_F3))
        {
            switch (bunnyHop.GetMode())
            {
            case BunnyHopMode::None:
                bunnyHop.SetMode(BunnyHopMode::Manual);
                break;
            case BunnyHopMode::Manual:
                bunnyHop.SetMode(BunnyHopMode::None);
                break;
            }
            Menu(aimbot.GetMode(), autoShoot.GetMode(), bunnyHop.GetMode());
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        
        // Use SEH to catch nullptr exceptions(prevent game crash)
        __try
        {
            offsets.UpdateOffsets();
            aimbot.RunAimbot(offsets.pEntityList, offsets.pLocalPlayer, offsets.pViewAngles);
            autoShoot.RunAutoShoot(offsets.pAttack1);
            bunnyHop.RunBunnyHop(offsets.pLocalPlayer, offsets.pForceJump);
        }
        __except(GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION)
        {
            // Handle exception
            printf("EXCEPTION_ACCESS_VIOLATION\n");
        }
    }
    
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(
            CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)StartThread, hModule, 0, nullptr)
        );
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

