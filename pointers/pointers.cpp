#include "pointers.hpp"
#include "../hooking/hooking.hpp"
#include "../memory/memory.hpp"

namespace VX {

    pointers g_pointers;

    void pointers::initialize() {
        m_news_story_request_handle_received_data = reinterpret_cast<news_story_request_handle_received_data>(get_memory()->scan("48 89 5C 24 18 48 89 74 24 20 55 57 41 56 48 8B EC 48 81 EC 80 00 00 00 48 8D", "NSRHRD"));
        m_loading_screen_state = reinterpret_cast<eLoadingScreenState*>(get_memory()->scan("83 3D ? ? ? ? ? 75 17 8B 43 20 25", "LSS", 3, true));
        m_window = FindWindowA("grcWindow", "Grand Theft Auto V");
    }
    pointers* get_pointers() { return &g_pointers; }
}