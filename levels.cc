#include "map.hh"
#include "scene.hh"

#include <algorithm>
#include <iterator>
#include <string>
#include <unordered_map>
#include <memory>

struct Exit {
  enum class Function {
    Load, Jump
  } function;
  std::string name;
  enum class Direction {
    None, Up, Left, Down, Right
  } direction;
};

static constexpr Exit::Function load = Exit::Function::Load;
static constexpr Exit::Function jump = Exit::Function::Jump;

static constexpr Exit::Direction none = Exit::Direction::None;
static constexpr Exit::Direction up = Exit::Direction::Up;
static constexpr Exit::Direction left = Exit::Direction::Left;
static constexpr Exit::Direction down = Exit::Direction::Down;
static constexpr Exit::Direction right = Exit::Direction::Right;


static struct {
  std::string name;
  int width; int height;
  std::string map;
  std::unordered_map<char, std::string> actors;
  std::unordered_map<char, Exit> exits;
} levels[] = {
#include "levels/maze.ii"
#include "levels/secret.ii"
#include "levels/boss.ii"
};

class Scene;
class Actor;

static void throw_unknown_level_error(std::string const &name);

namespace mmog {
  std::unique_ptr<Scene> loadLevel(std::string const &name) {
    auto level = std::find_if(std::begin(levels), std::end(levels), [&name](auto const &l) { return name == l.name; });
    if (level == std::end(levels))
      throw_unknown_level_error(name);
    auto map = std::vector<char>(std::begin(level->map), std::end(level->map));
    std::vector<std::unique_ptr<Actor>> actors;
    int x = 0; int y = 0;
    for (auto & ch : map) {
      if (level->actors.count(ch) != 0) {
        actors.emplace_back(loadActor(level->actors[ch], x, y));
        ch = '.';
      }
      x++;
      if (x >= level->width) { y++; x = 0; }
    }
    return std::make_unique<Scene>(std::make_unique<Map>(map, level->width, level->height), std::move(actors));
  }
}

static void throw_unknown_level_error(std::string const &name) {
  using namespace std::string_literals;
  throw std::runtime_error("unknwon level "s + name);
}
