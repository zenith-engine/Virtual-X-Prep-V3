#include "hooking.hpp"
#include "../common.hpp"
#include "../pointers/pointers.hpp"
#include "hooks/news_story_request_handle_received_data.hpp"

namespace VX {

	hooking g_hooking;

	bool hooking::initialize() {
		MH_Initialize();

		m_news_story_request_handle_received_data.create("NSRHRD", get_pointers()->m_news_story_request_handle_received_data, &hooking::news_story_request_handle_received_data);

		MH_EnableHook(MH_ALL_HOOKS);
		return true;
	}

	void hooking::cleanup() {
		m_news_story_request_handle_received_data.remove();

		MH_DisableHook(MH_ALL_HOOKS);

		MH_Uninitialize();
	}
	hooking* get_hooking() { return &g_hooking; }
}