#include <iostream>


#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>

#include <glm/glm.hpp>

#include "render/Renderer.h"
#include "render/RenderResources.h"
#include "game_objects/SpriteComponent.h"
#include "common/TimeCounter.h"
using namespace glm;
using namespace std;

SDL_Window *initWindow(int width, int height, const char * title);
SDL_GLContext createContext(SDL_Window *window) { return SDL_GL_CreateContext(window); }

//--------config--------
const int screen_size = 600;
const float wasd_move_step_size = (20.0f / screen_size);
const float scaling_step = 2.0f;
const bool vSync = false;

//--------description---
// game_field texture -> render with gol shader to postTexture -> render postTexture to screenQuad -> swap this textures
//
//


int main(int argc, char *argv[]) {
    auto window = initWindow(screen_size, screen_size, "GL_game_of_life");
    auto context = createContext(window);

    Renderer renderer;

    TextureDescription gameMapTexture("game_field", "sprites/gol.png");

    FboDescription postProcFBO("postFBO", "postTexture", screen_size, screen_size);

    //game of life logic shader
    //texture - game of life field texture(screensize^2) white pixel - alive, black - dead
    //paused(uniform) ==0 - false , != 0 - true
    ShaderDescription golShader("golShader",
                                "shaders/gameoflife.vert", "shaders/gameoflife.frag",

                                {{0, 2, "a_Position"}, //0 - index, 2 - for x y
                                 {1, 4, "a_Color"},  // 4 - rgba
                                 {2, 2, "a_Texture"}}, // 2 - uv

                                {{"s_texture",   0}, //uniforms
                                 {"paused",      0},
                                 {"screen_size", static_cast<float>(screen_size)}},

                                GL_TRIANGLES);

    ShaderDescription basicSpriteShader(
            "postProcShader",
            "shaders/basic_sprite.vert", "shaders/basic_sprite.frag",

            {{0, 2, "a_Position"}, //2 for xy
             {1, 4, "a_Color"},
             {2, 2, "a_Texture"}},

            {{"s_texture", 0}},

            GL_TRIANGLES
    );


    auto &resourceManager = renderer.getResourceManager();
    resourceManager.loadResource(postProcFBO);
    resourceManager.loadResource(basicSpriteShader);
    resourceManager.loadResource(golShader);
    resourceManager.loadResource(gameMapTexture);


    SpriteComponent golScreenQuad(Vec2(0.0f, 0.0f), 0.0f, 1.0f, 0, resourceManager.getShaderHandle("golShader"),
                                  resourceManager.getTextureHandle("game_field"),
                                  resourceManager.getFBOhandle("postFBO"));


    SpriteComponent fullScreenQuad(Vec2(0.0f, 0.0f), 0.0f, 1.0f, 0, resourceManager.getShaderHandle("postProcShader"),
                                   resourceManager.getTextureHandle("postTexture"),
                                   resourceManager.getFBOhandle("screen"));


    TimeCounter totalFrameClock;
    TimeCounter renderingClock;
    TimeCounter inputClock;


    bool running = true;
    bool paused = true;

    bool oneFramePassed = true;


    SDL_GL_SetSwapInterval(vSync ? 1 : 0);
    while (running) {
        totalFrameClock.start();

        inputClock.start();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    auto key_event = event.key.keysym.sym;
                        if(key_event == SDLK_p)
                            cout << totalFrameClock.getTime() << endl;

                        if(key_event == SDLK_ESCAPE)
                            running = false;

                        if(key_event ==  SDLK_SPACE)
                            paused = !paused;

                        if (key_event == SDLK_RIGHT)
                            oneFramePassed = false;

                        if (key_event == SDLK_w)
                            fullScreenQuad.position.y -= wasd_move_step_size;

                        if (key_event == SDLK_a)
                            fullScreenQuad.position.x += wasd_move_step_size;

                        if (key_event == SDLK_s)
                            fullScreenQuad.position.y += wasd_move_step_size;

                        if  (key_event == SDLK_d)
                            fullScreenQuad.position.x -= wasd_move_step_size;

                        if (key_event == SDLK_UP)
                            fullScreenQuad.scale *= scaling_step;

                        if(key_event == SDLK_DOWN)
                            fullScreenQuad.scale /= scaling_step;
                    break;
            }
        }
        inputClock.stop();


        renderingClock.start();

        //passing paused value to gol shader
        if (!paused || !oneFramePassed) {
            oneFramePassed = true;
            golScreenQuad.shaderHandle.obj->setUniformValue("paused", 0);
        } else {
            golScreenQuad.shaderHandle.obj->setUniformValue("paused", 1);
        }

        golScreenQuad.prepareRenderCommand(renderer);
        fullScreenQuad.prepareRenderCommand(renderer);


        renderer.renderScheduledCommands();

        //swapping textures
        golScreenQuad.fboHandle.obj->useTextureAsColorBuffer(*golScreenQuad.textureHandle.obj);
        std::swap(golScreenQuad.textureHandle, fullScreenQuad.textureHandle);

        SDL_GL_SwapWindow(window);



        renderingClock.stop();
        totalFrameClock.stop();
    }
    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}

SDL_Window *initWindow(int width, int height, const char * title) {
    SDL_Window *window;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    window = SDL_CreateWindow(
            title,                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            width,                               // width, in pixels
            height,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
    );
    // Check that the window was successfully created
    if (window == NULL) {
        //TODO: real error logging
        // In the case that the window could not be made...
        //printf("Could not create window: %s\n", SDL_GetError());
        //return 1;
    }

    return window;
}
