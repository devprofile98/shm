#include <chrono>

#include "Engine.hpp"
#include "buffers.hpp"
#include "Light.hpp"
#include "physics.hpp"


namespace SHM
{

std::vector<glm::vec3> vertices;
std::vector<glm::vec3> cubePosition;

std::vector<GLuint> indices;
GLuint vao ,vbo, indexBuffer;
glm::mat4 model = glm::mat4(1.0f);
// Add Vertices
std::shared_ptr<shader> newShader = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");
std::shared_ptr<shader> newShader2 = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");
std::shared_ptr<shader> newShader3 = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");
std::shared_ptr<shader> newShader4 = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");

int ub_index;
bool first_time = true;

cyclon::Particle p1{};
auto now = std::chrono::high_resolution_clock::now();

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
    newShader->createProgram();
    newShader->use();
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
    newShader->use();
    glBindVertexArray(vao);
    glm::mat4 model{1.0};
    newShader->setMat4("projection", Engine::getRenderer()->getProjectionMatrix());
    newShader->setMat4("view", Engine::getRenderer()->getViewMatrix());
    newShader->setMat4("model", model);

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
    newShader->use();
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
    newShader->use();
    // activate vao
    glBindVertexArray(vao);
    // draw
    for(auto& pos: cubePosition){
        glm::mat4 model{1.0f};

        model = glm::translate(model, pos);
        model = glm::scale(model, glm::vec3(8, 8, 8));
        newShader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Engine::outLoop(){

    // write your configuration code to run before Engine::MainRenderLoop


    newShader->createProgram();

//    createGrid();
    createCube();

    int b{-1};
    newShader2->createProgram();
    newShader->useGlobalVariables();

    glm::mat4 model = glm::translate(glm::mat4{1.0}, glm::vec3(-3.0, -1.0, -1.0));
//    model = glm::translate(model, glm::vec3(10.0, 10.0, 10.0));

    newShader3->createProgram();
    Engine::getRenderer()->LoadModel("F:/project/SHM/Engine/assets/wooden watch tower23.obj", newShader2);
    Engine::getRenderer()->LoadModel("F:/project/SHM/PlayGround/assets/second/untitled.obj", newShader3);

    newShader2->use();
    newShader2->setMat4("model", model);
    newShader2->useGlobalVariables();

    newShader3->useGlobalVariables();

    // Point Light data to Lighting UBO
    PointLight pl{{-2,-0.7,3}, {1.0, 1.0, 0.0}};
    PointLight pl2{{1,-0.7,5}, {1.0f, 0.0f, 1.0f}};


    SpotLight sl{{0, -1, 0}, {0,0,0}};
    sl.setDiffuse({0.0f, 0.0f, 1.0f});
    SpotLight sl2{{0, -1, 0}, {-1,1,-1},{0.0f, 1.0f, 0.0f}};
    SpotLight sl3{{0, -1, 0}, {-2,-0.5,-1}};

    p1.inverseMass = ((cyclon::real)1.0)/2.0f;
    p1.velocity = cyclon::Vector3{0.0f, 3.0f, 0.3f};
    p1.acceleration = cyclon::Vector3{0.0f, -1.0f, 0.0f};
    p1.damping = 0.99f;
    p1.position = cyclon::Vector3{0, 0,-0.4};


}

void Engine::inLoop(){

//    DrawGrids();
    drawCube();

    Engine::getRenderer()->changeScale(0, glm::vec3(0.1, 0.1, 0.1));

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


    glm::mat4 model4{1.0};
    //    model4 = glm::translate(model4, glm::vec3(0, 0,-0.4));
    model4 = glm::translate(model4, glm::vec3(
                                p1.position.x,
                                p1.position.y,
                                p1.position.z
                                ));
    model4 = glm::scale(model4, glm::vec3(0.03, 0.03, 0.03));
    newShader4->use();
    newShader4->setMat4("model", model4);
    cyclon::real duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - now)
            .count();
    //    std::cout << p1.position.x << " "<< p1.position.y << " "<<duration<<std::endl;
    if (std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::high_resolution_clock::now() - now)
            .count() > 10){
        p1.integrate(0.0016f);
//        if (first_time){
//            Engine::saveImage("picture.png");
//            first_time = !first_time;
//        }
    }

    //    std::cout << p1.position.x << " "<< p1.position.y << " "<<p1.position.z<<std::endl;

    SHM::BUFFERS::uploadSubDataToUBO(
                Engine::getRenderer()->ubo_lights,
                glm::vec3(glm::sin(glfwGetTime()), glm::cos(glfwGetTime()),-2.0));



}
}
