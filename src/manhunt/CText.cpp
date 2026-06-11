#include "CText.h"

namespace CText
{
	float GetTextWidth8(const wchar_t* text, int sizex, int fontType)
    {
        return CallMethodAndReturn<float, 0x5E5670, const wchar_t*, int, int>(text, sizex, fontType);
    }

    float Text_CalcWidth(const wchar_t* text, int fontType, int fontIndex) 
    {
        return CallAndReturn<float, 0x5E56F0>(text, fontType, fontIndex);
    }

    float GetTextWidth(int fontType, float scale)
    {
        float result;
        __asm {
            mov     ecx, fontType
            mov     eax, [0x7D2BC4 + ecx * 4]
            fld     dword ptr[0x7D2BF4 + eax * 4]
            fmul    scale
            fstp    result
        }
        return result;
    }

    // -------------------------------------------------------------------------------

    wchar_t* GetKey(const char* key)
    {
        return CallMethodAndReturn<wchar_t*, 0x4937E0, int, const char*>(0x725A38, key);
    }

    wchar_t* KeyEx(const char* str)
    {
        int len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
        wchar_t* out = (wchar_t*)malloc(len * sizeof(wchar_t));
        MultiByteToWideChar(CP_ACP, 0, str, -1, out, len);
        return out;
    }

    // -------------------------------------------------------------------------------

    typedef int (*OriginalParseColorCodes)(int a1, DWORD* a2, int a3, int a4);

    SafetyHookInline g_ParseColorCodesHook;
    OriginalParseColorCodes g_OriginalFunc = nullptr;

    struct ColorRGBA {
        int r, g, b, a;
    };

    struct ColorSet {
        ColorRGBA c1, c2, c3, c4;
    };

