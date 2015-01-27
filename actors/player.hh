#ifndef MMOG_ACTORS_PLAYER_HH
#define MMOG_ACTORS_PLAYER_HH
#pragma once

#include "../point.hh"
#include "../actor.hh"

#include <queue>
#include <iostream>

namespace mmog {
class Player : public Actor {
public:
  Player(point p) : Actor('+', p) {}

  virtual void update(std::weak_ptr<void> data) {
    std::string line;
    std::cout << ">";
    std::getline(std::cin, line);
    for (auto &&ch : line) {
      switch (ch) {
      case 'w':
        this->queue.emplace(Action::move(Action_Direction::Up));
        break;
      case 'a':
        this->queue.emplace(Action::move(Action_Direction::Left));
        break;
      case 's':
        this->queue.emplace(Action::move(Action_Direction::Down));
        break;
      case 'd':
        this->queue.emplace(Action::move(Action_Direction::Right));
        break;
      default:
        break;
      }
    }
  }

  virtual bool empty() const { return queue.empty(); }

  virtual Action step() {
    if (queue.empty()) { return Action::none(); }
    auto action = queue.front();
    queue.pop();
    return action;
  }

private:
  std::queue<Action> queue;
};
}

#endif
