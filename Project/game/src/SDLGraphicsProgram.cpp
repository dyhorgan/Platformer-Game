#include "SDLGraphicsProgram.hpp"
#include "Camera.hpp"
#include "Terrain.hpp"
#include "Sphere.hpp"
#include "Canvas.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

SDLGraphicsProgram::SDLGraphicsProgram(int w, int h){
	
	bool success = true;
	
	std::stringstream errorStream;
	
	m_window = NULL;

	if(SDL_Init(SDL_INIT_VIDEO)< 0){
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else{
		
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		
		m_window = SDL_CreateWindow( "Lab",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                w,
                                h,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

		
		if( m_window == NULL ){
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		
		m_openGLContext = SDL_GL_CreateContext( m_window );
		if( m_openGLContext == NULL){
			errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		
		if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
			errorStream << "Failed to iniitalize GLAD\n";
			success = false;
		}

		
		if(!InitGL()){
			errorStream << "Unable to initialize OpenGL!\n";
			success = false;
		}
  	}

    
    if(!success){
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors=errorStream.str();
        SDL_Log("%s\n",errors.c_str());
    }else{
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

	GetOpenGLVersionInfo();

    m_renderer = new Renderer(w,h);   
}


SDLGraphicsProgram::~SDLGraphicsProgram(){
    if(m_renderer!=nullptr){
        delete m_renderer;
    } 

	SDL_DestroyWindow( m_window );
	
	m_window = nullptr;
	
	SDL_Quit();
}

bool SDLGraphicsProgram::InitGL(){

	bool success = true;

	return success;
}

Object* panel3;
SceneNode* Brick3;

Object* panel2;
SceneNode* Brick2;

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

Object* goal;
SceneNode* flags; 

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

Object* winCanvas;
SceneNode* youWin;

Object* symbol;
SceneNode* dollar;

Object* sphere;
SceneNode* Money;

Object* number1;
SceneNode* zero;

Object* number2;
SceneNode* hundred;

void SDLGraphicsProgram::Loop(){

    static float rotate = 0.05f;
    float moonRotate = 0.05;
    float characterX = 0.0;
    float characterY = 1.8;
    float characterZ = 6.75;

    float enemyX = 12.0;
    float enemyY = -2.8;
    float enemyZ = -7.5;

    float flagX = 25;
    float flagY = 0.7;
    float flagZ = -7.5;

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
    bool won = false;
    float movingGround = 6.7;
    float movingBrick = 3.0;
    float platformMod = 0;
    bool platformDown = true;
    bool gravity = true;

    sphere = new Sphere();
    sphere->LoadTexture("dollarsigns.ppm");
    
    Money = new SceneNode(sphere);

    panel4 = new Canvas();
    panel4->LoadTexture("brick.ppm");
   
    Brick4 = new SceneNode(panel4);

    panel5 = new Canvas();
    panel5->LoadTexture("brick.ppm");
    
    Brick5 = new SceneNode(panel5);

    enemy = new Canvas();
    enemy->LoadTexture("monster.ppm");
    
    Phantom = new SceneNode(enemy);

    panel6 = new Canvas();
    panel6->LoadTexture("brick.ppm");
    
    Brick6 = new SceneNode(panel6);

    panel7 = new Canvas();
    panel7->LoadTexture("brick.ppm");
    
    Brick7 = new SceneNode(panel7);

    panel8 = new Canvas();
    panel8->LoadTexture("brick.ppm");

    Brick8 = new SceneNode(panel8);

    panel9 = new Canvas();
    panel9->LoadTexture("brick.ppm");
    
    Brick9 = new SceneNode(panel9);

    panel10 = new Canvas();
    panel10->LoadTexture("brick.ppm");
    
    Brick10 = new SceneNode(panel10);

    panel3 = new Canvas();
    panel3->LoadTexture("brick.ppm");
   
    Brick3 = new SceneNode(panel3);

    panel2 = new Canvas();
    panel2->LoadTexture("brick.ppm");
    Brick2 = new SceneNode(panel2);

    panel = new Canvas();
    panel->LoadTexture("brick.ppm");
    Brick1 = new SceneNode(panel);
    
    canvas = new Canvas();
    canvas->LoadTexture("clouds.ppm");
    background = new SceneNode(canvas);

    deathCanvas = new Canvas();
    deathCanvas->LoadTexture("skull.ppm");
    skull = new SceneNode(deathCanvas);

    winCanvas = new Canvas();
    winCanvas->LoadTexture("You-Win.ppm");
    youWin = new SceneNode(winCanvas);

    symbol = new Canvas();
    symbol->LoadTexture("moneybag.ppm");
    dollar = new SceneNode(symbol);

    goal = new Canvas();
    goal->LoadTexture("flags.ppm");
    flags = new SceneNode(goal);

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

    
    m_renderer->setRoot(Brick1);
    m_renderer->setBackgroundRoot(background);

    background->AddChild(dollar);
    background->AddChild(youWin);
    background->AddChild(skull);
    background->AddChild(character);
    background->AddChild(BrockFace);
    background->AddChild(BrockFace2);
    background->AddChild(BrockFace3);

    dollar->AddChild(Phantom);
    dollar->AddChild(flags);

    dollar->AddChild(zero);
    dollar->AddChild(hundred);

    Brick1->AddChild(Brick2);
    
    Brick2->AddChild(Brick3);

    Brick3->AddChild(Brick4);

    Brick4->AddChild(Money);

    Brick3->AddChild(Brick5);
    Brick5->AddChild(Brick6);
    Brick6->AddChild(Brick7);

    Brick7->AddChild(Brick8);
    Brick8->AddChild(Brick9);
    Brick8->AddChild(Brick10);
    
    m_renderer->GetCamera(0)->SetCameraEyePosition(3.0,4.0f,21.0f);
    float cameraX = m_renderer->GetCamera(0)->GetEyeXPosition();
    float cameraY = m_renderer->GetCamera(0)->GetEyeYPosition();
    float cameraZ = m_renderer->GetCamera(0)->GetEyeZPosition();
    float lastCameraX;
    float lastCameraY;
    float lastCameraZ;
    bool moneyGrabbed = false;

    bool quit = false;

    SDL_Event e;
   
    SDL_StartTextInput();

    float cameraSpeed = 5.0f;
    float ground = 1.64;

    int upTraj = 0;

    while(!quit){
        
        while(SDL_PollEvent( &e ) != 0){
            
            if(e.type == SDL_QUIT){
                quit = true;
            }
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
			    std::cout << "ESC: Goodbye! (Leaving MainApplicationLoop())" << std::endl;
                quit = true;
            }
            
            if(e.type==SDL_MOUSEMOTION){
                
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

        
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(inputOn){

        if (state[SDL_SCANCODE_W]) {
            
            m_renderer->GetCamera(0)->MoveUp(0.1f);
        }
        if (state[SDL_SCANCODE_S]) {
            
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
            if(characterY < ground){
                hitWall = true;
                sceneX = lastSceneX;
                m_renderer->GetCamera(0)->SetCameraEyePosition(lastCameraX,lastCameraY,lastCameraZ);
                characterY -= 0.05;
            }
        }

        if(sceneX > 0.1 && sceneX < 0.14){
            ground = -4;
        }
        
        Brick2->GetLocalTransform().LoadIdentity();		
        
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

        Brick3->GetLocalTransform().LoadIdentity();	
        
        Brick3->GetLocalTransform().Translate(4.0,0.0,0.0);

        Brick4->GetLocalTransform().LoadIdentity();	
        
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

        flags->GetLocalTransform().LoadIdentity();	
        flags->GetLocalTransform().Scale(3,3,3);
        flags->GetLocalTransform().Translate(flagX-(sceneX*25.5), flagY, flagZ);

        Brick6->GetLocalTransform().LoadIdentity();	
        Brick6->GetLocalTransform().Translate(2.0,0.0,0.0);

        Brick7->GetLocalTransform().LoadIdentity();	
        Brick7->GetLocalTransform().Translate(2.0,0.0,0.0);

        Brick8->GetLocalTransform().LoadIdentity();	
        Brick8->GetLocalTransform().Translate(4.0,3.0,0.0);

        Brick9->GetLocalTransform().LoadIdentity();	
        Brick9->GetLocalTransform().Translate(4.0,movingBrick,0.0);

        Brick10->GetLocalTransform().LoadIdentity();	
        Brick10->GetLocalTransform().Translate(10.0,1.5,0.0);

        if(sceneX > .604 && sceneX < .635){
            ground = -4;
        }
        if(sceneX > .635 && sceneX < .725){
            ground = 4.2;
            if(characterY < ground && characterY > 0.75){
                hitWall = true;
                sceneX = lastSceneX;
                m_renderer->GetCamera(0)->SetCameraEyePosition(lastCameraX,lastCameraY,lastCameraZ);
                characterY -= 0.05;
            }
            if(lastCharacterY < 0.75 && characterY >= 0.75){
                characterY = lastCharacterY;
                characterY -= 0.2;
            }
        }
        if(sceneX > .725 && sceneX < .76){
            ground = -4;
        }
        if(sceneX > .76 && sceneX < .855){
            ground = movingGround+.9;
            if(characterY < (ground-.15) && characterY > ground-.25){
                hitWall = true;
                sceneX = lastSceneX;
                m_renderer->GetCamera(0)->SetCameraEyePosition(lastCameraX,lastCameraY,lastCameraZ);
                characterY -= 0.05;
            }
            if(characterY > (ground-.15) && (characterY - ground) < .29){
                
                characterY = ground + .29;
                
            }
        }

        if(sceneX > .855 && sceneX < .95){
            ground = -4;
        }
        if(sceneX > .95 && sceneX < 1.07){
            ground = 5.4;
            if(characterY < ground){
                hitWall = true;
                sceneX = lastSceneX;
                m_renderer->GetCamera(0)->SetCameraEyePosition(lastCameraX,lastCameraY,lastCameraZ);
                characterY -= 0.05;
            }else if(characterY < 6.25){
                won = true;
                frozen = true;
            }
        }
        if(sceneX > 1.07){
            ground = -4;
        }

        character->GetLocalTransform().LoadIdentity();
        character->GetLocalTransform().Scale(0.02, 0.05, 0.05);
        
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
        
        if(!frozen && gravity){
            if( ( ((characterY-0.15) >= ground) && !jump ) || (((characterY+3) < ground) && !jump) ){
                characterY -= 0.15;
            }
        }
        
        if(!gravity){
            gravity = true;
        }

        if(!frozen){
            if(platformDown){
                platformMod -= .01;
            }else{
                platformMod += .01;
            }
            movingGround += platformMod;
            movingBrick += platformMod;
            if(movingGround < 2.7){
                platformDown = false;
            }
            if(movingGround > 2.9){
                platformDown = true;
            }
        }
        
        std::cout << "sceneX: " << sceneX << std::endl;
        std::cout << "char Y: " << characterY << std::endl;
        std::cout << "last char Y: " << lastCharacterY << std::endl;
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
               
                num += 1;
            }
            skull->GetLocalTransform().LoadIdentity();
            skull->GetLocalTransform().Scale(0.2,0.2,0.2);
            skull->GetLocalTransform().Translate(0.45,0.85,2.4);
        }
        if(won){
            frozen = true;
            inputOn = false;
            youWin->GetLocalTransform().LoadIdentity();
            youWin->GetLocalTransform().Scale(0.15,0.15,0.15);
            youWin->GetLocalTransform().Translate(0.45,0.85,3.4);
        }

        m_renderer->Update();
        
        m_renderer->Render();
        if(!hitWall){
            lastCameraX = cameraX;
            lastCameraY = cameraY;
            lastCameraZ = cameraZ;
        }

        lastSceneX = sceneX;
        lastCharacterY = characterY;

        SDL_Delay(25);  
                        
      	SDL_GL_SwapWindow(GetSDLWindow());
        rotate += 0.03;
        moonRotate += 0.15;
	}
   
    SDL_StopTextInput();
}


SDL_Window* SDLGraphicsProgram::GetSDLWindow(){
  return m_window;
}


void SDLGraphicsProgram::GetOpenGLVersionInfo(){
	SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
	SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
	SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
	SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
	SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}
