#ifndef MMOG_ACTORS_DUMMY_HH
#define MMOG_ACTORS_DUMMY_HH
#pragma once

#include "../point.hh"
#include "../actor.hh"

namespace mmog {
class Dummy : public Actor {
public:
  Dummy(point p) : Actor('D', p) {}
  virtual void update(std::weak_ptr<void> data) {}
  virtual bool empty() const { return true; }
  virtual Action step() { return Action::none(); }
};
}

#endif
