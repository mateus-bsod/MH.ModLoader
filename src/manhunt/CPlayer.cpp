
#include "CPlayer.h"

int& Player_State = *reinterpret_cast<int*>(0x7D34F8); // dword_7D34F8

//

namespace CPlayer
{
    void SetPlayerCameraMode(CAMERA_MODE mode)
    {
        int& gCameraMode = *reinterpret_cast<int*>(0x715BB0);
        int& gCameraMode2 = *reinterpret_cast<int*>(0x715BB4);

        switch (mode)
        {
        case CAMERA_MODE_FIRST_PERSON:
            gCameraMode = 0;
            gCameraMode2 = 0;
            break;

        case CAMERA_MODE_FLYMODE:
            gCameraMode = 1;
            gCameraMode2 = 0;
            break;

        case CAMERA_MODE_THIRD_PERSON:
            gCameraMode = 1;
            gCameraMode2 = 1;
            break;
        }
    }

    CAMERA_MODE GetPlayerCameraMode()
    {
        int& gCameraMode = *reinterpret_cast<int*>(0x715BB0);
        int& gCameraMode2 = *reinterpret_cast<int*>(0x715BB4);

        if (!gCameraMode && !gCameraMode2) return CAMERA_MODE_FIRST_PERSON;
        else if (gCameraMode && !gCameraMode2) return CAMERA_MODE_FLYMODE;
        else if (gCameraMode && gCameraMode2) return CAMERA_MODE_THIRD_PERSON;
        return CAMERA_MODE_INVALID;
    }

    //

    PLAYER_STATE GetPlayerState() {

        switch (Player_State) {
            case 0: return PLAYER_MENU;
            case 1: return PLAYER_CUTSCENE;
            case 2: return PLAYER_INGAME;
        }
        return PLAYER_INVALID;
    }

    void SetPlayerFogColor(DWORD color)
    {
        DWORD& gFogColor = *reinterpret_cast<DWORD*>(0x715BB8);
        gFogColor = color;
	}

    DWORD GetPlayerFogColor()
    {
        DWORD& gFogColor = *reinterpret_cast<DWORD*>(0x715BB8);
        return gFogColor;
	}

    DWORD GetPlayerBase() 
    {
        __try {
            return *(DWORD*)0x715B9C;
        }
        __except (1) {
            printf("[CRASH] GetPlayerBase");
            return 0;
        }
    }

    /*
    int GetPlayerBase()
    {
        DWORD addr = *(DWORD*)0x715B9C;
        if (!addr) return 0;
		return addr;
    }
    */

    Player* GetPlayer()
    {
        DWORD addr = *(DWORD*)0x715B9C;
        if (!addr) return nullptr;

        return (Player*)addr;
    }


    void TogglePlayerHud(bool toggle)
    {
        DWORD& gPlayerHud = *reinterpret_cast<DWORD*>(0x7CF0A0);
		gPlayerHud = toggle ? 1 : 0;
    }

    bool IsPlayerHudEnabled()
    {
        DWORD& gPlayerHud = *reinterpret_cast<DWORD*>(0x7CF0A0);
		return gPlayerHud != 0;
    }

    void SetMenu(int menu)
    {
		Call<0x5D7A40, int>(menu);
    }

    void AccumulateTime()
    {
        __try {
            void* pPlayer = *(void**)0x715B9C;
            if (!pPlayer) return;

            DWORD funcAddr = 0x45BB10;

            __asm {
                mov ecx, pPlayer
                call funcAddr
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
    }

    void InstallHook()
    {
    }

}


