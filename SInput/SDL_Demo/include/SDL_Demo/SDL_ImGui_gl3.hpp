

struct SDL_Window;
typedef union SDL_Event SDL_Event;

IMGUI_API bool        SDL_ImGui_GL3_Init(SDL_Window* window);
IMGUI_API void        SDL_ImGui_GL3_Shutdown();
IMGUI_API void        SDL_ImGui_GL3_NewFrame(SDL_Window* window);
IMGUI_API bool        SDL_ImGui_GL3_ProcessEvent(SDL_Event* event);

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_API void        SDL_ImGui_GL3_InvalidateDeviceObjects();
IMGUI_API bool        SDL_ImGui_GL3_CreateDeviceObjects();

// GLFW callbacks (installed by default if you enable 'install_callbacks' during initialization)
// Provided here if you want to chain callbacks.
// You can also handle inputs yourself and use those as a reference.
IMGUI_API void        SDL_ImGui_GL3_MouseButtonCallback(SDL_Window* window, int button, int action, int mods);
IMGUI_API void        SDL_ImGui_GL3_ScrollCallback(SDL_Window* window, double xoffset, double yoffset);
IMGUI_API void        SDL_ImGui_GL3_KeyCallback(SDL_Window* window, int key, int scancode, int action, int mods);
IMGUI_API void        SDL_ImGui_GL3_CharCallback(SDL_Window* window, unsigned int c);

IMGUI_API void        SDL_ImGui_GL3_ShowLog(bool* p_open);

