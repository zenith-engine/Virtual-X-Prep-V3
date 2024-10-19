#pragma once
#include "../lib/json/json.hpp"

#include <cstdint>
#include <utility>

class CNetworkSCNewsStoryRequest {
public:
	char gap0[8];     //0x0
	uint32_t m_state;    //0x8
	char* m_buffer;      //0x0010 //rage::datGrowBuffer
	uint32_t m_cap;      //0x0018
	uint32_t m_len;      //0x001C
	uint32_t m_flags;    //0x0020
	uint8_t m_allocator; //0x0024 //rage::sysMemAllocator
	char gap[0x138];
	uint32_t m_style;              //0x160
	char gap164[4];             //0x164
	char m_newStoryTxdName[64]; //0x168

	std::string getGrowBuffer() {
		return m_buffer;
	}
	void dump(nlohmann::json& json) {
		set(json.dump());
	}
	nlohmann::json toJson() {
		if (!m_buffer)
			return {};
		return nlohmann::json::parse(getGrowBuffer());
	}
	void set(const std::string& str) {
		strcpy(m_buffer, str.c_str());
		m_len = static_cast<uint32_t>(str.length());
		m_cap = UINT_MAX;
	}
};
static_assert(sizeof(CNetworkSCNewsStoryRequest) == 0x1A8);
