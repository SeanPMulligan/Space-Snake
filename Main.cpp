#include <iostream>
#include <cmath>
#include "Screen.h"

int main() {
  std::srand(std::time(NULL));

  Screen screen;

  if (!screen.init()) {
    std::cout << "Error initializing screen" << std::endl;
  }

  while (true) {
    int elapsed = SDL_GetTicks();
    unsigned char green = (1 + std::sin(elapsed * 0.002)) * 128;
    unsigned char red = (1 + std::sin(elapsed * 0.001)) * 128;
    unsigned char blue = (1 + std::sin(elapsed * 0.003)) * 128;

    screen.clear();

    for (int i = 0; i < screen.size; i++) {
      // Left Wall
      screen.setPixel(screen.x, screen.y+i, red, green, blue);
      // Top Wall
      screen.setPixel(screen.x+i, screen.y, red, green, blue);
      // Bottom Wall
      screen.setPixel(screen.x+i, screen.y+screen.size, red, green, blue);
      // Right Wall
      screen.setPixel(screen.x+screen.size, screen.y+i, red, green, blue);
    }

    screen.update();

    if (!screen.processEvents()) {
      break;
    }
  }

  screen.close();

  return 0;
}
