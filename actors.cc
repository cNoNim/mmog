#include "point.hh"
#include "action.hh"
#include "actor.hh"

#include <iostream>
#include <memory>
#include <string>
#include <queue>

static void throw_unknown_actor_error(std::string const &name);

namespace mmog {

  struct temp {
  };

  class Player : public Actor {
  public:
    Player(point p) : Actor('+', p) {}
    virtual void update(std::weak_ptr<void> data) {
      auto t = std::static_pointer_cast<temp>(data.lock());
      std::string line;
      std::cout << ">";
      std::getline(std::cin, line);
      for (auto &&ch : line) {
        switch (ch)
        {
        case 'w': this->queue.emplace(Action::move(Action_Direction::Up)); break;
        case 'a': this->queue.emplace(Action::move(Action_Direction::Left)); break;
        case 's': this->queue.emplace(Action::move(Action_Direction::Down)); break;
        case 'd': this->queue.emplace(Action::move(Action_Direction::Right)); break;
        }
      }
    }
    virtual bool empty() const {
      return queue.empty();
    }
    virtual Action step() {
      if (queue.empty()) {
        return Action::none();
      }
      auto action = queue.front();
      queue.pop();
      return action;
    }
  private:
    std::queue<Action> queue;
  };

  class Cerberus : public Actor {
  public:
    Cerberus(point p) : Actor('@', p) {}
    virtual void update(std::weak_ptr<void> data) {}
    virtual bool empty() const {
      return true;
    }
    virtual Action step() {
      return Action::none();
    }
  };
}

static struct { std::string name; std::unique_ptr<mmog::Actor>(*factory)(mmog::point); } actors[] = {
  { "player", [](auto p) ->  std::unique_ptr<mmog::Actor> { return std::make_unique<mmog::Player>(p); } },
  { "cerberus", [](auto p) ->  std::unique_ptr<mmog::Actor> { return std::make_unique<mmog::Cerberus>(p); } }
};

namespace mmog {
  std::unique_ptr<Actor> loadActor(std::string const &name, int x, int y) {
    auto actor = std::find_if(std::begin(actors), std::end(actors), [&name](auto const &a) { return name == a.name; });
    if (actor == std::end(actors))
      throw_unknown_actor_error(name);
    return actor->factory({x, y});
  }
}

static void throw_unknown_actor_error(std::string const &name) {
  using namespace std::string_literals;
  throw std::runtime_error("unknwon actor "s + name);
}
