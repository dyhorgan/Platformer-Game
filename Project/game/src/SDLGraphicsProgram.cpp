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
    //background_renderer = new Renderer(w,h);  
}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    if(m_renderer!=nullptr){
        delete m_renderer;
    } 
    /* 
    if(background_renderer!=nullptr){
        delete background_renderer;
    }
    */


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
Object* panel3;
SceneNode* Brick3;
// Create the Earth
Object* panel2;
SceneNode* Brick2;
// Create the Sun
Object* panel;
SceneNode* Brick1;

Object* canvas;
SceneNode* background;

Object* life1;
SceneNode* BrockFace;

Object* life2;
SceneNode* BrockFace2;

Object* life3;
SceneNode* BrockFace3;

Object* sprite;
SceneNode* character;

Object* panel4;
SceneNode* Brick4;

Object* enemy;
SceneNode* Phantom;

Object* panel5;
SceneNode* Brick5;
Object* panel6;
SceneNode* Brick6;
Object* panel7;
SceneNode* Brick7;

Object* panel8;
SceneNode* Brick8;
Object* panel9;
SceneNode* Brick9;
Object* panel10;
SceneNode* Brick10;

Object* deathCanvas;
SceneNode* skull;

Object* symbol;
SceneNode* dollar;

Object* sphere;
SceneNode* Money;

Object* number1;
SceneNode* zero;

Object* number2;
SceneNode* hundred;

// ====================== Create the planets =============

