#include "Screen.h"
#include <iostream>

Screen::Screen():
  m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), x(60), y(90) {
}

bool Screen::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return false;
  }

  m_window = SDL_CreateWindow(
      "Particle Fire Explosion",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_SHOWN
      );

  if (m_window == NULL) {
    SDL_Quit();
    return false;
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
  m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT); 

  if (m_renderer == NULL) {
    // refactor destruction of objects into one function
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }

  if (m_texture == NULL) {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }

  m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

  memset(m_buffer1, 255, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

  return true;
}

void Screen::clear() {
  memset(m_buffer1, 255, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
}

bool Screen::processEvents() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return false;
    } else if (event.type == SDL_KEYDOWN) {
      const Uint8 *state = SDL_GetKeyboardState(NULL);
      if (state[SDL_SCANCODE_RIGHT]) {
        std::cout << "Right Keys Pressed.\n";
        x++;
      } else if (state[SDL_SCANCODE_LEFT]) {
        std::cout << "Left Keys Pressed.\n";
        x--;
      } else if (state[SDL_SCANCODE_DOWN]) {
        std::cout << "Down Keys Pressed.\n";
        y--;
      /* } else if (state[SDL_SCANCODE_UP]) { */
      /*   std::cout << "Up Keys Pressed.\n"; */
      /*   y++; */
      }
    }
  }
  return true;
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
    return;
  }

  Uint32 color = 0;

  color += red;
  color <<= 8;
  color += green;
  color <<= 8;
  color += blue;
  color <<= 8;
  color += 0xFF;

  m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}

void Screen::update() {
  SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH*sizeof(Uint32));
  SDL_RenderClear(m_renderer);
  SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
  SDL_RenderPresent(m_renderer);
}

void Screen::close() {
  delete[] m_buffer1;
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyTexture(m_texture);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}