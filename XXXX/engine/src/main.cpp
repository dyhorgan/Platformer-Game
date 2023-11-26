
/* Compilation on Linux: 
 g++ -std=c++17 ./src/*.cpp -o prog -I ./include/ -I./../common/thirdparty/ -lSDL2 -ldl
*/

// Third Party Libraries
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> 

// C++ Standard Template Library (STL)
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Our libraries
#include "camera.hpp"
#include "texture.hpp"
#include "objLoader.hpp"
#include "utils.hpp"

#include "globals.hpp"

float g_uOffset=-2.0f;
float g_uRotate=0.0f;

void CreateGraphicsPipeline(){

    std::string vertexShaderSource      = LoadShaderAsString("./shaders/vert.glsl");
    std::string fragmentShaderSource    = LoadShaderAsString("./shaders/frag.glsl");

	g.myObj->mShaderID = CreateShaderProgram(vertexShaderSource,fragmentShaderSource);
}




/**
* Initialization of the graphics application. Typically this will involve setting up a window
* and the OpenGL Context (with the appropriate version)
*
* @return void
*/
void InitializeProgram(){
	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)< 0){
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		exit(1);
	}
	
	// Setup the OpenGL Context
	// Use OpenGL 4.1 core or greater
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	// We want to request a double buffer for smooth updating.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Create an application window using OpenGL that supports SDL
	g.gGraphicsApplicationWindow = SDL_CreateWindow( "OpenGL First Program",
													SDL_WINDOWPOS_UNDEFINED,
													SDL_WINDOWPOS_UNDEFINED,
													g.gScreenWidth,
													g.gScreenHeight,
													SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

	// Check if Window did not create.
	if( g.gGraphicsApplicationWindow == nullptr ){
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
		exit(1);
	}

	// Create an OpenGL Graphics Context
	g.gOpenGLContext = SDL_GL_CreateContext( g.gGraphicsApplicationWindow );
	if( g.gOpenGLContext == nullptr){
		std::cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
		exit(1);
	}

	// Initialize GLAD Library
	if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
		std::cout << "glad did not initialize" << std::endl;
		exit(1);
	}

	g.myObj = new objLoader(objPath);
	g.myObj->Initialize();
	
}

/**
* Setup your geometry during the vertex specification step
*
* @return void
*/
void VertexSpecification(){
    
	// We will load a texture here prior

	
}


/**
* PreDraw
* Typically we will use this for setting some sort of 'state'
* Note: some of the calls may take place at different stages (post-processing) of the
* 		 pipeline.
* @return void
*/
void PreDraw(){

	g.myObj->PreDraw();

}



/**
* Draw
* The render function gets called once per loop.
* Typically this includes 'glDraw' related calls, and the relevant setup of buffers
* for those calls.
*
* @return void
*/
void Draw(){
  g.myObj->Draw();
}


/**
* Helper Function to get OpenGL Version Information
*
* @return void
*/
void getOpenGLVersionInfo(){
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
  std::cout << "Version: " << glGetString(GL_VERSION) << "\n";
  std::cout << "Shading language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
}


