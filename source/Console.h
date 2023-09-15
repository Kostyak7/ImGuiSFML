#pragma once

#include "imgui_console.h"

class Console {
public:
	Console();
	~Console();

	ImGuiConsole& operator()() { return m_console; }

	bool is_active() { return m_is_active; }
	bool activate(bool is_activate_ = true) {
		return m_is_active = is_activate_;
	}
private:
	bool m_is_active = false;
	ImGuiConsole  m_console;

	void init();
};