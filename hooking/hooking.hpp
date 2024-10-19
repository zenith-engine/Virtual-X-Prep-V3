#pragma once
#include "detour/detour.hpp"
#include "../lib/MinHook.h"
#include "../gta/sc_news_story.hpp"

namespace VX {
	class hooking {
	public:
		bool initialize();
		void cleanup();
	public:
		inline static bool news_story_request_handle_received_data(CNetworkSCNewsStoryRequest* pStory);
		detour_hook m_news_story_request_handle_received_data;
	};
	hooking* get_hooking();
}