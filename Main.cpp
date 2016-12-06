#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <memory>
#include <string>
#include <vector>
#include "Ball.hpp"
#include "Bob.hpp"
#include "IO.hpp"
#include "Texture.hpp"
#include "Timer.hpp"
#include "WindowInit.hpp"
#include "TextureContainer.hpp"

// Frees media and shuts down SDL
void close();
void load();

// The window we'll be rendering to
SDL_Window* m_window = NULL;
SDL_Window& windowRef = *m_window;

// The window renderer
SDL_Renderer* m_renderer = NULL;
SDL_Renderer& rendererRef = *m_renderer;
std::shared_ptr<Bob> bob_c;
std::shared_ptr<TextureContainer> t_container;

void close() {
  bob_c->clear();
  t_container->clear();
  // Destroy window
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  m_window = NULL;
  m_renderer = NULL;

  // Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

void load() {
  bob_c = std::make_shared<Bob>(m_renderer);
  t_container = std::make_shared<TextureContainer>(m_renderer);
}

int main(int argc, char* args[]) {
  /*Initialise windows*/
  if (!init(m_window, m_renderer)) {
    printf("Failed to initialize!\n");
    return 1;
  }

  // Textures
  load();

  bool quit = false;

  SDL_Event e;

  int bg_scroller_div = 5;
  int floor_scroller_div = 4;
  int bg_scroller_offset = 0;
  int floor_scroller_offset = 0;

  while (!quit) {
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        // Select surfaces based on key press
        switch (e.key.keysym.sym) {
          case SDLK_UP:
          case SDLK_SPACE:
            bob_c->set_jump();
            break;
          default:
            break;
        }
      }
    }

    // Clear screen
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(m_renderer);

    t_container->run(m_renderer);
    bob_c->run(m_renderer);

    // Update screen
    SDL_RenderPresent(m_renderer);
  }

  // Free resources and close SDL
  close();
  return 0;
}
