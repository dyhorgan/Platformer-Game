#include "Shader.hpp"

#include <iostream>
#include <fstream>


Shader::Shader(){}


Shader::~Shader(){
	glDeleteProgram(m_shaderID);
}

void Shader::Bind() const{
	glUseProgram(m_shaderID);
}

void Shader::Unbind() const{
	glUseProgram(0);
}

void Shader::Log(const char* system, const char* message){
    std::cout << "[" << system << "]" << message << "\n";
}


std::string Shader::LoadShader(const std::string& fname){
		std::string result;
		
		std::string line;
		std::ifstream myFile(fname.c_str());

		if(myFile.is_open()){
			while(getline(myFile,line)){
					result += line + '\n';

			}
		}
		else{
			Log("LoadShader","file not found. Try an absolute file path to see if the file exists");
		}
		
		myFile.close();
		return result;
}


void Shader::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource){

    unsigned int program = glCreateProgram();
    
    unsigned int myVertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int myFragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    
    glAttachShader(program,myVertexShader);
    glAttachShader(program,myFragmentShader);
    
    glLinkProgram(program);
    glValidateProgram(program);

    glDetachShader(program,myVertexShader);
    glDetachShader(program,myFragmentShader);

    glDeleteShader(myVertexShader);
    glDeleteShader(myFragmentShader);

    if(!CheckLinkStatus(program)){
        Log("CreateShader","ERROR, shader did not link! Were there compile errors in the shader?");
    }

    m_shaderID = program;
}


unsigned int Shader::CompileShader(unsigned int type, const std::string& source){
  
  unsigned int id;

  if(type == GL_VERTEX_SHADER){
    id = glCreateShader(GL_VERTEX_SHADER);
  }else if(type == GL_FRAGMENT_SHADER){
    id = glCreateShader(GL_FRAGMENT_SHADER);
  }
  const char* src = source.c_str();
 
  glShaderSource(id, 1, &src, nullptr);

  glCompileShader(id);

  int result;
  
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if(result == GL_FALSE){
      int length;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
      char* errorMessages = new char[length]; 
      glGetShaderInfoLog(id, length, &length, errorMessages);
      if(type == GL_VERTEX_SHADER){
		Log("CompileShader ERROR", "GL_VERTEX_SHADER compilation failed!");
		Log("CompileShader ERROR", (const char*)errorMessages);
      }else if(type == GL_FRAGMENT_SHADER){
        Log("CompileShader ERROR","GL_FRAGMENT_SHADER compilation failed!");
		Log("CompileShader ERROR",(const char*)errorMessages);
      }
      
      delete[] errorMessages;
    
      glDeleteShader(id);
      return 0;
  }

  return id;
}

bool Shader::CheckLinkStatus(GLuint programID){                                                                             
                                                                                              
    int result;                                                                                                                         
    
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    if(result == GL_FALSE){
      int length;
      glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);
      char* errorMessages = new char[length];
      glGetProgramInfoLog(programID, length, &length, errorMessages);
      
      SDL_Log("ERROR in linking process\n");
          SDL_Log("%s\n",errorMessages);
      delete[] errorMessages;
      return false;
    }

    return true;
}


GLuint Shader::GetID() const{
    return m_shaderID;
}


void Shader::SetUniformMatrix4fv(const GLchar* name, const GLfloat* value){

    GLint location = glGetUniformLocation(m_shaderID,name);

    glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

void Shader::SetUniform3f(const GLchar* name, float v0, float v1, float v2){
    GLint location = glGetUniformLocation(m_shaderID,name);
    glUniform3f(location, v0, v1, v2);
}

void Shader::SetUniform1i(const GLchar* name, int value){
    GLint location = glGetUniformLocation(m_shaderID,name);
    glUniform1i(location, value);
}

void Shader::SetUniform1f(const GLchar* name, float value){
    GLint location = glGetUniformLocation(m_shaderID,name);
    glUniform1f(location, value);
}
