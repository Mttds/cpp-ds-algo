#pragma once

#include "stack.h"
#include <vector>

class Game {
  public:
    Game();
    void solve();

    friend std::ostream& operator<<(std::ostream &os, const Game &game);

  private:
    std::vector<Stack> stacks_;

    void _legalMove(unsigned int, unsigned int);
    void _move(unsigned int, unsigned int);
};

