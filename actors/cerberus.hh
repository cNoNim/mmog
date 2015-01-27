#ifndef MMOG_ACTORS_CERBERUS_HH
#define MMOG_ACTORS_CERBERUS_HH
#pragma once

#include "../point.hh"
#include "../actor.hh"

namespace mmog {
class Cerberus : public Actor {
public:
  Cerberus(point p) : Actor('@', p) {}
  virtual void update(std::weak_ptr<void> data) {}
  virtual bool empty() const { return true; }
  virtual Action step() { return Action::none(); }
};
}

#endif
