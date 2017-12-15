#pragma once

#include "jammy_game_object.h"

class player : public jammy_game_object
{
public:
  player();

  void update(float dt) override;

  void draw(screen& scr) override;

  // * move *
  // Move in the given direction, a bitfield combination of 
  //  directions.
  void move(int move_dir);

  int lose_life();

  void keep_immune();
 
  bool is_immune() const { return m_is_immune; }

  int get_num_lives() const { return m_lives; }

  int get_score() const { return m_score; }
 
  void add_score(int add) { m_score += add; }

  void add_human_saved() { m_humans_saved++; }

  int get_num_humans_saved() const { return m_humans_saved; }

private:
  bool m_is_immune = false;
  float m_immune_time = 0;
  int m_lives = 0;
  int m_score = 0;
  int m_humans_saved = 0;
};

