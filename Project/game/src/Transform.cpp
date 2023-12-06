#include "Transform.hpp"

Transform::Transform(){
    LoadIdentity();
}

Transform::~Transform(){

}

void Transform::LoadIdentity(){
    m_modelTransformMatrix = glm::mat4(1.0f);
}

void Transform::Translate(float x, float y, float z){
        m_modelTransformMatrix = glm::translate(m_modelTransformMatrix,glm::vec3(x,y,z));                            
}

void Transform::Rotate(float radians, float x, float y, float z){
    m_modelTransformMatrix = glm::rotate(m_modelTransformMatrix, radians, glm::vec3(x,y,z));        
}

void Transform::Scale(float x, float y, float z){
    m_modelTransformMatrix = glm::scale(m_modelTransformMatrix,glm::vec3(x,y,z));        
}

GLfloat* Transform::GetTransformMatrix(){
    return &m_modelTransformMatrix[0][0];
}

glm::mat4 Transform::GetInternalMatrix() const{
    return m_modelTransformMatrix;
}

void Transform::ApplyTransform(Transform t){
    m_modelTransformMatrix = t.GetInternalMatrix();
}

Transform& Transform::operator*=(const Transform& t) {
    m_modelTransformMatrix =  m_modelTransformMatrix * t.GetInternalMatrix();
    return *this;
}

Transform& Transform::operator+=(const Transform& t) {
    m_modelTransformMatrix =  m_modelTransformMatrix + t.GetInternalMatrix();
    return *this;
}

Transform& Transform::operator=(const Transform& t) {
    m_modelTransformMatrix =  t.GetInternalMatrix();
    return *this;
}

Transform operator*(const Transform& lhs, const Transform& rhs){
    Transform result;

    result.m_modelTransformMatrix = lhs.GetInternalMatrix() * rhs.GetInternalMatrix();

    return result;
}

Transform operator+(const Transform& lhs, const Transform& rhs){
    Transform result;

    result.m_modelTransformMatrix = lhs.GetInternalMatrix() + rhs.GetInternalMatrix();

    return result;
}
