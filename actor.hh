#ifndef MMOG_ACTOR_HH
#define MMOG_ACTOR_HH
#pragma once

#include "action.hh"
#include "point.hh"

#include <memory>
#include <string>

namespace mmog {

  class Object {
  public:
    Object(char c, point p) : c(c), p(p) { }
    virtual ~Object() { }
    char representation() const { return c; }
    point & position() { return p; }
    point const & position() const { return p; }
  private:
    point p;
    char c;
  };

  class Actor : public Object {
  public:
    Actor(char c, point p) : Object(c, p) {}
    virtual std::shared_ptr<void> init() const { return nullptr; }
    virtual void update(std::weak_ptr<void> data) = 0;
    void update() { update(_data); }
    virtual bool empty() const = 0;
    virtual Action step() = 0;
  private:
    std::shared_ptr<void> _data;
  };

  std::unique_ptr<Actor> loadActor(std::string const &name, int x, int y);
}

#endif