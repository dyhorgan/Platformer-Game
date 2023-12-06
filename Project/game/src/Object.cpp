#include "Object.hpp"
#include "Camera.hpp"
#include "Error.hpp"


Object::Object(){
}

Object::~Object(){
    
}

void Object::LoadTexture(std::string fileName){
        
        m_textureDiffuse.LoadTexture(fileName);
}


void Object::MakeTexturedQuad(std::string fileName){


        m_geometry.AddVertex(-1.0f,-1.0f, 0.0f, 0.0f, 0.0f);
        m_geometry.AddVertex( 1.0f,-1.0f, 0.0f, 1.0f, 0.0f);
    	m_geometry.AddVertex( 1.0f, 1.0f, 0.0f, 1.0f, 1.0f);
        m_geometry.AddVertex(-1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
            	
        m_geometry.MakeTriangle(0,1,2);
        m_geometry.MakeTriangle(2,3,0);

        m_geometry.Gen();

        m_vertexBufferLayout.CreateNormalBufferLayout(m_geometry.GetBufferDataSize(),
                                        m_geometry.GetIndicesSize(),
                                        m_geometry.GetBufferDataPtr(),
                                        m_geometry.GetIndicesDataPtr());


        m_textureDiffuse.LoadTexture(fileName.c_str());
}


void Object::Bind(){
        
        m_vertexBufferLayout.Bind();
        
        m_textureDiffuse.Bind(0);
}


void Object::Render(){

    Bind();

    glDrawElements(GL_TRIANGLES,
                   m_geometry.GetIndicesSize(), 
                   GL_UNSIGNED_INT,             
                        nullptr);                                                          
}

