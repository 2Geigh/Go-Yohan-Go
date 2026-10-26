#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <stdbool.h>

#define SDL_FLAGS SDL_INIT_VIDEO

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static int WIDTH = 160;
static int HEIGHT = 144;

// This function is equivalent to the init() function in Go
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  SDL_SetAppMetadata("Go Yohan Go!", "1.0-SNAPSHOT",
                     "com.nicholasgarcia.goyohango.renderer-clear");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("Go Yohan Go!", 160, 144,
                                   SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_SetRenderLogicalPresentation(renderer, WIDTH, HEIGHT,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);

  return SDL_APP_CONTINUE;
}

// This function is the handler for user-generated events
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {

  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  const double now =
      ((double)SDL_GetTicks()) / 1000.0; // Convert from milliseconds to seconds

  const float pink = (float)(0.5 + 0.5 * SDL_sin(now));
  const float white = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
  const float cyan = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

  // This is essentially setting the colour of the renderer's current pen/brush
  SDL_SetRenderDrawColorFloat(renderer, pink, white, cyan,
                              SDL_ALPHA_OPAQUE_FLOAT);

  // Clear the current rendering target with the last-set draw colour
  SDL_RenderClear(renderer);

  // Display the new rendering
  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE;
}

// Like an inverse of SDL_AppInit, SDL3 runs this function once at shutdown
void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  /* SDL will clean up the window/renderer for us. */
}
