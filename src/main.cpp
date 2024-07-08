#include "draw.h"
#include "input.h"
#include "world.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <cstdlib>
#include <iostream>

constexpr auto timerDelay = 20;

void display(World &world, SDL_Window *window) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslated(0, 0, -70);
    Draw::drawStars();
    world.draw();
    glPopMatrix();
    SDL_GL_SwapWindow(window);
}

void perspectiveTransformations() {
    glLoadIdentity();
    gluPerspective(50, 1, 1, 100);
}

void handleKeyDown(SDL_Keycode key) {
    InputControl::setKey(key, 1);
}

void handleKeyUp(SDL_Keycode key) {
    InputControl::setKey(key, 0);
}

int main(int argc, char **args) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window =
        SDL_CreateWindow("Rymdtrish", 100, 100, 800, 640, SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        std::cerr << "SDL CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (glContext == nullptr) {
        std::cerr << "SDL CreateContext Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetSwapInterval(1);

    InputControl::resetKeys();

    auto world = World{};

    world.init();

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                handleKeyDown(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                handleKeyUp(event.key.keysym.sym);
                break;
            }
        }

        perspectiveTransformations();
        world.update(timerDelay / 1000.0);
        display(world, window);
        SDL_Delay(timerDelay);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
