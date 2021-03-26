#include "Engine.hpp"


namespace SHM
{

std::vector<glm::vec3> vertices;
std::vector<glm::vec3> cubePosition;

std::vector<GLuint> indices;
GLuint vao ,vbo, indexBuffer;
glm::mat4 model = glm::mat4(1.0f);
// Add Vertices
shader newShader{"F:/project/SHM/PlayGround/assets/vert.vs", "F:/project/SHM/PlayGround/assets/frag.fs"};

Light light{
    glm::vec3(0.5,0.0,-2.0),
            glm::vec3(0.01,0.0,0.4),
            glm::vec3(-1.0,0.0,-2.0)
};

// TODO add Grid data and drawing completely into shader
void createGrid(){
    // create vertex data for Grid
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
    // draw grid in to the scene  with it's separate texture
    newShader.use();
    glBindVertexArray(vao);

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
                            glm::vec3(-1.0,-0.5,-0.3),
                            glm::vec3(-0.7,-0.2,-1.0),
                            glm::vec3(-1.2,-0.7,-0.2),
                            glm::vec3(-0.5,-0.8,-0.5),
                            glm::vec3(-1.1,-1.0,-0.5),
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
        model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
        newShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Engine::outLoop(){

    // write your configuration code to run before Engine::MainRenderLoop
    // createGrid();

    // setup data for ubo-vp

    glBindBuffer(GL_UNIFORM_BUFFER, Engine::getRenderer()->ubo_vp);
    glBufferSubData(GL_UNIFORM_BUFFER,0, sizeof(glm::mat4), glm::value_ptr(Engine::getRenderer()->getProjectionMatrix()));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(Engine::getRenderer()->getViewMatrix()));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBuffer(GL_UNIFORM_BUFFER, Engine::getRenderer()->ubo_lights);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 16, glm::value_ptr(light.position));
    glBufferSubData(GL_UNIFORM_BUFFER, 1* 16, 16, glm::value_ptr(light.ambient));
    glBufferSubData(GL_UNIFORM_BUFFER, 2* 16, 16, glm::value_ptr(light.diffuse));

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    newShader.createProgram();

    Engine::getRenderer()->LoadShaders(
                "F:/project/SHM/Engine/assets/model_loading.vs",
                "F:/project/SHM/Engine/assets/model_loading.fs"
                );
    Engine::getRenderer()->LoadModel("F:/project/SHM/Engine/assets/wooden watch tower23.obj");
    Engine::getRenderer()->shader_program.useGlobalVariables();



    newShader.useGlobalVariables();
    createCube();

}

void Engine::inLoop(){

    //    DrawGrids();
    glBindBuffer(GL_UNIFORM_BUFFER, Engine::getRenderer()->ubo_vp);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(Engine::getRenderer()->getViewMatrix()));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    drawCube();
    glBindBuffer(GL_UNIFORM_BUFFER, Engine::getRenderer()->ubo_lights);
    light.ambient = glm::vec3(glm::sin(glfwGetTime()),glm::cos(glfwGetTime()),-2.0);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 16, glm::value_ptr(light.ambient));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

}
