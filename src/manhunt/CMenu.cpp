#include "CMenu.h"

#define PAUSE_MENU_ADDR 0x5FFB50
#define DRAW_TEXT_ADDR 0x5D7EC0

typedef signed int(__thiscall* tPauseMenuControl)(void* pThis);
typedef void(__thiscall* tDrawText)(void* text1, void* text2, void* text3, int a, int b);
tDrawText oDrawText = nullptr;

tPauseMenuControl oPauseMenuControl = nullptr;
SafetyHookInline g_PauseMenuHook;

int currentSelection = 0;
bool customMenuActive = false;


namespace CMenu
{
    int IsMenuLocked()
    {
        int& dword_7C8758 = *reinterpret_cast<int*>(0x7C8758);
        return dword_7C8758;
	}

    void InstallHook()
    {
        /*
        oPauseMenuControl = (tPauseMenuControl)PAUSE_MENU_ADDR;
        g_PauseMenuHook = safetyhook::create_inline(
            (void*)PAUSE_MENU_ADDR,
            (void*)hkPauseMenuControl
        );
        oPauseMenuControl =
            g_PauseMenuHook.original<tPauseMenuControl>();
        */
    }
}

/*

signed int __fastcall hkPauseMenuControl(void* pThis, void*)
{
    int* pSelectedItem = (int*)0x7C8A68;

    if (*pSelectedItem == 3) // quit
    {
        *pSelectedItem = 0;
    }
}

*/


signed int __fastcall hkPauseMenuControl(void* pThis, void*)
{
    /*
    int* pSelectedItem = (int*)0x7C8A68;

    if (*pSelectedItem == 3) // quit
    {
        *pSelectedItem = 0; 
    }
    */
    return oPauseMenuControl(pThis);
}

