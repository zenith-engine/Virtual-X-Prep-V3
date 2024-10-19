#pragma once
#include "../common.hpp"
#include "../gta/sc_news_story.hpp"

#include <dxgi.h>

namespace rage {
	class CDynamicEntity;
}
namespace VX {
	class pointers
	{
	public:
		void initialize();
	public:
		using news_story_request_handle_received_data = bool (*)(CNetworkSCNewsStoryRequest* pStory);
		news_story_request_handle_received_data m_news_story_request_handle_received_data;

		eLoadingScreenState* m_loading_screen_state{};

		HWND m_window;

	}; pointers* get_pointers();
}