#include "CGame.h"
#include "CPlayer.h"
#include "CVisual.h"
#include "CText.h"

DWORD gRenderer;

namespace CGame
{
    typedef int (*tOriginalEventHandler)(int a1, int a2);
    tOriginalEventHandler oEventHandler = nullptr;
    SafetyHookInline g_EventHandlerHook;

    // --------------------------------------------------------------------------

    void InitialiseWorld(int missionId)
    {
        Call<0x474330, int>(missionId);
    }

    // --------------------------------------------------------------------------

	// hkEventHandler é chamado apenas quando está no menu ou cutscenes.
    int __cdecl hkEventHandler(int a1, int a2)
    {
        /*
        __try
        {
            CVisual::DrawString(L"Manhunt Hooked!", 10.0f, 10.0f, 255, 1);
        }
        __except (EXCEPTION_SDK)
        {
        }

        __try
        {
            int logoTexture = CVisual::LoadTexture(*(int*)0x7C8704, "logo");
            float logoScale = *(float*)0x7D3458 * *(float*)0x7D63FC;
            CVisual::DrawImage(*(float*)0x7D6408, *(float*)0x7D6404, logoScale, *(float*)0x7D6400, 180, 180, 180, 255, logoTexture);
        }
        __except (EXCEPTION_SDK)
        {
        }
        */

        // ----------------------------------------------------------------------

        int ret = oEventHandler(a1, a2);
        return ret;
    }

    void InstallHook()
    {
        g_EventHandlerHook = safetyhook::create_inline((void*)0x5EF900, (void*)&hkEventHandler);
        oEventHandler =
            g_EventHandlerHook.original<tOriginalEventHandler>();


        // ------------------------------------------------------

        while (true)
        {
            DWORD p = *(DWORD*)0x82279C;
            if (!p)
            {
                printf("\r[CGame::InstallHook] Waiting for renderer...\n");
                Sleep(1000);
                continue;
            }

            gRenderer = *(DWORD*)p;
            if (gRenderer) break;
        }

        printf("[CGame::InstallHook] Renderer = 0x%08X\n", gRenderer);
    }
}