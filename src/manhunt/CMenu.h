// CustomMenu.h
#pragma once

#include "../../framework.h"



enum MENU_ITEM
{
    MENU_ITEM_RESUME = 0,
    MENU_ITEM_LOAD = 1,
    MENU_ITEM_SAVE = 2,
    MENU_ITEM_OPTIONS = 3,
    MENU_ITEM_CONTROLS = 4,
    MENU_ITEM_AUDIO = 5,
    MENU_ITEM_VIDEO = 6,
    MENU_ITEM_QUIT = 7,
    MENU_ITEM_CHEATS = 8,
    MENU_ITEM_MAX = 9,
    MENU_ITEM_CONFIG = 10
};

enum MENU_STATE
{
    MENU_STATE_IDLE = 0,
    MENU_STATE_ACTIVE = 3,
    MENU_STATE_LOADING = 8
};

enum SUBMENU_ID
{
    SUBMENU_MAIN = 25,
    SUBMENU_OPTIONS = 30,
    SUBMENU_CONTROLS = 33,
    SUBMENU_AUDIO = 19,
    SUBMENU_LOAD_GAME = 39,
    SUBMENU_SAVE_GAME = 27,
    SUBMENU_CHEATS = 50  // Novo submenu para cheats
};

enum CHEAT_FLAGS
{
    CHEAT_RUN = 1 << 0,   // 1
    CHEAT_SILENT = 1 << 1,   // 2
    CHEAT_REGEN = 1 << 2,   // 4
    CHEAT_HELI = 1 << 3,   // 8
    CHEAT_FULEQ = 1 << 4,   // 16
    CHEAT_SUPUN = 1 << 5,   // 32
    CHEAT_RABBI = 1 << 6,   // 64
    CHEAT_MONKEY = 1 << 7,   // 128
    CHEAT_INVIS = 1 << 8,   // 256
    CHEAT_PIGGS = 1 << 9,   // 512
    CHEAT_GOD = 1 << 10   // 1024
};

#define PAUSE_MENU_ADDR 0x5FFB50
#define DRAW_TEXT_ADDR 0x5D7EC0
#define CPLAYER_PTR 0x715B9C
#define ADDR_BAT_COUNT 0x8204A4
#define ADDR_KNIFE_COUNT 0x8204AC
#define ADDR_BAG_COUNT 0x8204A8

typedef signed int(__thiscall* tPauseMenuControl)(void* pThis);
typedef void(__thiscall* tDrawText)(void* text1, void* text2, void* text3, int a, int b);

extern tPauseMenuControl oPauseMenuControl;
extern tDrawText oDrawText;
extern SafetyHookInline g_PauseMenuHook;
extern SafetyHookInline g_DrawTextHook;


extern int currentSelection;
extern bool customMenuActive;

signed int __fastcall hkPauseMenuControl(void* pThis, void*);
void __fastcall hkDrawText(void* text1, void* text2, void* text3, int a, int b);


namespace CMenu
{
    int IsMenuLocked();
    void InstallHook();
};

/*

#pragma pack(push, 1)
struct SaveLoadMenu
{
    // Slot de save individual
    struct SaveSlot
    {
        char szSlotName[32];            // 0x00 - Nome do slot
        DWORD dwSaveData[56];           // 0x20 - Dados do save (224 bytes)
    };  // Total: 256 bytes por slot

    SaveSlot aSaveSlots[8];             // 0x000 - 8 slots (2048 bytes)

    // Estado do menu
    int nSelectedIndex;                 // 0x800 - Índice selecionado (0-7)
    int nPadding1[9];                   // 0x804 - Espaço reservado
    int nMaxSlots;                      // 0x828 - Máximo de slots (7)
    int nPadding2[2];                   // 0x82C - Espaço reservado
    int nSelectedAction;                // 0x834 - Ação selecionada (3=Load)

    // Status
    bool bIsActive;                     // 0x8B8 - Menu está visível/ativo
    float fBackgroundPos;               // 0x8BC - Posição do fundo
    DWORD dwConfigFlags;                // 0x8C0 - Flags de configuração

};  // Tamanho total: ~0x8C4 bytes
#pragma pack(pop)

inline SaveLoadMenu* GetSaveLoadMenu()
{
    return (SaveLoadMenu*)0x7C87CC;
}

// Uso
SaveLoadMenu* pMenu = GetSaveLoadMenu();
pMenu->nSelectedIndex = 2;  // Seleciona o terceiro slot

*/