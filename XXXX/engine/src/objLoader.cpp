#include "objLoader.hpp"
#include "globals.hpp"
#include "utils.hpp"
#include "texture.hpp"


float uOffset=-2.0f;
float uRotate=0.1f;

void objLoader::printVertexData(){
    std::cout << "{ ";
    for(int i = 0; i < vertexData.size(); i++){
        std::cout << vertexData[i];
        if((i+1) % 8 == 0){
            std::cout << "," << std::endl;
        }else{
            std::cout << ",";
        }
    }
    std::cout << "}" << std::endl;
}

objLoader::objLoader(std::string pathString){

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

const char* path = pathString.c_str();

FILE * file = fopen(path, "r");
if( file == NULL ){
    printf("Impossible to open the file !\n");
}

while( 1 ){

    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF){
        break; 
    }else{
    if(strcmp( lineHeader, "mtllib" ) == 0){
        char str[100];
        fgets(str,100,file);
        mtlFile = str;
        remove(mtlFile.begin(), mtlFile.end(), ' ');
        remove(mtlFile.begin(), mtlFile.end()+1, '\n');
     
    }else if ( strcmp( lineHeader, "v" ) == 0 ){
        glm::vec3 vertex;
        fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
        glmVertices.push_back(vertex);
        
    }else if ( strcmp( lineHeader, "vt" ) == 0 ){
        glm::vec2 uv;
        fscanf(file, "%f %f\n", &uv.x, &uv.y );
        glmColors.push_back(uv);
        
    }else if ( strcmp( lineHeader, "vn" ) == 0 ){
        glm::vec3 normal;
        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
        glmNormals.push_back(normal);
        
    }else if ( strcmp( lineHeader, "f" ) == 0 ){
        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
        char str[100];
        fgets(str,100,file);

        int matches = sscanf(str,"%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
    if (matches != 9){

        int matches = sscanf(str,"%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
    }
 
    vertexIndices.push_back(vertexIndex[0]);
    vertexIndices.push_back(vertexIndex[1]);
    vertexIndices.push_back(vertexIndex[2]);
    uvIndices    .push_back(uvIndex[0]);
    uvIndices    .push_back(uvIndex[1]);
    uvIndices    .push_back(uvIndex[2]);
    normalIndices.push_back(normalIndex[0]);
    normalIndices.push_back(normalIndex[1]);
    normalIndices.push_back(normalIndex[2]);

    }
    }
}

for( unsigned int i=0; i < vertexIndices.size(); i++ ){
    Vertex newVert;
    unsigned int vertexIndex = vertexIndices[i];
    glm::vec3 vertex = glmVertices[ vertexIndex-1 ];
    
    vertexData.push_back(vertex.x);
    vertexData.push_back(vertex.y);
    vertexData.push_back(vertex.z);
    newVert.x = vertex.x;
    newVert.y = vertex.y;
    newVert.z = vertex.z;
    
    unsigned int normalIndex = normalIndices[i];
    glm::vec3 normal = glmNormals[ normalIndex-1 ];

    vertexData.push_back(normal.x);
    vertexData.push_back(normal.y);
    vertexData.push_back(normal.z);
    newVert.nx = normal.x;
    newVert.ny = normal.y;
    newVert.nz = normal.z;
    
    unsigned int uvIndex = uvIndices[i];
    glm::vec2 uv = glmColors[ uvIndex-1 ];

    vertexData.push_back(uv.x);
    vertexData.push_back(uv.y);
    newVert.uvX = uv.x;
    newVert.uvY = uv.y;

    gridPoints.push_back(newVert);
}

    fclose(file);
    int index = pathString.find_last_of("/");
    std::string newMTL = mtlFile;
    if(index != std::string::npos){
        newMTL = pathString.substr(0,index+1) + mtlFile;
    }
    std::cout << "newMTL: " << newMTL << std::endl;
    FILE * texfile = fopen(newMTL.c_str(), "r");
    

    if( texfile == NULL ){
        printf("Impossible to open the mtl file !\n");
    }

    while( 1 ){

        char lineHeader[128];

        int res = fscanf(texfile, "%s", lineHeader);

        if (res == EOF){
            break; 
        }else{
            if(strcmp( lineHeader, "map_Kd" ) == 0){
                
                char str[100];
                fgets(str,100,texfile);
                
                kdppmFile = str;
                remove(kdppmFile.begin(), kdppmFile.end(), ' ');
                remove(kdppmFile.begin(), kdppmFile.end()+1, '\n');
                int index = pathString.find_last_of("/");
                std::string newKD = kdppmFile;
                if(index != std::string::npos){
                    newKD = pathString.substr(0,index+1) + newKD;
                }
                std::cout << "newKD: " << newKD << std::endl;
                kdppmFile = newKD;
               
            }else if(strcmp( lineHeader, "map_Bump" ) == 0){
               
                char str[100];
                fgets(str,100,texfile);
                
                bumpppmFile = str;
                remove(bumpppmFile.begin(), bumpppmFile.end(), ' ');
                remove(bumpppmFile.begin(), bumpppmFile.end()+1, '\n');

            }else if(strcmp( lineHeader, "map_Ks" ) == 0){
                 
                char str[100];
                fgets(str,100,texfile);
             
                ksppmFile = str;
                remove(ksppmFile.begin(), ksppmFile.end(), ' ');
                remove(ksppmFile.begin(), ksppmFile.end()+1, '\n');
            }
        }
    }
    fclose(texfile);

}

std::vector<glm::vec3> objLoader::getGLMVertices(){
    return glmVertices;
};
std::vector<glm::vec3> objLoader::getGLMNormals(){
    return glmNormals;
};
std::vector<glm::vec2> objLoader::getGLMColors(){
    return glmColors;
};
std::vector<float> objLoader::getVertices(){
    return mVertices;
};
std::vector<float> objLoader::getNormals(){
    return mNormals;
};
std::vector<float> objLoader::getColors(){
    return mColors;
};
std::vector<Vertex> objLoader::getGridPoints(){
    return gridPoints;
};
std::vector<Triangle> objLoader::getMesh(){
    return mesh;
}
void objLoader::Initialize(){

    g.gTexture.LoadTexture(kdppmFile);
    /*
	g.gTexture.LoadTexture("cat3.ppm");

    
        vertexData = {
    // 0 - Vertex
		-0.5f, -0.5f, 0.0f, 	// Left vertex position
		1.0f,  0.0f, 0.0f, 	  // color
		 0.0f, 0.0f,       		// texture coordinate
    // 1 - Vertex
		0.5f, -0.5f, 0.0f,  	// right vertex position
		0.0f,  1.0f, 0.0f,  	// color
		1.0f , 0.0f,		      // texture coordinate
		// 2 - Vertex
		-0.5f,  0.5f, 0.0f,  	// Top left vertex position
		0.0f,  0.0f, 1.0f,  	// color
		0.0f, 1.0f, 					// texture coordinate
        // 3 - Vertex
		0.5f,  0.5f, 0.0f,  	// Top-right position
		0.0f,  0.0f, 1.0f,  	// color
		1.0f,1.0f, 					  // texture coordinate
	};
    */
    //printVertexData();

	glGenVertexArrays(1, &mVAO);

	glBindVertexArray(mVAO);

	glGenBuffers(1, &gVertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
    
	glBufferData(GL_ARRAY_BUFFER, 								// Kind of buffer we are working with 
																// (e.g. GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER)
				 vertexData.size() * sizeof(GL_FLOAT), 	        // Size of data in bytes
				 vertexData.data(), 						    // Raw array of data
				 GL_STATIC_DRAW);								// How we intend to use the data
 
    // Index buffer data for a quad
    //std::vector<GLuint> indexBufferData;
    //const std::vector<GLuint> indexBufferData {2,0,1, 3,2,1};
    /*
    int modifyer = 0;
    for(int i = 0; i < vertexData.size(); i+=24){
        indexBufferData.push_back(2 + modifyer);
        indexBufferData.push_back(0 + modifyer);
        indexBufferData.push_back(1 + modifyer);
        modifyer += 3;
    }
    */
    /*
    int modifyer = 0;
    for(int i = 0; i < cleanVertexFloats.size(); i+=32){
        indexBufferData.push_back(2 + modifyer);
        indexBufferData.push_back(0 + modifyer);
        indexBufferData.push_back(1 + modifyer);
        indexBufferData.push_back(3 + modifyer);
        indexBufferData.push_back(2 + modifyer);
        indexBufferData.push_back(1 + modifyer);
        modifyer += 4;
    }
    */

    // Setup the Index Buffer Object (IBO i.e. EBO)
    /*
    glGenBuffers(1,&mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
                 mIBO);
    // Populate our Index Buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indexBufferData.size()*sizeof(GLuint),
                 indexBufferData.data(),
                 GL_STATIC_DRAW);
    */

	
	glEnableVertexAttribArray(0);

    glVertexAttribPointer(0,  		// Attribute 0 corresponds to the enabled glEnableVertexAttribArray
							  		// In the future, you'll see in our vertex shader this also correspond
							  		// to (layout=0) which selects these attributes.
                          3,  		// The number of components (e.g. x,y,z = 3 components)
                          GL_FLOAT, // Type
                          GL_FALSE, // Is the data normalized
                          sizeof(GL_FLOAT)*8, 		// Stride
                         (void*)0	// Offset
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
                          3, 
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GL_FLOAT)*8,
                          (GLvoid*)(sizeof(GL_FLOAT)*3)
            );

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,
                          2, 
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GL_FLOAT)*8,
                          (GLvoid*)(sizeof(GL_FLOAT)*6)
            );


	glBindVertexArray(0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
void objLoader::PreDraw(){
    
    glPolygonMode(GL_FRONT_AND_BACK,g.gPolygonMode);

    //glDisable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

		// Enable texture mapping
	glEnable(GL_TEXTURE_2D);

    // Initialize clear color
    // This is the background of the screen.
    glViewport(0, 0, g.gScreenWidth, g.gScreenHeight);
    glClearColor( 1.f, 1.f, 0.f, 1.f );

    //Clear color buffer and Depth Buffer
  	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(mShaderID);
        // Model transformation by translating our object into world space
    glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,uOffset)); 

    // Update our model matrix by applying a rotation after our translation
    model           = glm::rotate(model,glm::radians(uRotate),glm::vec3(0.0f,1.0f,0.0f));
    

    // Retrieve our location of our Model Matrix
    GLint u_ModelMatrixLocation = glGetUniformLocation( mShaderID,"u_ModelMatrix");
    if(u_ModelMatrixLocation >=0){
        glUniformMatrix4fv(u_ModelMatrixLocation,1,GL_FALSE,&model[0][0]);
    }else{
        std::cout << "Could not find u_ModelMatrix, maybe a mispelling?\n";
        exit(EXIT_FAILURE);
    }

    // Update the View Matrix
    GLint u_ViewMatrixLocation = glGetUniformLocation(mShaderID,"u_ViewMatrix");
    if(u_ViewMatrixLocation>=0){
        glm::mat4 viewMatrix = g.gCamera.GetViewMatrix();
        glUniformMatrix4fv(u_ViewMatrixLocation,1,GL_FALSE,&viewMatrix[0][0]);
    }else{
        std::cout << "Could not find u_ModelMatrix, maybe a mispelling?\n";
        exit(EXIT_FAILURE);
    }


    // Projection matrix (in perspective) 
    glm::mat4 perspective = glm::perspective(glm::radians(45.0f),
                                             (float)g.gScreenWidth/(float)g.gScreenHeight,
                                             0.1f,
                                             1000.0f);

    // Retrieve our location of our perspective matrix uniform 
    GLint u_ProjectionLocation= glGetUniformLocation( mShaderID,"u_Projection");
    if(u_ProjectionLocation>=0){
        glUniformMatrix4fv(u_ProjectionLocation,1,GL_FALSE,&perspective[0][0]);
    }else{
        std::cout << "Could not find u_Perspective, maybe a mispelling?\n";
        exit(EXIT_FAILURE);
    }

       g.gTexture.Bind(0);
    	GLint u_textureLocation = glGetUniformLocation(mShaderID,"u_DiffuseTexture");
		//std::cout << u_textureLocation << std::endl;
		if(u_textureLocation>=0){
			// Setup the slot for the texture
			glUniform1i(u_textureLocation,0);
		}else{
			std::cout << "Could not find u_DiffuseTexture, maybe a misspelling?" << std::endl;
     	exit(EXIT_FAILURE);
		}
}

void objLoader::Draw(){
        //Render data
	glBindVertexArray(mVAO);
    //glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
    
    glDrawArrays(GL_TRIANGLES,0,vertexData.size());
    //std::cout << "vertexData Size: " << vertexData.size() << std::endl;
    /*
    glDrawElements(GL_TRIANGLES,
                    vertexData.size(),
                    GL_UNSIGNED_INT,
                    0);
                    */
    glUseProgram(0);
}

std::string objLoader::getMTLFile(){
    return mtlFile;
}
std::string objLoader::getKDPPMFile(){
    return kdppmFile;
}
std::string objLoader::getKSPPMFile(){
    return ksppmFile;
}
std::string objLoader::getBumpPPMFile(){
    return bumpppmFile;
}
GLuint objLoader::getVBO(){
    return gVertexBufferObject;
}
GLuint objLoader::getVAO(){
    return mVAO;
    
}
GLuint objLoader::getIBO(){
    return mIBO;
}
GLuint objLoader::getShaderID(){
    return mShaderID;
}

