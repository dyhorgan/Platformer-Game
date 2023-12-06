#include "SceneNode.hpp"

#include <string>
#include <iostream>

SceneNode::SceneNode(Object* ob){
	std::cout << "(SceneNode.cpp) Constructor called\n";
	m_object = ob;

	m_parent = nullptr;
	
	std::string vertexShader = m_shader.LoadShader("./shaders/vert.glsl");
	std::string fragmentShader = m_shader.LoadShader("./shaders/frag.glsl");
	
	m_shader.CreateShader(vertexShader,fragmentShader);       
}
 
SceneNode::~SceneNode(){
	
	for(unsigned int i =0; i < m_children.size(); ++i){
		delete m_children[i];
	}
}

void SceneNode::AddChild(SceneNode* n){

	n->m_parent = this;
	
	m_children.push_back(n);
}

void SceneNode::PopChild(){
	m_children.pop_back();
}


void SceneNode::Draw(){
	
	m_shader.Bind();
	
	if(m_object!=nullptr){
		
		m_object->Render();
		
		for(int i =0; i < m_children.size(); ++i){
			m_children[i]->Draw();
		}
	}	
}


void SceneNode::Update(glm::mat4 projectionMatrix, Camera* camera){
    if(m_object!=nullptr){

		if(m_parent){

			m_worldTransform = m_parent->m_worldTransform * m_localTransform;
		}else{
			
			m_worldTransform = m_localTransform;
		}
		
		m_shader.Bind();
    	
        m_shader.SetUniform1i("u_DiffuseMap",0);  

        m_shader.SetUniformMatrix4fv("model", &m_worldTransform.GetInternalMatrix()[0][0]);
        m_shader.SetUniformMatrix4fv("view", &camera->GetWorldToViewmatrix()[0][0]);
        m_shader.SetUniformMatrix4fv("projection", &projectionMatrix[0][0]);

        m_shader.SetUniform3f("lightColor", 1.0f,1.0f,1.0f);
        m_shader.SetUniform3f("lightPos",
                               camera->GetEyeXPosition() + camera->GetViewXDirection(),
                               camera->GetEyeYPosition() + camera->GetViewYDirection(),
                               camera->GetEyeZPosition() + camera->GetViewZDirection());
        m_shader.SetUniform1f("ambientIntensity",0.5f);
	
		for(int i =0; i < m_children.size(); ++i){
			m_children[i]->Update(projectionMatrix, camera);
		}
	}
}

Transform& SceneNode::GetLocalTransform(){
    return m_localTransform; 
}

Transform& SceneNode::GetWorldTransform(){
    return m_worldTransform; 
}
