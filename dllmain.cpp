
#define DEBUG_CONSOLE true

#include "framework.h"
#include "./src/game.sdk.h"

#include "src/manhunt/CPlayer.h"
#include "src/manhunt/CText.h"
#include "src/manhunt/CMainMenu.h"
#include "src/manhunt/CWeapons.h"
#include "src/manhunt/CVisual.h"    
#include "src/manhunt/CInput.h"    
#include "src/manhunt/CEntity.h"    

#include "./src/hooks.h"

#include <stdio.h>




void InitConsole()
{
#if DEBUG_CONSOLE 
    AllocConsole();

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

    SetConsoleTitleA("Manhunt Debug Console");

    //HWND hConsole = GetConsoleWindow();
    //ShowWindow(hConsole, SW_MINIMIZE);
#endif
}


void Test()
{
    DWORD p = *(DWORD*)0x82279C;

    if (!p)
        return;

    DWORD renderer = *(DWORD*)p;

    if (!renderer)
        return;


    DWORD func = 0x5F6E00;

    __asm
    {
        push dword ptr ds : [0x7CE214]
        push 1
        push dword ptr ds : [0x7CD23C]
        push dword ptr ds : [0x7CD54C]
        push dword ptr ds : [0x7CE144]
        push dword ptr ds : [0x7CE27C]
        push dword ptr ds : [0x7CC568]
        push dword ptr ds : [0x7CE280]

        call func
        add esp, 20h
    }
}

DWORD WINAPI KillAllHunters(LPVOID) {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);


    while (true) {
        __try
        {
            DWORD player = CPlayer::GetPlayerBase();
            if (!player) continue;

            Vector* pos = CEntity::GetEntityPosition(player);
            Vector* rot = CEntity::GetEntityRotation(player);
            
            Vector* boundmax = CEntity::GetEntityBoundingBoxMax(player);
            Vector* boundmin = CEntity::GetEntityBoundingBoxMin(player);


            char buffer[256];
            float lineHeight = 0.04f;
            float startY = 0.40f;



            if (GetAsyncKeyState(VK_DELETE) & 1)
            {
                __try
                {
                    Test();
                }
                __except (MyExceptionFilter(GetExceptionInformation()))
                {
                    printf("Exception: %08X\n", GetExceptionCode());
                }
            }


            // Posição
            //sprintf(buffer, "Pos: %.2f %.2f %.2f", pos->x, pos->y, pos->z);
            //CVisual::DrawString(CText::KeyEx(buffer), 0.58f, startY, 0.70f, 0.70f);

            /*
            // Rotação
            sprintf(buffer, "Rot: %.2f %.2f %.2f", rot->x, rot->y, rot->z);
            CVisual::DrawString(CText::KeyEx(buffer), 0.58f, startY + lineHeight, 0.70f, 0.70f);

            // Bounding Box Max
            sprintf(buffer, "Bound Max: %.2f %.2f %.2f", boundmax->x, boundmax->y, boundmax->z);
            CVisual::DrawString(CText::KeyEx(buffer), 0.58f, startY + lineHeight * 2, 0.70f, 0.70f);

            // Bounding Box Min
            sprintf(buffer, "Bound Min: %.2f %.2f %.2f", boundmin->x, boundmin->y, boundmin->z);
            CVisual::DrawString(CText::KeyEx(buffer), 0.58f, startY + lineHeight * 3, 0.70f, 0.70f);
            */


        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            continue;
        }
        Sleep(80);
    }
    return 1;
}


DWORD WINAPI MainThread(LPVOID) {
    InitConsole();
    InitHooks();

    // Dentro do seu MainThread ou onde quiser testar



    CreateThread(0, 0, KillAllHunters, 0, 0, 0);
    return 0;
}


BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD reason,
    LPVOID
)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);

        CreateThread(
            nullptr,
            0,
            MainThread,
            nullptr,
            0,

            nullptr
        );
    }
	if (reason == DLL_PROCESS_DETACH)
    {
        CInput::Shutdown();
    }

    return TRUE;
}