#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include <SDL2/SDL.h>

#include "objLoader.hpp"
#include "camera.hpp"
#include "texture.hpp"
//#include "Light.hpp"

// Forward Declaration
//struct STLFile;
struct objLoader;

struct Global{

    Camera gCamera;

    GLenum gPolygonMode = GL_FILL;

    objLoader* myObj;

    Texture gTexture;

    int gScreenWidth 						= 640;
    int gScreenHeight 						= 480;
    SDL_Window* gGraphicsApplicationWindow 	= nullptr;
	SDL_GLContext gOpenGLContext			= nullptr;

	// Main loop flag
	bool gQuit = false; // If this is quit = 'true' then the program terminates.

};

// External linkage such that the
// global variable is available
// everywhere.
extern Global g;

#endif