    int MyParseColorCodes(int a1, DWORD* a2, int a3, int a4)
    {
        char tag[32] = { 0 };
        int tagLen = 0;
        int* colorArray = (int*)0x7D4EC8;
        int* colorData = (int*)0x7D2C04;

        while (1)
        {
            tagLen = 0;

            while (1)
            {
                int pos = tagLen + *a2 + 1;
                if (pos >= a3)
                {
                    ((void(*)(int, const char*, int))0x5E5530)(0x7D2E38, "PrintFunctionC", 0);
                    return 0;
                }

                short ch = *(short*)(a1 + 2 * pos);
                if (ch == '~') break;

                tag[tagLen++] = (char)ch;
            }

            tag[tagLen] = 0;
            if (tagLen <= 0) break;

            // Cores
            if (strcmp(tag, "black") == 0) {
                if (*(int*)0x7D4EAC) {
                    for (int i = 0; i < 16; i++)
                        colorArray[i] = colorData[i];
                }
            }
            else if (strcmp(tag, "white") == 0) {
                if (*(int*)0x7D4EAC) {
                    for (int i = 0; i < 16; i++)
                        colorArray[i] = colorData[i + 4];
                }
            }
            else if (strcmp(tag, "red") == 0 || strcmp(tag, "red2") == 0 || strcmp(tag, "red3") == 0 || strcmp(tag, "red4") == 0) {
                if (*(int*)0x7D4EAC) {
                    for (int i = 0; i < 4; i++) {
                        colorArray[i * 4] = 255;
                        colorArray[i * 4 + 1] = 0;
                        colorArray[i * 4 + 2] = 0;
                        colorArray[i * 4 + 3] = 255;
                    }
                }
            }
            else if (strcmp(tag, "green") == 0 || strcmp(tag, "green2") == 0 || strcmp(tag, "green3") == 0 || strcmp(tag, "green4") == 0) {
                if (*(int*)0x7D4EAC) {
                    for (int i = 0; i < 4; i++) {
                        colorArray[i * 4] = 0;
                        colorArray[i * 4 + 1] = 255;
                        colorArray[i * 4 + 2] = 0;
                        colorArray[i * 4 + 3] = 255;
                    }
                }
            }
            else if (strcmp(tag, "blue") == 0 || strcmp(tag, "blue2") == 0 || strcmp(tag, "blue3") == 0 || strcmp(tag, "blue4") == 0) {
                if (*(int*)0x7D4EAC) {
                    for (int i = 0; i < 4; i++) {
                        colorArray[i * 4] = 0;
                        colorArray[i * 4 + 1] = 0;
                        colorArray[i * 4 + 2] = 255;
                        colorArray[i * 4 + 3] = 255;
                    }
                }
            }
            else if (strcmp(tag, "yellow") == 0 || strcmp(tag, "yellow2") == 0 || strcmp(tag, "yellow3") == 0 || strcmp(tag, "yellow4") == 0) {
                if (*(int*)0x7D4EAC) {
                    for (int i = 0; i < 4; i++) {
                        colorArray[i * 4] = 255;
                        colorArray[i * 4 + 1] = 255;
                        colorArray[i * 4 + 2] = 0;
                        colorArray[i * 4 + 3] = 255;
                    }
                }
            }
            else if (strcmp(tag, "orange") == 0 || strcmp(tag, "orange2") == 0 || strcmp(tag, "orange3") == 0 || strcmp(tag, "orange4") == 0) {
                if (*(int*)0x7D4EAC) {
                    for (int i = 0; i < 4; i++) {
                        colorArray[i * 4] = 255;
                        colorArray[i * 4 + 1] = 165;
                        colorArray[i * 4 + 2] = 0;
                        colorArray[i * 4 + 3] = 255;
                    }
                }
            }
            else if (strcmp(tag, "grey") == 0 || strcmp(tag, "grey2") == 0 || strcmp(tag, "grey3") == 0 || strcmp(tag, "grey4") == 0) {
                if (*(int*)0x7D4EAC) {
                    for (int i = 0; i < 4; i++) {
                        colorArray[i * 4] = 128;
                        colorArray[i * 4 + 1] = 128;
                        colorArray[i * 4 + 2] = 128;
                        colorArray[i * 4 + 3] = 255;
                    }
                }
            }
            else if (strcmp(tag, "cyan") == 0 || strcmp(tag, "cyan2") == 0 || strcmp(tag, "cyan3") == 0 || strcmp(tag, "cyan4") == 0) {
                if (*(int*)0x7D4EAC) {
                    for (int i = 0; i < 4; i++) {
                        colorArray[i * 4] = 0;
                        colorArray[i * 4 + 1] = 255;
                        colorArray[i * 4 + 2] = 255;
                        colorArray[i * 4 + 3] = 255;
                    }
                }
            }
            else if (strcmp(tag, "magenta") == 0 || strcmp(tag, "magenta2") == 0 || strcmp(tag, "magenta3") == 0 || strcmp(tag, "magenta4") == 0) {
                if (*(int*)0x7D4EAC) {
                    for (int i = 0; i < 4; i++) {
                        colorArray[i * 4] = 255;
                        colorArray[i * 4 + 1] = 0;
                        colorArray[i * 4 + 2] = 255;
                        colorArray[i * 4 + 3] = 255;
                    }
                }
            }
            else if (strcmp(tag, "colour") == 0) {
                if (*(int*)0x7D4EAC) {
                    for (int i = 0; i < 4; i++) {
                        colorArray[i * 4] = 180;
                        colorArray[i * 4 + 1] = 180;
                        colorArray[i * 4 + 2] = 180;
                        colorArray[i * 4 + 3] = 255;
                    }
                }
            }
            
            // Ícones
            else if (strcmp(tag, "triangle") == 0) {
                short val = 91;
                ((void(*)(short*, int))0x5E59C0)(&val, a4);
                // GetKey etc...
            }
            else if (strcmp(tag, "circle") == 0) {
                short val = 111;
                ((void(*)(short*, int))0x5E59C0)(&val, a4);
            }
            else if (strcmp(tag, "cross") == 0) {
                short val1 = 91;
                short val2 = 93;
                ((void(*)(short*, int))0x5E59C0)(&val1, a4);
                ((void(*)(short*, int))0x5E59C0)(&val2, a4);
            }
            else if (strcmp(tag, "square") == 0) {
                short val = 35;
                ((void(*)(short*, int))0x5E59C0)(&val, a4);
            }
            else if (strcmp(tag, "TM") == 0) {
                short val = 132;
                ((void(*)(short*, int))0x5E59C0)(&val, a4);
            }
            else if (strcmp(tag, "(C)") == 0) {
                short val = 169;
                ((void(*)(short*, int))0x5E59C0)(&val, a4);
            }
            else if (strcmp(tag, "(R)") == 0) {
                short val = 174;
                ((void(*)(short*, int))0x5E59C0)(&val, a4);
            }
            else if (strcmp(tag, "star") == 0 || strcmp(tag, "star2") == 0) {
                short val = (strcmp(tag, "star") == 0) ? 156 : 157;
                ((void(*)(short*, int))0x5E59C0)(&val, a4);
            }
            else if (strcmp(tag, "left") == 0) {
                short val = 139;
                ((void(*)(short*, int))0x5E59C0)(&val, a4);
            }
            else if (strcmp(tag, "right") == 0) {
                short val = 140;
                ((void(*)(short*, int))0x5E59C0)(&val, a4);
            }
            else if (strcmp(tag, "up") == 0) {
                short val = 141;
                ((void(*)(short*, int))0x5E59C0)(&val, a4);
            }
            else if (strcmp(tag, "down") == 0) {
                short val = 142;
                ((void(*)(short*, int))0x5E59C0)(&val, a4);
            }

            if (*(short*)(a1 + 2 * (tagLen + *a2) + 4) != '~')
                break;

            *a2 += tagLen + 2;
        }

        *a2 += tagLen + 2;
        return 1;
    }

    void InstallHook()
    {
        g_OriginalFunc = (OriginalParseColorCodes)0x5E5D10;

        g_ParseColorCodesHook = safetyhook::create_inline((void*)0x5E5D10, (void*)&MyParseColorCodes);
	}

}