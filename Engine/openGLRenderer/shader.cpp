
#include "shader.hpp"


// shader::shader(){
    
// }

// shader::~shader(){

// }


shader::shader(const char* vertexPath, const char* fragmentPath){

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // reading the shader file
    try{
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vertexStream, fragmentStream;

        vertexStream << vShaderFile.rdbuf();
        fragmentStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vShaderCode = vertexStream.str();
        fShaderCode = fragmentStream.str();

    }
    catch(std::ifstream::failure e){
        std::cout << "SHADER::FILE::READ_ERROR:: CANT OPEN FILE SUCCESFULLY"<<std::endl;
    }
}

bool shader::createProgram()
{
    int success;
    char* infolog = new char[512];

    // auto vertexCode = std::make_unique<const char *>(vShaderCode.c_str());
    // auto fragmentCode = std::make_unique<const char *>(fShaderCode.c_str());
    const char* vertexCode = vShaderCode.c_str();
    const char* fragmentCode=fShaderCode.c_str();
    std::cout<< " VERTEX SHADER CODE \n";
    std::cout<< vertexCode <<std::endl;
    std::cout << " ------------------------------- \n\n\n";
    
    std::cout<< " Fragment SHADER CODE \n";
    std::cout<< fragmentCode <<std::endl;
    std::cout << " ------------------------------- \n";
    m_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertex, 1, &vertexCode,nullptr);
    glCompileShader(m_vertex);

    glGetShaderiv(m_vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(m_vertex, 512, nullptr, infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
        return false;
    }

   m_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragment, 1, &fragmentCode,nullptr);
    glCompileShader(m_fragment);

    glGetShaderiv(m_fragment, GL_COMPILE_STATUS, &success);
    if(!success){

        glGetShaderInfoLog(m_vertex, 512, nullptr, infolog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
        return false;

    }

    ID = glCreateProgram();
    glAttachShader(ID, m_vertex);
    glAttachShader(ID, m_fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
        return  false;
    }
    
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(m_vertex);
    glDeleteShader(m_fragment);

    delete[] infolog;
//    free((char*)vertexCode);
//    free((char*)fragmentCode);
    return true;
}

void shader::use(){

    glUseProgram(ID);

}

void shader::useGlobalVariables() const{
    int ub_index{-1};
    std::cout<<"******************* in useGlobalVariable function "<< m_ub_pairs[0].first.c_str()<<std::endl;
    for(auto& pair: m_ub_pairs){
        ub_index = glGetUniformBlockIndex(this->ID, pair.first.c_str());
        std::cout<<"\n\n\n\n\n\n\nGL ACTIVE UNIFORM BLCOK INDEX IS :"<<ub_index<< " "<< pair.first<<std::endl;
        glUniformBlockBinding(this->ID, ub_index, pair.second);
    }
}


void shader::setVec3(const char* uniform_name,const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(this->ID, uniform_name),1, &value[0]);
}

void shader::setVec3(const char* uniform_name,float x, float y, float z) const 
{
    glUniform3f(glGetUniformLocation(this->ID, uniform_name), x, y, z);
}

void shader::setFloat(const char* uniform_name, float value) const
{
    glUniform1f(glGetUniformLocation(this->ID, uniform_name), value);
}
void shader::setInt(const char* uniform_name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, uniform_name), value); 
}
void shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

std::vector<std::pair<std::string, int>> shader::m_ub_pairs;
