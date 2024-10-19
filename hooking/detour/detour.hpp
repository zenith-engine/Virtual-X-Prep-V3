#pragma once
#include "../../lib/MinHook.h"

namespace VX {
	class detour_hook {
	public:
		void create(char const* name, void* ptr, void* dtr, bool disable = false) {
			m_name = name;
			m_ptr = ptr;
			m_dtr = dtr;
			m_disable = disable;
			if (!m_disable) {
				if (auto status = MH_CreateHook(m_ptr, m_dtr, &m_og); status == MH_OK) {
				}
			}
		}
		void remove() {
			if (!m_disable) {
				if (auto status = MH_RemoveHook(m_ptr); status == MH_OK) {
				}
			}
		}
		void enable() {
			if (!m_disable) {
				if (auto status = MH_EnableHook(m_ptr); status != MH_OK) {
				}
			}
		}
		void disable() {
			if (!m_disable) {
				if (auto status = MH_DisableHook(m_ptr); status != MH_OK) {
				}
			}
		}

		template <typename T>
		inline T get_original()
		{
			return static_cast<T>(m_og);
		}
	private:
		char const* m_name;
		void* m_dtr;
		void* m_ptr;
		void* m_og;
		bool m_disable;
	};
};