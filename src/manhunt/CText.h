#pragma once
#include "../../framework.h"
#include "../game.sdk.h"

namespace CText
{
    float GetTextWidth8(const wchar_t* text, int sizex, int fontType);
    float GetTextWidth(int fontType, float scale);
    float Text_CalcWidth(const wchar_t* text, int fontType, int fontIndex);

    wchar_t* GetKey(const char* key);
    wchar_t* KeyEx(const char* str);

    void InstallHook();
}