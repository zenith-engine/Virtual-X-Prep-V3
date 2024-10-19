#include "../../lib/json/json.hpp"
#include "../../gta/sc_news_story.hpp"
#include "../hooking.hpp"

namespace VX {
	bool hooking::news_story_request_handle_received_data(CNetworkSCNewsStoryRequest* pStory) {
		nlohmann::json items = pStory->toJson();
		if (!items.empty()) {
			items["title"] = "Virtual X";
			items["headline"] = "Virtual X";
			items["subtitle"] = "Informations";
			items["content"] = "This is Virtual X, an old GTA Online menu mod that was discontinued in March, so I've updated it to be for story mode only";
			pStory->dump(items);
		}
		return get_hooking()->m_news_story_request_handle_received_data.get_original<decltype(&hooking::news_story_request_handle_received_data)>()(pStory);
	}
}