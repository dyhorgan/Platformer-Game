#include "VertexBufferLayout.hpp"
#include <iostream>


VertexBufferLayout::VertexBufferLayout(){
}

VertexBufferLayout::~VertexBufferLayout(){

    glDeleteBuffers(1,&m_vertexPositionBuffer);
    glDeleteBuffers(1,&m_indexBufferObject);
}


void VertexBufferLayout::Bind(){
  
    glBindVertexArray(m_VAOId);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
}

void VertexBufferLayout::Unbind(){
        
        glBindVertexArray(0);
       
        glBindBuffer(GL_ARRAY_BUFFER, 0);
       
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void VertexBufferLayout::CreatePositionBufferLayout(unsigned int vcount,unsigned int icount, float* vdata, unsigned int* idata ){
       
        m_stride = 3;
        
        static_assert(sizeof(GLfloat)==sizeof(float),
            "GLFloat and gloat are not the same size on this architecture");
       
        glGenVertexArrays(1, &m_VAOId);

        glBindVertexArray(m_VAOId);

        glGenBuffers(1, &m_vertexPositionBuffer); 

        glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
        glBufferData(GL_ARRAY_BUFFER, vcount*sizeof(float), vdata, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(  0,   
                                3,   
                                GL_FLOAT, 
                                GL_FALSE, 
                                sizeof(float)*m_stride, 
                                0             
        );

        static_assert(sizeof(unsigned int)==sizeof(GLuint),"Gluint not same size!");

        glGenBuffers(1, &m_indexBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount*sizeof(unsigned int), idata,GL_STATIC_DRAW);
    }


void VertexBufferLayout::CreateTextureBufferLayout(unsigned int vcount,unsigned int icount, float* vdata, unsigned int* idata ){
       
        m_stride = 5;
        
        static_assert(sizeof(GLfloat)==sizeof(float),
            "GLFloat and gloat are not the same size on this architecture");
       
        glGenVertexArrays(1, &m_VAOId);

        glBindVertexArray(m_VAOId);

        glGenBuffers(1, &m_vertexPositionBuffer); 
    
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
        glBufferData(GL_ARRAY_BUFFER, vcount*sizeof(float), vdata, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
       
        glVertexAttribPointer(  0,   
                                3,  
                                GL_FLOAT, 
                                GL_FALSE,
                                sizeof(float)*m_stride,              
                                0                          
        );

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,2,GL_FLOAT, GL_TRUE,sizeof(float)*m_stride,(char*)(sizeof(float)*3));

        static_assert(sizeof(unsigned int)==sizeof(GLuint),"Gluint not same size!");

        glGenBuffers(1, &m_indexBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount*sizeof(unsigned int), idata,GL_STATIC_DRAW);
    }

void VertexBufferLayout::CreateNormalBufferLayout(unsigned int vcount,unsigned int icount, float* vdata, unsigned int* idata ){
		m_stride = 14;
        
        
        static_assert(sizeof(GLfloat)==sizeof(float), "GLFloat and gloat are not the same size on this architecture");
       
        glGenVertexArrays(1, &m_VAOId);

        glBindVertexArray(m_VAOId);

        glGenBuffers(1, &m_vertexPositionBuffer); 

        glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
        glBufferData(GL_ARRAY_BUFFER, vcount*sizeof(float), vdata, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(  0,   
                                3,   
                                GL_FLOAT, 
                                GL_FALSE, 
                                sizeof(float)*m_stride,        
                                0                          
        );

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE,sizeof(float)*m_stride,(char*)(sizeof(float)*3));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE,sizeof(float)*m_stride,(char*)(sizeof(float)*6));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3,3,GL_FLOAT, GL_FALSE,sizeof(float)*m_stride,(char*)(sizeof(float)*8));

        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4,3,GL_FLOAT, GL_FALSE,sizeof(float)*m_stride,(char*)(sizeof(float)*11));
        
        static_assert(sizeof(unsigned int)==sizeof(GLuint),"Gluint not same size!");

        glGenBuffers(1, &m_indexBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount*sizeof(unsigned int), idata,GL_STATIC_DRAW);
    }
