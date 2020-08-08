#pragma once
#include <SDL2/SDL.h>

class Screen {
  public:
    const static int SCREEN_WIDTH = 1200;
    const static int SCREEN_HEIGHT = 1000;
  private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture; 
    Uint32 *m_buffer1;

  public:
    int x;
    int y;
    int size;
    Screen();
    bool init();
    bool processEvents();
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    void update();
    void clear();
    void close();
};
