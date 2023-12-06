#include "Renderer.hpp"


Renderer::Renderer(unsigned int w, unsigned int h){
    m_screenWidth = w;
    m_screenHeight = h;

    Camera* defaultCamera = new Camera();
   
    m_cameras.push_back(defaultCamera);

    m_root = nullptr;
}

Renderer::~Renderer(){
    
    for(int i=0; i < m_cameras.size(); i++){
        delete m_cameras[i];
    }
}

void Renderer::Update(){

    m_projectionMatrix = glm::perspective(glm::radians(45.0f),((float)m_screenWidth)/((float)m_screenHeight),0.1f,512.0f);

    
    if(m_root!=nullptr){

        m_root->Update(m_projectionMatrix, m_cameras[0]);
        background_root->Update(m_projectionMatrix, m_cameras[0]);
    }
}

void Renderer::Render(){

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D); 
    
    glViewport(0, 0, m_screenWidth, m_screenHeight);
    glClearColor( 0.01f, 0.01f, 0.01f, 1.f );

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    if(m_root!=nullptr){
        m_root->Draw();
    }
    if(background_root!=nullptr){
        background_root->Draw();
    }
}

void Renderer::setRoot(SceneNode* startingNode){
    m_root = startingNode;
}

void Renderer::setBackgroundRoot(SceneNode* startingNode){
    background_root = startingNode;
}


