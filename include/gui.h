#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR

#if defined(__linux__)
#  define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#  define NK_INCLUDE_FONT_BAKING
#  define NK_INCLUDE_DEFAULT_FONT
#  define NK_SDL_GL2_IMPLEMENTATION
#endif

#include <nuklear.h>

// WARN:MOVE TO CMAKE CONFIG
#define GDI_UI

#if defined(__linux__)
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_opengl.h>
#elif defined(_WIN32)
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  if defined(GDIP_UI)
#    include <nuklear_gdip.h>
#  elif defined(GDI_UI)
#    include <nuklear_gdi.h>
#  endif
#endif

class App {
private:
#if   defined(__linux__)
    SDL_Window *win;
    SDL_GLContext glContext;
#elif defined(_WIN32)
#  if defined(GDIP_UI)
    GdipFont* font;
#  elif defined(GDI_UI)
    GdiFont* font;
    HDC dc;
#  endif
    WNDCLASSW wc;
    HWND wnd;
    int needs_refresh = 1;
#endif
    struct nk_context *ctx;
    struct nk_colorf bg;
    int win_width, win_height;
    int running = 1;
    const char *window_name;
public:
  App(const char *w_name, int w, int h);
  void menu();
  void loop();
  void cleanup();
};
