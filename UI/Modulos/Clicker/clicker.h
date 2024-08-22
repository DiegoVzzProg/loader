#pragma once
#include "../../ui.h"

namespace clicker_ui {
	extern void render();
}

namespace cg_clicker {
	inline bool enabled = false;
	inline float cps = 12.f;
	inline bool block_hit = false;
	inline bool auto_block_hit = false;
	inline bool only_one_hit = false;
	inline bool auto_click = false;
	inline bool break_blocks = false;
	inline bool shift_disabled_click = false;
}