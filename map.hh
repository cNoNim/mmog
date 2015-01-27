#ifndef MMOG_MAP_HH
#define MMOG_MAP_HH
#pragma once

#include <vector>
#include "point.hh"

namespace mmog {
  class Map {
  public:
    template<typename V>
    explicit Map(V && map, int width, int height);

    char & at(int x, int y);
    char const & at(int x, int y) const;

    char & at(point const & pt) { return at(pt.x, pt.y); }
    char const & at(point const & pt) const { return at(pt.x, pt.y); }

    char & operator[] (point const & pt) { return at(pt); }
    char const & operator[] (point const & pt) const { return at(pt); }

    int width() const { return this->w; }
    int height() const { return this->h; }

  private:
    std::vector<char> map;
    int w;
    int h;
  };
}

namespace mmog {
  template<typename V>
  inline Map::Map(V && map, int width, int height) : map(std::forward<V>(map)), w(width), h(height) {
  }

  inline char & Map::at(int x, int y) {
    return this->map[y * this->width() + x];
  }

  inline char const & Map::at(int x, int y) const {
    return this->map[y * this->width() + x];
  }
}

#endif