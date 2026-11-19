#pragma once
#include <unordered_set>
#include <functional>
#include <vector>
#include <unordered_map>
#include <Windows.h>
#include "Keys.h"
#include "Mouse.h"

namespace Forge
{
    using BindingID = uint64_t;
    using KeyCallback = std::function<void(KeyEvent event)>;
    using MouseMoveCallback = std::function<void(MouseState state)>;
    using MouseButtonCallback = std::function<void(MouseEvent event)>;
    using MouseScrollCallback = std::function<void(int delta)>;

    template<typename T>
    struct FORGE_API Binding
    {
        BindingID id;
        T callback;

        Binding(BindingID _id, T _callback)
        {
            id = _id;
            callback = std::move(_callback);
        }
    };

    class FORGE_API InputManager
    {
    public:
        InputManager();
        ~InputManager();

        static InputManager* Get();

        void ProcessKeyUp(Key key);
        void ProcessKeyDown(Key key);
        void SetKeyState(Key key, KeyEvent state);

        void ProcessMouseButtonUp(MouseButton button);
        void ProcessMouseButtonDown(MouseButton button);
        void SetMouseButtonState(MouseButton button, MouseEvent state);

        void ProcessMouseMove(int xPos, int yPos);
        void ProcessMouseScroll(MouseEvent direction, int delta);

        bool IsKeyUp(Key key) const;
        bool IsKeyDown(Key key) const;

        bool IsMouseButtonUp(MouseButton button) const;
        bool IsMouseButtonDown(MouseButton button) const;

        MouseState GetMouseState() const;

        BindingID BindKeyEvent(Key key, KeyEvent event, KeyCallback callback);
        void UnBindKeyEvent(BindingID id);

        BindingID BindMouseButtonEvent(MouseButton button, MouseEvent event, MouseButtonCallback callback);
        void UnBindMouseButtonEvent(BindingID id);

        BindingID BindMouseMoveEvent(MouseMoveCallback callback);
        void UnBindMouseMoveEvent(BindingID id);

        BindingID BindMouseScrollEvent(MouseEvent scroll_event, MouseScrollCallback callback);
        void UnBindMouseScrollEvent(BindingID id);

        void ClearState();
    
    private:
        void BroadcastKeyEvent(Key key, KeyEvent event) const;
        void BroadcastMouseButtonEvent(MouseButton button, MouseEvent event) const;
        void BroadcastMouseMoveEvent(MouseState state) const;
        void BroadcastMouseScrollEvent(MouseEvent direction, int delta) const;

        // key events and state
        std::unordered_set<Key> pressed_keys;
        std::unordered_map<Key, std::vector<Binding<KeyCallback>>> _boundKeyEventsPressed;
        std::unordered_map<Key, std::vector<Binding<KeyCallback>>> _boundKeyEventsReleased;

        // mouse events and state
        MouseState _mouseState;
        std::unordered_set<MouseButton> _pressedMouseButtons;
        std::unordered_map<MouseButton, std::vector<Binding<MouseButtonCallback>>> _boundMouseButtonEventsPressed;
        std::unordered_map<MouseButton, std::vector<Binding<MouseButtonCallback>>> _boundMouseButtonEventsReleased;
        std::vector<Binding<MouseMoveCallback>> _boundMouseMoveEvents;
        std::vector<Binding<MouseScrollCallback>> _boundMouseScrollHorizontalEvents;
        std::vector<Binding<MouseScrollCallback>> _boundMouseScrollVerticalEvents;

        BindingID _nextBindingID = 0;
    };
}

