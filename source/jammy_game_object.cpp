#include "jammy_game_object.h"
#include "universe.h"

vec2 jammy_game_object::s_cam_pos;

static const vec2 CENTRE(60.f, 60.f);

bool sprite_collision(
  jammy_game_object* jgo1, jammy_game_object* jgo2)
{
  pix_int_result r = pixel_intersect(
    jgo1->m_sprite, jgo1->m_sprite.get_cell(), jgo1->m_pos.x, jgo1->m_pos.y,
    jgo2->m_sprite, jgo2->m_sprite.get_cell(), jgo2->m_pos.x, jgo2->m_pos.y);

  return (r == pix_int_result::YES_COLLIDE);
}

void jammy_game_object::set_cam_pos(const vec2& pos)
{
}

void jammy_game_object::draw(screen& dest)
{
  vec2 rel_pos = m_pos - s_cam_pos + CENTRE;

  int x = rel_pos.x;
  int y = rel_pos.y;

  m_sprite.draw(dest, x, y);
}

void jammy_game_object::update(float dt) 
{
  game_object::update(dt);

  // Wrap around
  vec2 rel_pos = m_pos - s_cam_pos + CENTRE;

  if (rel_pos.x < -(UNIVERSE_SIZE / 2))
  {
    m_pos.x += UNIVERSE_SIZE;
  }
  if (rel_pos.x > (UNIVERSE_SIZE / 2))
  {
    m_pos.x -= UNIVERSE_SIZE;
  }
  if (rel_pos.y < -(UNIVERSE_SIZE / 2))
  {
    m_pos.y += UNIVERSE_SIZE;
  }
  if (rel_pos.y > (UNIVERSE_SIZE / 2))
  {
    m_pos.y -= UNIVERSE_SIZE;
  }

  m_sprite.update(dt);
}

