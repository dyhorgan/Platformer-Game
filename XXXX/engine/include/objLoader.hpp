#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>

#include <glad/glad.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "globals.hpp"

// The STL format is a simple 'triangle soup' format that outputs
// one normal per triangle, and then the following three triangles
// The .stl bunny was obtained from: https://en.m.wikipedia.org/wiki/File:Stanford_Bunny.stl
// And then modified in blender3D.

struct Vertex{
    float x,y,z;    // position
	float uvX, uvY;
	float nx,ny,nz; // normals
    bool operator==(const Vertex& rhs){
        if(this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && this->nx == rhs.nx && this->ny == rhs.ny && this->nz == rhs.nz && this->uvX == rhs.uvX && this->uvY == rhs.uvY ){
            return true;
        }else{
            return false;
        }
    }
};  

struct Triangle{
    Vertex vertices[3];
    float nx,ny,nz;

    Triangle(Vertex v1, Vertex v2, Vertex v3){
        vertices[0] = v1;
        vertices[1] = v2;
        vertices[2] = v3;

        nx = 0.0f;
        ny = 1.0f;
        nz = 0.0f;
        //computeSurfaceNormal();
    }
    //void computeSurfaceNormal(){

    //}
};

struct objLoader{
	private:
		std::string path;
		std::vector< glm::vec3 > glmVertices;
		std::vector< glm::vec3 > glmNormals;
		std::vector< glm::vec2 > glmColors;
        std::vector<float> mVertices;
		std::vector<float> mNormals;
		std::vector<float> mColors;
        std::vector<Vertex> gridPoints;
        std::vector<Triangle> mesh;
        std::string mtlFile;
        std::string kdppmFile;
        std::string ksppmFile;
        std::string bumpppmFile;
        std::vector<GLfloat> vertexData;
        
	public:
		objLoader(std::string path);
        std::vector<Vertex> cleanVertexData;
        std::vector<GLfloat> cleanVertexFloats;
		std::vector<float> getVertices();
		std::vector<float> getNormals();
        std::vector<float> getColors();
        std::vector<glm::vec3> getGLMVertices();
        std::vector<glm::vec3> getGLMNormals();
        std::vector<glm::vec2> getGLMColors();
        std::vector<Vertex> getGridPoints();
        std::vector<Triangle> getMesh();
        std::string getMTLFile();
        std::string getKDPPMFile();
        std::string getKSPPMFile();
        std::string getBumpPPMFile();
        GLuint getVBO();
        GLuint getVAO();
        GLuint getIBO();
        GLuint getShaderID();
        GLuint mShaderID = 0;
        GLuint 	gVertexBufferObject					= 0;

        GLuint mVAO= 0;
		GLuint mVBO[3];
        GLuint mIBO= 0;
        void Initialize();
        void PreDraw();
		void Draw();
        void printVertexData();
};


#endif
