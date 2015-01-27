#ifndef MMOG_SCENE_HH
#define MMOG_SCENE_HH
#pragma once

#include <memory>
#include <vector>

namespace mmog {
struct point;
class Action;
enum class Action_Direction;
class Actor;
class Map;

class Scene {
public:
  template <typename Map, typename Actors>
  Scene(Map &&map, Actors &&actors);

  char const &move(point &pt, Action_Direction const &dir) const;
  void update();
  void draw(std::vector<char> &buffer) const;

  int width() const;
  int height() const;

private:
  std::unique_ptr<Map> map;
  std::vector<std::shared_ptr<Actor>> actors;
};

std::unique_ptr<Scene> loadLevel(std::string const &name);
}

#include "actor.hh"
#include "action.hh"
#include "map.hh"
#include "point.hh"

namespace mmog {
template <typename Map, typename Actors>
inline Scene::Scene(Map &&map, Actors &&actors)
  : map(std::forward<Map>(map))
  , actors(std::make_move_iterator(std::begin(actors)),
           std::make_move_iterator(std::end(actors))) {}

inline char const &Scene::move(point &pt, Action_Direction const &dir) const {
  switch (dir) {
  case Action_Direction::Up:
    pt.y--;
    break;
  case Action_Direction::Left:
    pt.x--;
    break;
  case Action_Direction::Down:
    pt.y++;
    break;
  case Action_Direction::Right:
    pt.x++;
    break;
  }
  while (pt.x < 0) pt.x+= this->width();
  while (pt.x >= this->width()) pt.x-= this->width();
  while (pt.y < 0) pt.y+= this->height();
  while (pt.y >= this->height()) pt.y-= this->height();
  return this->map->at(pt);
}

inline void Scene::update() {
  for (auto &&actor : actors) {
    actor->update();
    while (!actor->empty()) {
      auto action= actor->step();
      switch (action.tag()) {
      case Action::Tag::None:
        break;
      case Action::Tag::Move:
        this->move(actor->position(), action.get<Action::Tag::Move>());
        break;
      }
    }
  }
}

inline void Scene::draw(std::vector<char> &buffer) const {
  for (auto y= 0, height= this->height(); y < height; y++)
    for (auto x= 0, width= this->width(); x < width; x++)
      buffer.emplace_back(this->map->at(x, y));

  for (auto const &actor : actors) {
    auto position= actor->position();
    buffer[position.y * this->width() + position.x]= actor->representation();
  }
}

inline int Scene::width() const { return this->map->width(); }
inline int Scene::height() const { return this->map->height(); }
}

#endif