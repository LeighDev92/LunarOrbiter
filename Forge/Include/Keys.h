#pragma once
#include "framework.h"

namespace Forge
{
    enum class KeyEvent
    {
        Unknown = 0,

        Down,
        Up,

        Count
    };

    enum class Key
    {
        Unknown = 0,

        // Mouse
        MouseLeft,
        MouseRight,
        MouseMiddle,
        MouseX1,
        MouseX2,

        // Control
        Backspace,
        Tab,
        Enter,
        Shift,
        Control,
        Alt,
        Pause,
        CapsLock,
        Escape,
        Space,
        PageUp,
        PageDown,
        End,
        Home,
        Left,
        Up,
        Right,
        Down,
        Insert,
        Delete,

        // Numbers
        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,

        // Letters
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        // Numpad
        Numpad0,
        Numpad1,
        Numpad2,
        Numpad3,
        Numpad4,
        Numpad5,
        Numpad6,
        Numpad7,
        Numpad8,
        Numpad9,
        NumpadMultiply,
        NumpadAdd,
        NumpadSubtract,
        NumpadDecimal,
        NumpadDivide,

        // Function keys
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,

        // Lock keys
        NumLock,
        ScrollLock,

        // Symbols
        Semicolon,
        Equals,
        Comma,
        Minus,
        Period,
        Slash,
        Grave,
        LeftBracket,
        Backslash,
        RightBracket,
        Apostrophe,

        // Modifier keys
        LeftShift,
        RightShift,
        LeftControl,
        RightControl,
        LeftAlt,
        RightAlt,

        Count
    };

    FORGE_API Key VirtualKeyToKey(WPARAM vk);

    FORGE_API const wchar_t* KeyToString(Key key);
}