#pragma once
#include "framework.h"

namespace Forge
{

    enum class MouseEvent
    {
        Move,
        ButtonDown,
        ButtonUp,
        ScrollVertical,
        ScrollHorizontal
    };

    enum class MouseButton
    {
        Unkown = 0,

        Left,
        Right,
        Middle,
        X1,
        X2,

        Count
    };

    struct FORGE_API MouseState
    {
        int x = 0;
        int y = 0;

        int deltaX = 0;
        int deltaY = 0;
    };


    FORGE_API MouseButton MouseMessageToMouseButton(WPARAM key);

    FORGE_API const wchar_t* MouseButtonToString(MouseButton button);
}