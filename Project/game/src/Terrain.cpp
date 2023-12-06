#include "Terrain.hpp"
#include "Image.hpp"

#include <iostream>

Terrain::Terrain(unsigned int xSegs, unsigned int zSegs, std::string fileName) : 
                m_xSegments(xSegs), m_zSegments(zSegs) {
    std::cout << "(Terrain.cpp) Constructor called \n";

    Image heightMap(fileName);
    heightMap.LoadPPM(true);

    float scale = 5.0f; 

    m_heightData = new int[m_xSegments*m_zSegments];

    Init();
}

Terrain::~Terrain(){
 
    if(m_heightData!=nullptr){
        delete m_heightData;
    }
}

void Terrain::Init(){

   m_geometry.Gen();  
   
   m_vertexBufferLayout.CreateNormalBufferLayout(m_geometry.GetBufferDataSize(),
                                        m_geometry.GetIndicesSize(),
                                        m_geometry.GetBufferDataPtr(),
                                        m_geometry.GetIndicesDataPtr());
}


void Terrain::LoadHeightMap(Image image){

}
