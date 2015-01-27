#ifndef MMOG_ACTION_HH
#define MMOG_ACTION_HH
#pragma once

namespace mmog {

  enum class Action_Tag { None, Move };
  enum class Action_Direction { Up, Left, Down, Right };

  class Action {
  public:
    using Tag = Action_Tag;
    using Direction = Action_Direction;

    template<Tag tag>
    struct tag_t { static constexpr Tag value() { return tag; } };
    using none_t = tag_t<Tag::None>;
    using move_t = tag_t<Tag::Move>;

    static Action none() {
      return Action(none_t());
    }
    static Action move(Direction direction) {
      return Action(move_t(), direction);
    }

    Tag tag() const {
      return t;
    }
    template<Tag tag>
    auto & get() {
      return get(tag_t<tag>());
    }
    template<Tag tag>
    auto const & get() const {
      return get(tag_t<tag>());
    }

  private:
    Action(move_t t, Direction direction) : t(t.value()), d(direction) { }
    template<typename T>
    Action(T t) : t(t.value()) { }

    Direction & get(move_t) {
      return d;
    }
    Direction const & get(move_t) const {
      return d;
    }

    Tag t;
    union { Direction d; };
  };

}

#endif
