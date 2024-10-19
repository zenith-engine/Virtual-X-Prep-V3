#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define CURL_STATICLIB

#include <windows.h>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>
#include <minwindef.h>
#include <filesystem>
#include <mutex>
#include <functional>

#include <vector>

using namespace std::chrono_literals;

#define NAME "Virtual X"

inline bool g_running = true;
inline HMODULE m_module{};
inline HANDLE m_main_thread;
inline DWORD m_main_thread_id;
inline std::vector<HMODULE> module_handles;
inline bool inject = false;

enum class eLoadingScreenState : std::int32_t
{
	Invalid = -1,
	Finished,
	PreLegal,
	Unknown_2,
	Legals,
	Unknown_4,
	LandingPage,
	Transition,
	Unknown_7,
	Unknown_8,
	Unknown_9,
	SessionStartLeave
};

inline void injection(std::string path)
{
	if (!FindWindowA(NULL, "Grand Theft Auto V"))
	{
		MessageBoxA(NULL, "Failed To Inject Virtual X", "Services", MB_OK | MB_ICONERROR);
	}
	HWND HWND = FindWindowA(NULL, "Grand Theft Auto V");
	DWORD ProcessID;
	GetWindowThreadProcessId(HWND, &ProcessID);
	HANDLE Handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);

	LPVOID Path = VirtualAllocEx(Handle, 0, strlen(path.c_str()) + 1, MEM_COMMIT, PAGE_READWRITE);

	WriteProcessMemory(Handle, Path, (LPVOID)path.c_str(), strlen(path.c_str()) + 1, 0);

	HANDLE hLoadThread = CreateRemoteThread(Handle, 0, 0,
		(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA"), Path, 0, 0);

	WaitForSingleObject(hLoadThread, INFINITE);

	VirtualFreeEx(Handle, Path, strlen(path.c_str()) + 1, MEM_RELEASE);
}