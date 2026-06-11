// CVisual.cpp
#include "CVisual.h"
#include "CInput.h"
#include "CMainMenu.h"

int& selectedDialog = *reinterpret_cast<int*>(0x7C8774);
int& InDialogBox = *reinterpret_cast<int*>(0x7C8758);
int& VisibleDialog = *reinterpret_cast<int*>(0x7C875C);
int& dword_7C8760 = *reinterpret_cast<int*>(0x7C8760);
int& dword_7C8764 = *reinterpret_cast<int*>(0x7C8764);
int& TitleDialogBox = *reinterpret_cast<int*>(0x7C8768);
int& Btn1DialogBox = *reinterpret_cast<int*>(0x7C876C);
int& Btn2DialogBox = *reinterpret_cast<int*>(0x7C8770);
int& Btn1Pos = *reinterpret_cast<int*>(0x7C8774);
int& Btn2Pos = *reinterpret_cast<int*>(0x7C8778);

DialogState g_Dialog = { false, nullptr };


namespace CVisual
{
    

    int LoadTexture(int txd, const char* texture)
    {
        return CallAndReturn<int, 0x5EA520, int, const char*>(txd, texture);
    }

    void DrawImage(float posX, float posY, float scaleX, float scaleY, int red, int green, int blue, int alpha, int pTexture)
    {
        Call<0x5F96F0>(posX, posY, scaleX, scaleY, red, green, blue, alpha, pTexture);
    }

    // ------------------------------------------------------------------------------------------------

    void DrawMenuItem(wchar_t* text, float x, float y, int textScaleX, float textScaleY, int menuID)
    {
        // a4, v5 -> text scale?
        Call<0x5D55C0>(text, x, y, textScaleX, textScaleY, menuID);
    }

    void DrawColoredQuad(float x, float y, float width, float height, int r, int g, int b, int a, int unknown)
    {
        Call<0x5F96F0, float, float, float, float, int, int, int, int, int>(x, y, width, height, r, g, b, a, unknown);
    }


    int GetAspectRatio()
    {
        return CallAndReturn<int, 0x5EA2B0>();
    }


    int IsUIActive()
    {
        return CallAndReturn<int, 0x5DACB0>();
    }

    // Variáveis globais
    int& dword_7C8F80 = *(int*)0x7C8F80;
    int& dword_7C8FB4 = *(int*)0x7C8FB4;
    int& dword_7C8FA4 = *(int*)0x7C8FA4;
    int& dword_7C8FA8 = *(int*)0x7C8FA8;
    float& mouseX = *(float*)0x7C8FC0;
    float& mouseY = *(float*)0x7C8FC4;
    float& flt_7C8730 = *(float*)0x7C8730;
    float& flt_7C8734 = *(float*)0x7C8734;
    float& flt_7C9048 = *(float*)0x7C9048;
    float& paddingDefault = *(float*)0x7C872C;
    int& bgR = *(int*)0x7C8748;
    int& bgG = *(int*)0x7C874C;
    int& bgB = *(int*)0x7C8750;
    int& bgA = *(int*)0x7C8754;

    void DrawMenuItemEx(wchar_t* text, float x, float y, int fontType, float scale, void (*callback)(),
        int customR, int customG, int customB, int customA, float customPadding)
    {
        int r = customR, g = customG, b = customB, a = customA, menuID;

        if (customR == -1) r = bgR;
        if (customG == -1) g = bgG;
        if (customB == -1) b = bgB;
        if (customA == -1) a = bgA;

        if (GetAspectRatio() == 2 && customR == -1) { r = 22; g = 22; b = 118; a = 164; }

        float padding = (customPadding == -1.0f) ? paddingDefault : customPadding;

        float textW = CText::Text_CalcWidth((const wchar_t*)text, fontType, 2);
        float textH = CText::GetTextWidth(2, scale);

        if (IsUIActive()) {
            if (dword_7C8F80) { if (!dword_7C8FB4) dword_7C8FA4++; }
            else if (!dword_7C8FB4) dword_7C8FA8++;

            if (mouseX > x && x + textW > mouseX && mouseY > y && y + textH > mouseY) {
                dword_7C8FB4 = 1;
                menuID = 1;
            }
        }

        if (menuID) {
            DrawColoredQuad(x - padding, y + flt_7C8730, padding * flt_7C9048 + textW, textH + flt_7C8734, r, g, b, a, 0);
            CMainMenu::SetSelectedMenuItemColor();
        }
        else {
            CMainMenu::SetNormalMenuItemColor();
        }
    }

    // ------------------------------------------------------------------------------------------------

    void DrawString(wchar_t* text, float x, float y, int textScaleX, float textScaleY)
    {
        Call<0x5D5B30>(text, x, y, textScaleX, textScaleY);
    }

    //

    void GameText(const char* text)
    {
        ((void(__cdecl*)(const char*))0x005E5410)(text);
    }

    void GameTextLeft(int line, const char* text)
    {
		if (line < 0 || line > 25) return;

		Call<0x5E5480>(line, text);
    }


    // --------------------------------------------------------------------------------------------------------------

    void ShowDialogBox(void* pMessageText, void* pBtn1, void* pBtn2, int pBtn1_Column, int pBtn2_Column)
    {
        if (InDialogBox) return;

        InDialogBox = 1;
        VisibleDialog = 1;
        dword_7C8760 = 0;
        dword_7C8764 = 1;
        TitleDialogBox = (int)pMessageText;
        Btn1DialogBox = (int)pBtn1;
        Btn2DialogBox = (int)pBtn2;
        Btn1Pos = pBtn1_Column - 1;
        Btn2Pos = pBtn2_Column - 1;
    }

    void HideDialogBox()
    {
        if (!InDialogBox && !VisibleDialog) return;
        InDialogBox = 0;
        VisibleDialog = 0;
        g_Dialog.waiting = false;
    }

    // --------------------------------------------------------------------------------------------------------------

    void ShowDialogBoxEx(void* pMessageText, void* pBtn1, void* pBtn2, tDialogCallback callback, int pBtn1_Column, int pBtn2_Column)
    {
        if (InDialogBox) return;

        ShowDialogBox(pMessageText, pBtn1, pBtn2, pBtn1_Column, pBtn2_Column);
        g_Dialog.waiting = true;
        g_Dialog.callback = callback;
    }

    void UpdateDialogBox()
    {
        if (!g_Dialog.waiting) return;
        if (!InDialogBox || !VisibleDialog) return;

        int button = (selectedDialog == 0) ? 1 : 2;

        if (g_Dialog.callback)
            g_Dialog.callback(button);

        HideDialogBox();
    }



    // --------------------------------------------------------------------------------------------------------------

    void InstallHook()
    {
        // Nada por enquanto
    }
}