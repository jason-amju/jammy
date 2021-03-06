#include <iostream>
#include "directory.h"
#include "input.h"
#include "globals.h"
#include "player.h"
#include "sign.h"

const float MAX_IMMUNE_TIME = 3.f;

const float DECELERATION = 0.25f;

player::player()
{
  m_sprite.load(get_data_dir() + "Player_all.png", the_global_palette);
  m_sprite.set_num_cells(9, 1);

  m_pos = vec2(60, 60);

  m_is_immune = false;
  m_immune_time = 0;
  m_lives = 5;
}

void player::keep_immune()
{
  m_immune_time = MAX_IMMUNE_TIME;
  m_is_immune = true;
}

int player::lose_life()
{
  if (m_lives > 0)
  {
    m_lives--;
  }

  keep_immune();

  return m_lives;
}

static float flasher = 0;
static const float FLASH_PERIOD = .3f;

void player::draw(screen& scr)
{
  if (m_is_immune)  
  {
    if (flasher > FLASH_PERIOD * .5f)
    {
      return;
    }
  }

  jammy_game_object::draw(scr);
}

void player::update(float dt)
{
  if (m_is_immune)
  {
    flasher += dt;
    if (flasher > FLASH_PERIOD)
    {
      flasher = 0;
    }

    m_immune_time -= dt;
    if (m_immune_time <= 0)
    {
      m_immune_time = 0;
      m_is_immune = false;
    }
  }

  vec2 old_vel = m_vel;

  jammy_game_object::update(dt);
  
  // Check for deceleration to stop
  if (sign(old_vel.x) != sign(m_vel.x))
  {
    m_vel.x = 0;
  }

  if (sign(old_vel.y) != sign(m_vel.y))
  {
    m_vel.y = 0;
  }

  const float STOPPED = 0.1f;
  if (fabs(m_vel.x) < STOPPED && fabs(m_vel.y) < STOPPED)
  {
    // Set sprite to stopped
    m_sprite.set_cell_range(3, 3);
  }

  s_cam_pos = m_pos; // TODO some elasticity
}

void player::move(int move_dir)
{
  float speed = 2.f; // TODO 

  if (move_dir != MOVE_NONE)
  {
    int CELL[16];  // 16 permutations but not all are valid
    // Map move bitfield to cell position
    for (int i = 0; i < 16; i++)
    {
      CELL[i] = 3;
    }
    CELL[MOVE_RIGHT] = 0;
    CELL[MOVE_RIGHT | MOVE_UP] = 1;
    CELL[MOVE_RIGHT | MOVE_DOWN] = 2;
    CELL[MOVE_UP] = 4;
    CELL[MOVE_DOWN] = 5;
    CELL[MOVE_LEFT] = 6;
    CELL[MOVE_LEFT | MOVE_UP] = 7;
    CELL[MOVE_LEFT | MOVE_DOWN] = 8;

    int c = CELL[move_dir];
    m_sprite.set_cell_range(c, c);
  }

  vec2 dir;
  if (move_dir & MOVE_UP)
  {
    dir.y -= speed; 
  }
  if (move_dir & MOVE_DOWN)
  {
    dir.y += speed; 
  }
  if (move_dir & MOVE_LEFT)
  {
    dir.x -= speed; 
  }
  if (move_dir & MOVE_RIGHT)
  {
    dir.x += speed; 
  }

  m_vel += dir;
  // Max speed
//  float max_speed = 20.f; // TODO
//  if (squared_length(m_vel) > max_speed)
//  {
//    m_vel = normalise(m_vel) * max_speed;
//  }

  m_acc = -m_vel * DECELERATION; 
}

