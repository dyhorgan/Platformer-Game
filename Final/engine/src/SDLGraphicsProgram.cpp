#include "SDLGraphicsProgram.hpp"
#include "Camera.hpp"
#include "Terrain.hpp"
#include "Sphere.hpp"
#include "Canvas.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h){
	// Initialization flag
	bool success = true;
	// String to hold any errors that occur.
	std::stringstream errorStream;
	// The window we'll be rendering to
	m_window = NULL;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)< 0){
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else{
		//Use OpenGL 3.3 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		// We want to request a double buffer for smooth updating.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		//Create window
		m_window = SDL_CreateWindow( "Lab",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                w,
                                h,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

		// Check if Window did not create.
		if( m_window == NULL ){
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Create an OpenGL Graphics Context
		m_openGLContext = SDL_GL_CreateContext( m_window );
		if( m_openGLContext == NULL){
			errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		// Initialize GLAD Library
		if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
			errorStream << "Failed to iniitalize GLAD\n";
			success = false;
		}

		//Initialize OpenGL
		if(!InitGL()){
			errorStream << "Unable to initialize OpenGL!\n";
			success = false;
		}
  	}

    // If initialization did not work, then print out a list of errors in the constructor.
    if(!success){
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors=errorStream.str();
        SDL_Log("%s\n",errors.c_str());
    }else{
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

	// SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // Uncomment to enable extra debug support!
	GetOpenGLVersionInfo();


    // Setup our Renderer
    m_renderer = new Renderer(w,h);    
}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    if(m_renderer!=nullptr){
        delete m_renderer;
    }


    //Destroy window
	SDL_DestroyWindow( m_window );
	// Point m_window to NULL to ensure it points to nothing.
	m_window = nullptr;
	//Quit SDL subsystems
	SDL_Quit();
}


// Initialize OpenGL
// Setup any of our shaders here.
bool SDLGraphicsProgram::InitGL(){
	//Success flag
	bool success = true;

	return success;
}

// ====================== Create the planets =============
// NOTE: I will admit it is a little lazy to have these as globals,
//       we could build on our ObjectManager structure to manage the
//       each object that is inserted and automatically create a 'SceneNode'
//       for it for example. Or otherwise, build a 'SceneTree' class that
//       manages creating nodes and setting their type.
//       (e.g. A good use of the Factory Design Pattern if you'd like to
//             invetigate further--but it is beyond the scope of this assignment).

// Create the Moon
Object* sphere3;
SceneNode* Moon;
// Create the Earth
Object* sphere2;
SceneNode* Earth;
// Create the Sun
Object* sphere;
SceneNode* Sun;

Object* canvas;
SceneNode* background;
// ====================== Create the planets =============

//Loops forever!
void SDLGraphicsProgram::Loop(){

    // ================== Initialize the planets ===============
    static float rotate = 0.05f;
    float moonRotate = 0.05;


    // Create new geometry for Earth's Moon
    sphere3 = new Sphere();
    sphere3->LoadTexture("rock.ppm");
    // Create a new node using sphere3 as the geometry
    Moon = new SceneNode(sphere3);

    // Create the Earth
    sphere2 = new Sphere();
    sphere2->LoadTexture("earth.ppm");
    Earth = new SceneNode(sphere2);

    // Create the Sun
    sphere = new Sphere();
    sphere->LoadTexture("sun.ppm");
    Sun = new SceneNode(sphere);
    
    canvas = new Canvas();
    canvas->LoadTexture("opeth.ppm");
    background = new SceneNode(canvas);
    

    //background = new

    // Render our scene starting from the sun.
    m_renderer->setRoot(Sun);
    // Make the Earth a child of the Sun
    Sun->AddChild(Earth);
    // Make the Moon a child of the Earth
    Earth->AddChild(Moon);

    Sun->AddChild(background);
    
    // Set a default position for our camera
    m_renderer->GetCamera(0)->SetCameraEyePosition(0.0f,2.0f,20.0f);

    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();

    // Set the camera speed for how fast we move.
    float cameraSpeed = 5.0f;

    // While application is running
    while(!quit){

        //Handle events on queue
        while(SDL_PollEvent( &e ) != 0){
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if(e.type == SDL_QUIT){
                quit = true;
            }
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
			    std::cout << "ESC: Goodbye! (Leaving MainApplicationLoop())" << std::endl;
                quit = true;
            }
            // Handle keyboard input for the camera class
            if(e.type==SDL_MOUSEMOTION){
                // Handle mouse movements
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
                //m_renderer->GetCamera(0)->MouseLook(mouseX, mouseY);
            }

            /*
            switch(e.type){
                // Handle keyboard presses
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case SDLK_LEFT:
                            m_renderer->GetCamera(0)->MoveLeft(cameraSpeed);
                            break;
                        case SDLK_RIGHT:
                            m_renderer->GetCamera(0)->MoveRight(cameraSpeed);
                            break;
                        case SDLK_UP:
                            m_renderer->GetCamera(0)->MoveForward(cameraSpeed);
                            break;
                        case SDLK_DOWN:
                            m_renderer->GetCamera(0)->MoveBackward(cameraSpeed);
                            break;
                        case SDLK_RSHIFT:
                            m_renderer->GetCamera(0)->MoveUp(cameraSpeed);
                            break;
                        case SDLK_RCTRL:
                            m_renderer->GetCamera(0)->MoveDown(cameraSpeed);
                            break;
                    }
                break;
            }
            */
        } 

        // Retrieve keyboard state
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    /*
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
    */

    // Camera
    // Update our position of the camera
    if (state[SDL_SCANCODE_W]) {
        //m_renderer->GetCamera(0)->MoveForward(0.1f);
        m_renderer->GetCamera(0)->MoveUp(0.1f);
    }
    if (state[SDL_SCANCODE_S]) {
        //m_renderer->GetCamera(0)->MoveBackward(0.1f);
        m_renderer->GetCamera(0)->MoveDown(0.1f);
    }
    
    if (state[SDL_SCANCODE_A]) {
        m_renderer->GetCamera(0)->MoveLeft(0.1f);
    }	
    if (state[SDL_SCANCODE_D]) {
       m_renderer->GetCamera(0)->MoveRight(0.1f);
    }
    
    if (state[SDL_SCANCODE_UP]) {
        m_renderer->GetCamera(0)->MoveForward(0.1f);
    }
	if (state[SDL_SCANCODE_DOWN]) {
        m_renderer->GetCamera(0)->MoveBackward(0.1f);
    }
    

        // End SDL_PollEvent loop.
        // ================== Use the planets ===============
        // TODO:
        //      After the planets have been created, and the hierarchy
        //      has been made, you can transform them.
        //      Note, you'll need to setup the scene graph world/local
        //      transformation correctly first before the planets are shown.
        //      
        //      The 'Sun' for example will be the only object shown initially
        //      since the rest of the planets are children (or grandchildren)
        //      of the Sun.
       
        Sun->GetLocalTransform().LoadIdentity();	
        // ... transform the Sun

        Moon->GetLocalTransform().LoadIdentity();	
        // ... transform the Moon
        
        Moon->GetLocalTransform().Translate(7.0,0.0,0.0);
        	
        Earth->GetLocalTransform().LoadIdentity();		
        // ... transform the Earth
        
        Earth->GetLocalTransform().Translate(7.0,0.0,0.0);

        background->GetLocalTransform().LoadIdentity();
        background->GetLocalTransform().Scale(8.0,8.0,8.0);

        //background->GetLocalTransform().Translate(1.0, 0.0, 0.0);

        // Update our scene through our renderer
        m_renderer->Update();
        // Render our scene using our selected renderer
        m_renderer->Render();
        // Delay to slow things down just a bit!
        SDL_Delay(25);  // TODO: You can change this or implement a frame
                        // independent movement method if you like.
      	//Update screen of our specified window
      	SDL_GL_SwapWindow(GetSDLWindow());
        rotate += 0.03;
        moonRotate += 0.15;
	}
    //Disable text input
    SDL_StopTextInput();
}


// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::GetSDLWindow(){
  return m_window;
}

// Helper Function to get OpenGL Version Information
void SDLGraphicsProgram::GetOpenGLVersionInfo(){
	SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
	SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
	SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
	SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
	SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}
