#include "common.hpp"
#include "hooking/hooking.hpp"
#include "pointers/pointers.hpp"
#include "memory/dll.hpp"

BOOL DllMain(HINSTANCE hInstance, DWORD reason, LPVOID) {
	using namespace VX;

	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hInstance);
		m_module = hInstance;
		m_main_thread = CreateThread(
			nullptr,
			0,
			[](LPVOID) -> DWORD {
				get_pointers()->initialize();
				get_hooking()->initialize();
				SetWindowTextA(get_pointers()->m_window, NAME);
				if (*get_pointers()->m_loading_screen_state != eLoadingScreenState::Finished)
				{
					while (*get_pointers()->m_loading_screen_state != eLoadingScreenState::Finished)
					{
						std::this_thread::sleep_for(1000ms);
					}
				}
				while (g_running) {
					if (inject) {
						std::thread t([=]() mutable {
							MessageBoxA(NULL, "Sucessfuly Inject Virtual X", "Services", MB_OK);
						t.detach();
					}
					if (GetAsyncKeyState(VK_F7) & 0x8000) {
						g_running = false;
					}
					std::this_thread::sleep_for(1ms);
				}
				get_hooking()->cleanup();
				SetWindowTextA(get_pointers()->m_window, "Grand Theft Auto V");
				CloseHandle(m_main_thread);
				FreeLibraryAndExitThread(m_module, 0);
			}, nullptr,
			0,
			&m_main_thread_id);
	}
	return true;
}
