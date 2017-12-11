#define Run_GLFW 0
#define Run_SDL  0
#define Run_SFML 0
#define Run_APIs 1


#if Run_SFML
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(600, 600), "SFML WINDOW");
  sf::CircleShape shape(300.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();
  }

  return 0;
}
#endif

#if Run_GLFW
#include <iostream>
#include <GLFW/glfw3.h>

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main()
{
  std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
  // Init GLFW
  glfwInit();
  // Set all the required options for GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Create a GLFWwindow object that we can use for GLFW's functions
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GLFW WINDOW", NULL, NULL);
  glfwMakeContextCurrent(window);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Set the required callback functions
  glfwSetKeyCallback(window, key_callback);


  // Define the viewport dimensions
  glViewport(0, 0, WIDTH, HEIGHT);

  // Game loop
  while (!glfwWindowShouldClose(window))
  {
    // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
    glfwPollEvents();

    // Render
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap the screen buffers
    glfwSwapBuffers(window);
  }

  // Terminates GLFW, clearing any resources allocated by GLFW.
  glfwTerminate();
  return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  std::cout << key << std::endl;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
#endif

#if Run_SDL
//Using SDL and standard IO
#define SDL_MAIN_HANDLED //Stops SDL from being stupid with main
#include <stdio.h>
#include <SDL\SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
  //The window we'll be rendering to
  SDL_Window* window = NULL;

  //The surface contained by the window
  SDL_Surface* screenSurface = NULL;

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  }

  else
  {
    //Create window
    window = SDL_CreateWindow("SDL WINDOW", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    else
    {
      //Get window surface
      screenSurface = SDL_GetWindowSurface(window);

      //Fill the surface white
      SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

      //Update the surface
      SDL_UpdateWindowSurface(window);

      //Wait two seconds
      SDL_Delay(3000);


    }
  }

  //Destroy window
  SDL_DestroyWindow(window);

  //Quit SDL subsystems
  SDL_Quit();

  return 0;
}
#endif

#if Run_APIs

#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <SDL/SDL.h>
#include <SFML/Window.hpp>
//#include <SInput/SInput.hpp>
//#include <IMGUI/imgui.h>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }

  if (action == GLFW_PRESS)
  {
    std::cout << key << std::endl;
  }
}

static void focus_callback(GLFWwindow* window, int focused)
{
  if (focused)
  {
    std::cout << "GLFW Window Gained Focus!" << std::endl;
  }
}

int main(int argc, char* args[])
{

  //Find Monitor 1 size

  GLFWwindow* glfw_window;

  /* Initialize the library */
  if (!glfwInit())
  {
    return -1;
  }

  /* Create a windowed mode window and its OpenGL context */
  glfw_window = glfwCreateWindow(720, 540, "GLFW Window", NULL, NULL);

  if (!glfw_window)
  {
    glfwTerminate();
    return -1;
  }

  glfwSetWindowPos(glfw_window, 1, 30);
  glfwSetKeyCallback(glfw_window, key_callback);
  glfwSetWindowFocusCallback(glfw_window, focus_callback);

  //The window we'll be rendering to
  SDL_Window* sdl_window = NULL;

  //The surface contained by the window
  SDL_Surface* screenSurface = NULL;

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  else
  {
    //Create window
    sdl_window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 540, SDL_WINDOW_SHOWN);

    if (sdl_window == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      return -1;
    }
  }

  SDL_SetWindowPosition(sdl_window, 722, 30);

  sf::Window sfml_window(sf::VideoMode(720, 540), "SFML Window");
  sfml_window.setPosition(sf::Vector2i(-7, 570));

  bool quit = false;

  // run the program as long as the window is open
  while (sfml_window.isOpen() | !glfwWindowShouldClose(glfw_window) | !quit)
  {
    if (sfml_window.isOpen())
    {
      // check all the window's events that were triggered since the last iteration of the loop
      sf::Event event;
      while (sfml_window.pollEvent(event))
      {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
        {
          sfml_window.close();
        }

        if (event.type == sf::Event::GainedFocus)
        {
          std::cout << "SFML Window Gained Focus!" << std::endl;
        }

        if (event.type == sf::Event::KeyPressed)
        {
          std::cout << event.key.code << std::endl;
        }
      }
    }

    if (!glfwWindowShouldClose(glfw_window))
    {
      /* Render here */
      glClear(GL_COLOR_BUFFER_BIT);

      /* Swap front and back buffers */
      glfwSwapBuffers(glfw_window);

      /* Poll for and process events */
      glfwPollEvents();
    }
    else
    {
      if (glfw_window)
      {
        glfwTerminate();
      }
    }

    if (!quit)
    {
      SDL_Event e;

      while (SDL_PollEvent(&e) != 0)
      {
        //User requests quit
        if (e.type == SDL_QUIT)
        {
          quit = true;
        }

        if (e.type == SDL_WINDOWEVENT)
        {
          if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
          {
            std::cout << "SDL Window Gained Focus!" << std::endl;
          }
        }

        if (e.type == SDL_KEYDOWN)
        {
          std::cout << e.key.keysym.sym << std::endl;
        }
      }

    }
    else
    {
      //Destroy window
      SDL_DestroyWindow(sdl_window);

      //Quit SDL subsystems
      SDL_Quit();
    }
  }

  return 0;
}

#endif