/**
* Function called in the Main application loop to handle user input
*
* @return void
*/
void Input(){
	// Event handler that handles various events in SDL
	// that are related to input and output
	SDL_Event e;
	//Handle events on queue
	while(SDL_PollEvent( &e ) != 0){
		// If users posts an event to quit
		// An example is hitting the "x" in the corner of the window.
		if(e.type == SDL_QUIT){
			std::cout << "Goodbye! (Leaving MainApplicationLoop())" << std::endl;
			g.gQuit = true;
		}
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
			std::cout << "ESC: Goodbye! (Leaving MainApplicationLoop())" << std::endl;
            g.gQuit = true;
        }
	}

    // Retrieve keyboard state
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP]) {
        g_uOffset+=0.01f;
        //std::cout << "g_uOffset: " << g_uOffset << std::endl;
    }
    if (state[SDL_SCANCODE_DOWN]) {
        g_uOffset-=0.01f;
        //std::cout << "g_uOffset: " << g_uOffset << std::endl;
    }
    if (state[SDL_SCANCODE_LEFT]) {
        g_uRotate-=1.0f;
        //std::cout << "g_uRotate: " << g_uRotate<< std::endl;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        g_uRotate+=1.0f;
        //std::cout << "g_uRotate: " << g_uRotate<< std::endl;
    }

    // Camera
    // Update our position of the camera
    if (state[SDL_SCANCODE_W]) {
        g.gCamera.MoveForward(0.1f);
    }
    if (state[SDL_SCANCODE_S]) {
        g.gCamera.MoveBackward(0.1f);
    }
    if (state[SDL_SCANCODE_A]) {
        g.gCamera.MoveLeft(0.1f);
    }
    if (state[SDL_SCANCODE_UP]) {
        g.gCamera.MoveUp(0.1f);
    }
	if (state[SDL_SCANCODE_DOWN]) {
        g.gCamera.MoveDown(0.1f);
    }
	if (state[SDL_SCANCODE_D]) {
        g.gCamera.MoveRight(0.1f);
    }
	if (state[SDL_SCANCODE_1] || state[SDL_SCANCODE_TAB]) {
        SDL_Delay(250); // This is hacky in the name of simplicity,
                       // but we just delay the
                       // system by a few milli-seconds to process the 
                       // keyboard input once at a time.
		
        if(g.gPolygonMode== GL_FILL){
			std::cout << "Wireframe Mode" << std::endl;
            g.gPolygonMode = GL_LINE;
        }else{
			std::cout << "Filled Mode" << std::endl;
            g.gPolygonMode = GL_FILL;
        }
    }
    // Update the mouse look of the camera
    // Center the mouse in the window
    int mouseX, mouseY;
    SDL_GetGlobalMouseState(&mouseX,&mouseY);
    g.gCamera.MouseLook(mouseX,mouseY);

}


/**
* Main Application Loop
* This is an infinite loop in our graphics application
*
* @return void
*/
void MainLoop(){

    // For the mouse look
    // Nice to center mouse in the window
    SDL_WarpMouseInWindow(g.gGraphicsApplicationWindow, 640/2,480/2);

	// While application is running
	while(!g.gQuit){
		// Handle Input
		Input();
		// Setup anything (i.e. OpenGL State) that needs to take
		// place before draw calls
		PreDraw();
		// Draw Calls in OpenGL
        // When we 'draw' in OpenGL, this activates the graphics pipeline.
        // i.e. when we use glDrawElements or glDrawArrays,
        //      The pipeline that is utilized is whatever 'glUseProgram' is
        //      currently binded.
		Draw();
		//Update screen of our specified window
		SDL_GL_SwapWindow(g.gGraphicsApplicationWindow);
	}
}



/**
* The last function called in the program
* This functions responsibility is to destroy any global
* objects in which we have create dmemory.
*
* @return void
*/
void CleanUp(){
	//Destroy our SDL2 Window
	SDL_DestroyWindow(g.gGraphicsApplicationWindow );
	g.gGraphicsApplicationWindow = nullptr;

  // Delete our OpenGL Objects
  //GLuint vbo = g.myObj->getVBO();
  glDeleteBuffers(1, &g.myObj->gVertexBufferObject);
  //GLuint vao = g.myObj->getVAO();
  glDeleteVertexArrays(1, &g.myObj->mVAO);

	// Delete our Graphics pipeline
  //GLuint shader = g.myObj->getShaderID();
  glDeleteProgram(g.myObj->mShaderID);

	//Quit SDL subsystems
	SDL_Quit();
}


/**
* The entry point into our C++ programs.
*
* @return program status
*/
int main( int argc, char* args[] ){
  std::cout << "Use arrow keys to move and rotate\n";
	std::cout << "Use wasd to move\n";

    if(argc > 1){
       objPath = args[1];
       std::cout << "Obj Path: " << objPath << std::endl;
    }else{
        std::cout << "No arguments to read." << std::endl;
        return 0;
    }
     

	// 1. Setup the graphics program
	InitializeProgram();
	
	// 2. Setup our geometry
	VertexSpecification();
	
	// 3. Create our graphics pipeline
	// 	- At a minimum, this means the vertex and fragment shader
	CreateGraphicsPipeline();
	
	// 4. Call the main application loop
	MainLoop();	

	// 5. Call the cleanup function when our program terminates
	CleanUp();

	return 0;
}

