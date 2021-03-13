#include "Engine.hpp"


namespace SHM
{

std::vector<glm::vec3> vertices;
std::vector<GLuint> indices;
GLuint vao ,vbo, indexBuffer;
glm::mat4 model = glm::mat4(1.0f);
// Add Vertices
shader newShader{"F:/project/SHM/PlayGround/assets/vert.vs", "F:/project/SHM/PlayGround/assets/frag.fs"};

void Engine::outLoop(){

    // write your configuration code to run before Engine::MainRenderLoop

    model = glm::translate(model, glm::vec3(-1.0,-1.0,-4.0));

    for(int i=0;i<40;i+=2){
        vertices.push_back(glm::vec3(-1.0f,-0.0,0.f + i/40.0f));
        vertices.push_back(glm::vec3(+1.0f,-0.0,0.f + i/40.0f));
        indices.push_back(i);
        indices.push_back(i+1);
    }
    float value = 80;
    for(int i=40;i<value;i+=2){
        vertices.push_back(glm::vec3(-1.5f+i*2/value,0.0f,0.f));
        vertices.push_back(glm::vec3(-1.5f+i*2/value,0.0f,1.f));
        indices.push_back(i);
        indices.push_back(i+1);
    }
    newShader.createProgram();
    newShader.use();
    std::cout << "use count of camera is :"<<Engine::getCamera().use_count()<<std::endl;
    glBindVertexArray(0);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices.front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(glm::vec3),0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

}
void DrawGrids(){
    
    newShader.use();
    glBindVertexArray(vao);

    newShader.setMat4("projection", Engine::getRenderer()->getProjectionMatrix());
    newShader.setMat4("view", Engine::getRenderer()->getViewMatrix());
    newShader.setMat4("model", model);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
    glLineWidth(1.0f);

}
void Engine::inLoop(){

    DrawGrids();

}



}
