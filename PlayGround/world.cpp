#include "Engine.hpp"
#include "buffers.hpp"
#include "Light.hpp"

namespace SHM
{

std::vector<glm::vec3> vertices;
std::vector<glm::vec3> cubePosition;

std::vector<GLuint> indices;
GLuint vao ,vbo, indexBuffer;
glm::mat4 model = glm::mat4(1.0f);
// Add Vertices
shader newShader{"F:/project/SHM/PlayGround/assets/vert.vs", "F:/project/SHM/PlayGround/assets/frag.fs"};
std::shared_ptr<shader> newShader2 = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");
std::shared_ptr<shader> newShader3 = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");

int ub_index;

// TODO add Grid data and drawing completely into shader
void createGrid(){
    // create vertex data for Grid
    //    model = glm::translate(model, glm::vec3(-1.0,-1.0,-4.0));
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
    // draw grid in to the scene  with it's separate texture
    newShader.use();
    glBindVertexArray(vao);
    glm::mat4 model{1.0};
    newShader.setMat4("projection", Engine::getRenderer()->getProjectionMatrix());
    newShader.setMat4("view", Engine::getRenderer()->getViewMatrix());
    newShader.setMat4("model", model);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
    glLineWidth(1.0f);

}

void createCube(){
    // create it's data
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    cubePosition.insert(cubePosition.begin(),{
                            glm::vec3(-1.0, -1.0,3),

                        });
    // activate shader
    model = glm::translate(model, glm::vec3(-5.0,0.0,-2.0));
    //    model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
    newShader.use();
    // add data to vbo
    glBindVertexArray(0);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void drawCube(){
    // use the shader program
    newShader.use();
    // activate vao
    glBindVertexArray(vao);
    // draw
    for(auto& pos: cubePosition){
        glm::mat4 model{1.0f};

        model = glm::translate(model, pos);
        model = glm::scale(model, glm::vec3(0.08, 0.08, 0.08));
        newShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Engine::outLoop(){

    // write your configuration code to run before Engine::MainRenderLoop
    // createGrid();
    newShader.createProgram();
    int b{-1};
    ub_index=SHM::BUFFERS::createNewUBO("MyMat", sizeof(glm::vec4), &b);
    std::cout<<"new binding point index is :"<<b<<std::endl;
    SHM::BUFFERS::uploadSubDataToUBO(ub_index, glm::vec4(0.0, 0.0,1.0,1.0));
    newShader2->createProgram();
    glm::mat4 model = glm::translate(glm::mat4{1.0}, glm::vec3(-3.0, -1.0, -1.0));
    model = glm::translate(model, glm::vec3(10.0, 10.0, 10.0));
    //    newShader2->setMat4("model", model);
    newShader3->createProgram();
    uint32_t tower_id = Engine::getRenderer()->LoadModel("F:/project/SHM/Engine/assets/wooden watch tower23.obj", newShader2);
    uint32_t gun_id = Engine::getRenderer()->LoadModel("F:/project/SHM/PlayGround/assets/second/untitled.obj", newShader3);
    newShader2->use();
    newShader2->setMat4("model", model);
    newShader2->useGlobalVariables();
    newShader.useGlobalVariables();
    newShader3->useGlobalVariables();

    createCube();

    SHM::BUFFERS::uploadSubDataToUBO(Engine::getRenderer()->ubo_lights,
                                     glm::vec3(0.0, 2.0,0.0), sizeof(glm::vec4));

    // Point Light data to Lighting UBO
    SHM::BUFFERS::uploadSubDataToUBO(Engine::getRenderer()->ubo_lights,
                                     glm::vec4(-1.0, -1.0,3, 0.0), 4*sizeof(glm::vec4));
    SHM::BUFFERS::uploadSubDataToUBO(Engine::getRenderer()->ubo_lights,
                                     glm::vec4(0.3,0.72 ,0.72, 0.0), 5*sizeof(glm::vec4));
    SHM::BUFFERS::uploadSubDataToUBO(Engine::getRenderer()->ubo_lights,
                                     glm::vec4(0.3,0.72 ,0.72, 0.0), 6*sizeof(glm::vec4));

    SHM::BUFFERS::uploadSubDataToUBO(Engine::getRenderer()->ubo_lights,
                                     1.0f, 7*sizeof(glm::vec4));
    SHM::BUFFERS::uploadSubDataToUBO(Engine::getRenderer()->ubo_lights,
                                     0.35f, 7*sizeof(glm::vec4) + 4);
    SHM::BUFFERS::uploadSubDataToUBO(Engine::getRenderer()->ubo_lights,
                                     0.44f, 7*sizeof(glm::vec4) + 8);



    SpotLight sl{{0, -1, 0}, {0,0,0}};
    SpotLight sl2{{0, -1, 0}, {-1,0,-1}};
    SpotLight sl3{{0, -1, 0}, {-2,0,-1}};

//    sl3.setDiffuse1({0.0f, 0.8f, 0.9f});




}

void Engine::inLoop(){

    //    DrawGrids();
    Engine::getRenderer()->changeScale(0, glm::vec3(0.1, 0.1, 0.1));

    SHM::BUFFERS::uploadSubDataToUBO(Engine::getRenderer()->ubo_vp, Engine::getRenderer()->getViewMatrix(), sizeof(glm::mat4));
    SHM::BUFFERS::uploadSubDataToUBO(ub_index, glm::vec4(glm::sin(glfwGetTime()), 0.0, 1-glm::sin(glfwGetTime()),1.0));
    glm::mat4 model{1.0};
    model = glm::translate(model, glm::vec3(-1.0, -1.0, -1.0));
    model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
    newShader2->use();
    newShader2->setMat4("model", model);
    glm::mat4 model2{1.0};
    model2 = glm::translate(model2, glm::vec3(-1.0, -1.0,2.6));
    model2 = glm::scale(model2, glm::vec3(0.3, 0.3, 0.3));
    newShader3->use();
    newShader3->setMat4("model", model2);

    SHM::BUFFERS::uploadSubDataToUBO(
                Engine::getRenderer()->ubo_lights,
                glm::vec3(glm::sin(glfwGetTime()), glm::cos(glfwGetTime()),-2.0));

    SHM::BUFFERS::uploadSubDataToUBO(Engine::getRenderer()->ubo_lights,
                                     glm::vec4(glm::sin(glfwGetTime()), 0.0, 1-glm::sin(glfwGetTime()),1.0), 5*sizeof(glm::vec4));

//    SHM::BUFFERS::uploadSubDataToUBO(Engine::getRenderer()->ubo_lights,
//                                     glm::vec4(Engine::getCamera()->m_position, 0.0), 8*sizeof(glm::vec4));

//    SHM::BUFFERS::uploadSubDataToUBO(Engine::getRenderer()->ubo_lights,
//                                     glm::vec4(Engine::getCamera()->m_front, 0.0), 9*sizeof(glm::vec4));

//    Engine::getRenderer()->GetUtility()->uploadVec4(Engine::getRenderer()->ubo_lights,
//                                                    glm::vec4(0.0, 1.0, 0.0, 0.0), 11*sizeof(glm::vec4), 0);

    //m_renderer->shader_program.setFloat("iTime", glfwGetTime());
//    std::cout<<Engine::getCamera()->m_front.x<<" "<< Engine::getCamera()->m_front.y <<" "<<Engine::getCamera()->m_front.z<<std::endl;

    drawCube();

}

}
