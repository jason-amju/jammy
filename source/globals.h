#pragma once

#include "font.h"
#include "game.h"
#include "game_over_state.h"
#include "palette.h"
#include "play_state.h"
#include "screen.h"
#include "splash_state.h"
#include "timer.h"

extern game the_game;
extern game_over_state* the_game_over_state;
extern timer the_timer;
extern font the_font;
extern palette the_global_palette;
extern screen the_screen;
extern play_state* the_play_state;
extern splash_state* the_splash_state;

