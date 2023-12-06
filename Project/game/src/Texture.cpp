#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else 
    #include <SDL.h>
#endif


#include "Texture.hpp"

#include <stdio.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <memory>

Texture::Texture(){

}

Texture::~Texture(){
	
	glDeleteTextures(1,&m_textureID);

    if(m_image != nullptr){
        delete m_image;
    }

}

void Texture::LoadTexture(const std::string filepath){
	
    m_filepath = filepath;

    m_image = new Image(filepath);
    m_image->LoadPPM(true);

    glEnable(GL_TEXTURE_2D); 
	glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
    glGenTextures(1,&m_textureID);
    
    glBindTexture(GL_TEXTURE_2D, m_textureID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
	
	glTexImage2D(GL_TEXTURE_2D,
							0 ,
						GL_RGB,
                        m_image->GetWidth(),
                        m_image->GetHeight(),
						0,
						GL_RGB,
						GL_UNSIGNED_BYTE,
						 m_image->GetPixelDataPtr()); 

    glGenerateMipmap(GL_TEXTURE_2D);                        
	   
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind(unsigned int slot) const{

    glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}


