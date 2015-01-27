#include "actors/cerberus.hh"
#include "actors/dummy.hh"
#include "actors/player.hh"

#include <algorithm>
#include <stdexcept>
#include <string>

static void throw_unknown_actor_error(std::string const &name);

static struct {
  std::string name;
  std::unique_ptr<mmog::Actor>(*factory)(mmog::point);
} actors[] = {{"dummy", [](auto p) -> std::unique_ptr<mmog::Actor> {
                return std::make_unique<mmog::Dummy>(p);
              }},
              {"cerberus", [](auto p) -> std::unique_ptr<mmog::Actor> {
                return std::make_unique<mmog::Cerberus>(p);
              }},
              {"player", [](auto p) -> std::unique_ptr<mmog::Actor> {
                return std::make_unique<mmog::Player>(p);
              }}};

namespace mmog {
std::unique_ptr<Actor> loadActor(std::string const &name, int x, int y) {
  auto actor = std::find_if(std::begin(actors),
                            std::end(actors),
                            [&name](auto const &a) { return name == a.name; });
  if (actor == std::end(actors)) throw_unknown_actor_error(name);
  return actor->factory({x, y});
}
}

static void throw_unknown_actor_error(std::string const &name) {
  using namespace std::string_literals;
  throw std::runtime_error("unknwon actor "s + name);
}