//Loops forever!
void SDLGraphicsProgram::Loop(){

    // ================== Initialize the planets ===============
    static float rotate = 0.05f;
    float moonRotate = 0.05;
    float characterX = 0.0;
    float characterY = 1.8;
    float characterZ = 6.75;

    float enemyX = 12.0;
    float enemyY = -2.8;
    float enemyZ = -7.5;
    int timer = 20;
    float sceneX;
    float lastSceneX;
    float lastCharacterY;
    float sceneY;
    float sceneZ;
    bool jump = false;
    int time = 0;
    int peak = 0;
    bool doubleJump = false;
    int lives = 3;
    bool inputOn = true;
    bool frozen = false;
    float patrolNum = 0;
    bool patrolDir = true;

    // Create new geometry for Earth's Moon
    sphere = new Sphere();
    sphere->LoadTexture("dollarsigns.ppm");
    // Create a new node using sphere3 as the geometry
    Money = new SceneNode(sphere);

    // Create new geometry for Earth's Moon
    panel4 = new Canvas();
    panel4->LoadTexture("brick.ppm");
    // Create a new node using sphere3 as the geometry
    Brick4 = new SceneNode(panel4);

    // Create new geometry for Earth's Moon
    panel5 = new Canvas();
    panel5->LoadTexture("brick.ppm");
    // Create a new node using sphere3 as the geometry
    Brick5 = new SceneNode(panel5);

    // Create new geometry for Earth's Moon
    enemy = new Canvas();
    enemy->LoadTexture("monster.ppm");
    // Create a new node using sphere3 as the geometry
    Phantom = new SceneNode(enemy);

    // Create new geometry for Earth's Moon
    panel6 = new Canvas();
    panel6->LoadTexture("brick.ppm");
    // Create a new node using sphere3 as the geometry
    Brick6 = new SceneNode(panel6);

    // Create new geometry for Earth's Moon
    panel7 = new Canvas();
    panel7->LoadTexture("brick.ppm");
    // Create a new node using sphere3 as the geometry
    Brick7 = new SceneNode(panel7);

        // Create new geometry for Earth's Moon
    panel8 = new Canvas();
    panel8->LoadTexture("brick.ppm");
    // Create a new node using sphere3 as the geometry
    Brick8 = new SceneNode(panel8);

        // Create new geometry for Earth's Moon
    panel9 = new Canvas();
    panel9->LoadTexture("brick.ppm");
    // Create a new node using sphere3 as the geometry
    Brick9 = new SceneNode(panel9);

        // Create new geometry for Earth's Moon
    panel10 = new Canvas();
    panel10->LoadTexture("brick.ppm");
    // Create a new node using sphere3 as the geometry
    Brick10 = new SceneNode(panel10);

    // Create new geometry for Earth's Moon
    panel3 = new Canvas();
    panel3->LoadTexture("brick.ppm");
    // Create a new node using sphere3 as the geometry
    Brick3 = new SceneNode(panel3);

    // Create the Earth
    panel2 = new Canvas();
    panel2->LoadTexture("brick.ppm");
    Brick2 = new SceneNode(panel2);

    // Create the Sun
    panel = new Canvas();
    panel->LoadTexture("brick.ppm");
    Brick1 = new SceneNode(panel);
    
    canvas = new Canvas();
    canvas->LoadTexture("clouds.ppm");
    background = new SceneNode(canvas);

    deathCanvas = new Canvas();
    deathCanvas->LoadTexture("skull.ppm");
    skull = new SceneNode(deathCanvas);

    symbol = new Canvas();
    symbol->LoadTexture("moneybag.ppm");
    dollar = new SceneNode(symbol);

    number1 = new Canvas();
    number1->LoadTexture("num000.ppm");
    zero = new SceneNode(number1);

    number2 = new Canvas();
    number2->LoadTexture("num100.ppm");
    hundred = new SceneNode(number2);

    life1 = new Canvas();
    life1->LoadTexture("BrockFace.ppm");
    BrockFace = new SceneNode(life1);

    life2 = new Canvas();
    life2->LoadTexture("BrockFace.ppm");
    BrockFace2 = new SceneNode(life2);

    life3 = new Canvas();
    life3->LoadTexture("BrockFace.ppm");
    BrockFace3 = new SceneNode(life3);

    sprite = new Canvas();
    sprite->LoadTexture("brock.ppm");
    character = new SceneNode(sprite);

    //background = new

    // Render our scene starting from the sun.
    m_renderer->setRoot(Brick1);
    m_renderer->setBackgroundRoot(background);
    // Make the Earth a child of the Sun
    //background->AddChild(Brick1);
    background->AddChild(dollar);
    background->AddChild(skull);
    background->AddChild(character);
    background->AddChild(BrockFace);
    background->AddChild(BrockFace2);
    background->AddChild(BrockFace3);

    dollar->AddChild(Phantom);

    dollar->AddChild(zero);
    dollar->AddChild(hundred);

    Brick1->AddChild(Brick2);
    // Make the Moon a child of the Earth
    Brick2->AddChild(Brick3);

    Brick3->AddChild(Brick4);

    Brick4->AddChild(Money);

    Brick3->AddChild(Brick5);
    Brick5->AddChild(Brick6);
    Brick6->AddChild(Brick7);

    

    Brick7->AddChild(Brick8);
    Brick8->AddChild(Brick9);
    Brick9->AddChild(Brick10);
    
    //background_renderer->setRoot(background);
    
    // Set a default position for our camera
    m_renderer->GetCamera(0)->SetCameraEyePosition(3.0,4.0f,21.0f);
    float cameraX = m_renderer->GetCamera(0)->GetEyeXPosition();
    float cameraY = m_renderer->GetCamera(0)->GetEyeYPosition();
    float cameraZ = m_renderer->GetCamera(0)->GetEyeZPosition();
    float lastCameraX;
    float lastCameraY;
    float lastCameraZ;
    bool moneyGrabbed = false;

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
    float ground = 1.64;

    int upTraj = 0;

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
            
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && !doubleJump) {
                
                time += 24;
                upTraj += 12;
                if(jump){
                    doubleJump = true;
                }else{
                    jump = true;
                }
            }

        } 
    //std::cout << "Time: " << time << std::endl;
    if(!frozen){

    if(upTraj > 0){
        
        characterY += 0.15;
        
        time -= 1;
        upTraj -= 1;
    }   
    if(time > 0 && upTraj == 0){
        if((characterY - 0.15) <= ground){
            jump = false;
            doubleJump = false;
            time = 0;
        }else{
            characterY -= 0.15;
        
            time -= 1;
            if(time == 0){
                jump = false;
                doubleJump = false;
            }
        }
    }   
    }

        // Retrieve keyboard state
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(inputOn){
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
        if (state[SDL_SCANCODE_RIGHT]) {
            sceneX += 0.005;
            m_renderer->GetCamera(0)->MoveRight(0.16f);
        }
	    if (state[SDL_SCANCODE_LEFT]) {
            sceneX -= 0.005;
            m_renderer->GetCamera(0)->MoveLeft(0.16f);
        } 
    
        if (state[SDL_SCANCODE_UP]) {
            m_renderer->GetCamera(0)->MoveForward(0.1f);
        }	
        if (state[SDL_SCANCODE_DOWN]) {
            m_renderer->GetCamera(0)->MoveBackward(0.1f);
        }
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
        cameraX = m_renderer->GetCamera(0)->GetEyeXPosition();
        cameraY = m_renderer->GetCamera(0)->GetEyeYPosition();
        cameraZ = m_renderer->GetCamera(0)->GetEyeZPosition();

        bool hitWall = false;

        background->GetLocalTransform().LoadIdentity();
        background->GetLocalTransform().Scale(16.0,12.0,12.0);
        background->GetLocalTransform().Scale(2.0,2.0,2.0);	
        background->GetLocalTransform().Translate(sceneX, sceneY, sceneZ);
        
        Brick1->GetLocalTransform().LoadIdentity();
        Brick1->GetLocalTransform().Translate(-0.2,0.0,8.0);
        
        if(sceneX < -0.05){
            ground = -4;
        }
        if(sceneX > -0.05 && sceneX < 0.1){
            ground = 1.64;
        }

        if(sceneX > 0.1 && sceneX < 0.14){
            ground = -4;
        }
        
        Brick2->GetLocalTransform().LoadIdentity();		
        // ... transform the Earth
        Brick2->GetLocalTransform().Translate(2.0,0.0,0.0);

        if(sceneX >= 0.14 && sceneX < .29){
            if(sceneX > 0.2){
                if(characterY < 3.2){
                    hitWall = true;
                    sceneX = lastSceneX;
                    m_renderer->GetCamera(0)->SetCameraEyePosition(lastCameraX,lastCameraY,lastCameraZ);
                }else{
                    ground = 3.4;
                    
                    if(sceneX > .21 && sceneX < .28 && characterY < 4.3){
                        if(!moneyGrabbed){
                            Brick4->PopChild();
                        }
                        moneyGrabbed = true;
                    }
                }
            }else{
                ground = 1.7;
                if(characterY < ground){
                    hitWall = true;
                    sceneX = lastSceneX;
                    m_renderer->GetCamera(0)->SetCameraEyePosition(lastCameraX,lastCameraY,lastCameraZ);
                    characterY -= 0.05;
                }
            }
        }
        // ... transform the Sun

        Brick3->GetLocalTransform().LoadIdentity();	
        
        // ... transform the Moon
        Brick3->GetLocalTransform().Translate(4.0,0.0,0.0);

        Brick4->GetLocalTransform().LoadIdentity();	
        // ... transform the Moon
        Brick4->GetLocalTransform().Translate(2.0,2.0,0.0);
        if(!moneyGrabbed){
            Money->GetLocalTransform().LoadIdentity();
            Money->GetLocalTransform().Scale(0.45, 0.45, 0.45);
            Money->GetLocalTransform().Translate(0.0, 4.0, 0.0);
            Money->GetLocalTransform().Rotate(rotate, 0.0, 1.0, 0.0);
            zero->GetLocalTransform().LoadIdentity();
            zero->GetLocalTransform().Translate(2.0,0.0,0.0);
        }else{
            std::cout << "money grabbed" << std::endl;
            zero->GetLocalTransform().Scale(0.0,0.0,0.0);
            hundred->GetLocalTransform().LoadIdentity();
            hundred->GetLocalTransform().Translate(2.0,0.0,0.0);
        }

        if(sceneX > .29 && sceneX < .38){
            ground = -4;
        }
        if(sceneX > .38 && sceneX < .605){
            ground = 1.64;
            if(characterY < ground){
                hitWall = true;
                sceneX = lastSceneX;
                m_renderer->GetCamera(0)->SetCameraEyePosition(lastCameraX,lastCameraY,lastCameraZ);
                characterY -= 0.05;
            }
        }
        Brick5->GetLocalTransform().LoadIdentity();	
        Brick5->GetLocalTransform().Translate(8.0,0.0,0.0);
        if(!frozen){

        if(patrolDir){
            patrolNum += 0.002;
            enemyX += patrolNum;
            if(enemyX > 14.2){
                patrolNum = 0;
                patrolDir = false;
            }
        }else{
            patrolNum -= 0.002;
            enemyX += patrolNum;
            if(enemyX < 10.3){
                patrolNum = 0;
                patrolDir = true;
            }
        }
        }
        Phantom->GetLocalTransform().LoadIdentity();	
        Phantom->GetLocalTransform().Scale(3,3,3);
        Phantom->GetLocalTransform().Translate(enemyX-(sceneX*25.5), enemyY, enemyZ);

        

        Brick6->GetLocalTransform().LoadIdentity();	
        Brick6->GetLocalTransform().Translate(2.0,0.0,0.0);

        Brick7->GetLocalTransform().LoadIdentity();	
        Brick7->GetLocalTransform().Translate(2.0,0.0,0.0);

        Brick8->GetLocalTransform().LoadIdentity();	
        Brick8->GetLocalTransform().Translate(4.0,3.0,0.0);

        Brick9->GetLocalTransform().LoadIdentity();	
        Brick9->GetLocalTransform().Translate(4.0,3.0,0.0);

        Brick10->GetLocalTransform().LoadIdentity();	
        Brick10->GetLocalTransform().Translate(4.0,0.0,0.0);

        if(sceneX > .604 && sceneX < .635){
            ground = -4;
        }
        if(sceneX > .635 && sceneX < .725){
            ground = 4.2;
            if(characterY < ground){
                hitWall = true;
                sceneX = lastSceneX;
                m_renderer->GetCamera(0)->SetCameraEyePosition(lastCameraX,lastCameraY,lastCameraZ);
                characterY -= 0.05;
            }
        }
        if(sceneX > .725 && sceneX < .76){
            ground = -4;
        }
        if(sceneX > .76 && sceneX < .854){
            ground = 6.7;
            if(characterY < ground){
                hitWall = true;
                sceneX = lastSceneX;
                m_renderer->GetCamera(0)->SetCameraEyePosition(lastCameraX,lastCameraY,lastCameraZ);
                characterY -= 0.05;
            }
        }

        if(sceneX > .854 && sceneX < .888){
            ground = -4;
        }
        if(sceneX > .888 && sceneX < .97){
            ground = 6.7;
            if(characterY < ground){
                hitWall = true;
                sceneX = lastSceneX;
                m_renderer->GetCamera(0)->SetCameraEyePosition(lastCameraX,lastCameraY,lastCameraZ);
                characterY -= 0.05;
            }
        }
        if(sceneX > .97){
            ground = -4;
        }

        character->GetLocalTransform().LoadIdentity();
        character->GetLocalTransform().Scale(0.02, 0.05, 0.05);
        //std::cout << Brick1->GetLocalTransform().GetInternalMatrix()[0][0] << std::endl;
        
        character->GetLocalTransform().Translate(characterX,characterY,characterZ);

        BrockFace->GetLocalTransform().LoadIdentity();
        BrockFace->GetLocalTransform().Scale(0.02,0.025,0.025);
        BrockFace->GetLocalTransform().Translate(8.0,10.0,24.0);

        BrockFace2->GetLocalTransform().LoadIdentity();
        BrockFace2->GetLocalTransform().Scale(0.02,0.025,0.025);
        BrockFace2->GetLocalTransform().Translate(9.7,10.0,24.0);

        BrockFace3->GetLocalTransform().LoadIdentity();
        BrockFace3->GetLocalTransform().Scale(0.02,0.025,0.025);
        BrockFace3->GetLocalTransform().Translate(11.4,10.0,24.0);

        dollar->GetLocalTransform().LoadIdentity();
        dollar->GetLocalTransform().Scale(0.02,0.025,0.025);
        dollar->GetLocalTransform().Translate(-1.4,10.0,24.0);

        if(!frozen){
        if((characterY-0.15) >= ground && !jump){
            characterY -= 0.15;
        }
        }
        

        std::cout << "sceneX: " << sceneX << std::endl;
        std::cout << "char Y: " << characterY << std::endl;
        std::cout << "cameraX: " << cameraX << std::endl;
        std::cout << "cameraY: " << cameraY << std::endl;
        std::cout << "cameraZ: " << cameraZ << std::endl;
        std::cout << "enemyX: " << enemyX << std::endl;
        std::cout << std::endl;

        if((characterY-0.15) <= -4 ){
            background->PopChild();
            sceneX = 0;
            characterX = 0.0;
            characterY = 1.8;
            characterZ = 6.75;
            cameraX = 3;
            cameraY = 4;
            cameraZ = 21;
            m_renderer->GetCamera(0)->SetCameraEyePosition(cameraX,cameraY,cameraZ);
            lives -=1;
        }
        
        if((sceneX*24.7422680412 - enemyX) < 1.3 && (sceneX*24.7422680412 - enemyX) > -1 && characterY < 3.15){
            //std::cout << "Hit!" << std::endl;
            if(timer){
                frozen = true;
                inputOn = false;
                timer -= 1;
            }else{
                frozen = false;
                inputOn = true;
                background->PopChild();
                sceneX = 0;
                characterX = 0.0;
                characterY = 1.8;
                characterZ = 6.75;
                cameraX = 3;
                cameraY = 4;
                cameraZ = 21;
                m_renderer->GetCamera(0)->SetCameraEyePosition(cameraX,cameraY,cameraZ);
                lives -=1;
                timer = 20;
            }

        }

        int num = 0;
        if(lives == 0){
            inputOn = false;
            if(num == 0){
                //background->PopChild();
                num += 1;
            }
            skull->GetLocalTransform().LoadIdentity();
            skull->GetLocalTransform().Scale(0.2,0.2,0.2);
            skull->GetLocalTransform().Translate(0.45,0.85,2.4);
        }
        //background_renderer->Update();
        //background_renderer->Render();
        // Update our scene through our renderer
        m_renderer->Update();
        // Render our scene using our selected renderer
        m_renderer->Render();
        if(!hitWall){
            lastCameraX = cameraX;
            lastCameraY = cameraY;
            lastCameraZ = cameraZ;
        }

        lastSceneX = sceneX;
        lastCharacterY = characterY;


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
