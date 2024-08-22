#pragma once
#include "../../ui.h"

namespace clicker_ui {
	extern void render();
}

namespace cg_clicker {
	static bool enabled = false;
	static float cps = 12.f;
	static bool block_hit = false;
	static bool auto_block_hit = false;
	static bool only_one_hit = false;
	static bool auto_click = false;
	static bool break_blocks = false;
	static bool shift_disabled_click = false;
}