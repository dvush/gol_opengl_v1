cmake_minimum_required(VERSION 3.5)
project(OpenGL_GoL)

set(CMAKE_CXX_STANDARD 11)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
include_directories(${SDL2_INCLUDE_DIRS})
set(LIBS ${LIBS} ${SDL2_LIBRARIES})
include_directories(${SDL2IMAGE_INCLUDE_DIRS})
set(LIBS ${LIBS} ${SDL2IMAGE_LIBRARIES})



set(LIBS ${LIBS} GL) #for linux

#variant
include_directories(lib/variant/include)

set(SOURCE_FILES main.cpp render/GLShader.cpp render/GLShader.h render/GLShaderProgram.cpp render/GLShaderProgram.h render/RendererQue.cpp render/RendererQue.h include/variant.h resource/TextureResource.cpp resource/TextureResource.h render/GLTexture.cpp render/GLTexture.h render/GLFbo.cpp render/GLFbo.h render/RenderResourceManager.cpp render/RenderResourceManager.h render/Renderer.cpp render/Renderer.h render/RenderResources.h game_objects/SpriteComponent.cpp game_objects/SpriteComponent.h render/DrawCommands.h common/Vectors.h common/TimeCounter.cpp common/TimeCounter.h)


add_executable(GoL ${SOURCE_FILES})
target_link_libraries(GoL ${LIBS})
