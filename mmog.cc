#include "scene.hh"

#include <chrono>
#include <iostream>
#include <memory>
#include <string>

class GameLogic {
	using time_t = std::chrono::system_clock::time_point;

	enum class State {
		Game, Fail, Win
	};
public:
	GameLogic(std::string const &levelName)
		: level(std::move(mmog::loadLevel(levelName))) {
	}

	bool update() {
    this->level->update();
		return State::Game == this->state;
	}

	void draw() {
    render_target.clear();
    this->level->draw(render_target);
    int x = 0;
    for (auto const & c : render_target) {
      std::cout << c;
      x++;
      if (x >= this->level->width()) {
        std::cout << std::endl;
        x = 0;
      }
    }
    std::cout << std::flush;
	}

	void finish() {
		std::cout << "Press [ENTER] to exit." << std::endl;
		std::cin.ignore();
	}

private:

	std::shared_ptr<mmog::Scene> level;
	State state = State::Game;
  std::vector<char> render_target;
};

int main(int argc, char *argv[])
try {
	auto game = GameLogic("maze");
	while (game.update()) {
		game.draw();
	}
	game.finish();
	return 0;
}
catch (std::runtime_error const & e) {
	std::cerr << e.what() << std::endl;
	throw;
}