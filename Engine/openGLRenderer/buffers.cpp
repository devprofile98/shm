#include "buffers.hpp"

namespace SHM{
    namespace BUFFERS {
        int createNewUBO(std::string uniform_block_name, uint32_t buffer_size, int *binding_point_index){
            uint32_t temp_buffer_id;
            glGenBuffers(1, &temp_buffer_id);
            if (glGetError() == GL_INVALID_VALUE){
                std::cout<<"OPENGL::BUFFERS::NEWUBO::ERROR:: failed to create new uniform buffer object "<<std::endl;
                return GL_INVALID_VALUE;
            }
            glBindBuffer(GL_UNIFORM_BUFFER, temp_buffer_id);
            glBufferData(GL_UNIFORM_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);
            glBindBuffer(GL_UNIFORM_BUFFER,0);
            shader::m_uniform_blocks[uniform_block_name] = temp_buffer_id;
//            std::cout <<"XXX Value of temp buffer id"<< temp_buffer_id <<" with name "<< uniform_block_name<< " " << shader::m_ub_pairs.size() <<std::endl;
            glBindBufferRange(GL_UNIFORM_BUFFER, shader::m_uniform_blocks[uniform_block_name] -1 , temp_buffer_id, 0, buffer_size);
            if (glGetError() == GL_INVALID_VALUE){
                std::cout<<"OPENGL::BUFFERS::NEWUBO::ERROR:: binding point is out of specified target binding point range"<<std::endl;
                return -1;
            }
//            *binding_point_index = shader::m_ub_pairs.size();

            // add uniform block and corresponding binding point index to static Shader member variable
//            shader::m_ub_pairs.push_back(std::make_pair(uniform_block_name, (int)shader::m_ub_pairs.size()));
            return shader::m_uniform_blocks[uniform_block_name];
        }

        // upload partial data to specified ubo
        void uploadSubDataToUBO(uint32_t buffer_index, const glm::vec4 &data, uint32_t offset, uint32_t size){
            glBindBuffer(GL_UNIFORM_BUFFER, buffer_index);
            if(size == 0)
                glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::vec4), glm::value_ptr(data));
            else
                glBufferSubData(GL_UNIFORM_BUFFER, offset, size, glm::value_ptr(data));
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

        void uploadSubDataToUBO(uint32_t buffer_index, const glm::mat4 &data, uint32_t offset)
        {
            glBindBuffer(GL_UNIFORM_BUFFER, buffer_index);
            glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::mat4), glm::value_ptr(data));
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

        void uploadSubDataToUBO(uint32_t buffer_index, const glm::vec3 &data, uint32_t offset)
        {
            glBindBuffer(GL_UNIFORM_BUFFER, buffer_index);
            glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::vec4), glm::value_ptr(data));
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

        void uploadSubDataToUBO(uint32_t buffer_index, float data, uint32_t offset)
        {
            glBindBuffer(GL_UNIFORM_BUFFER, buffer_index);
            glBufferSubData(GL_UNIFORM_BUFFER, offset, 4, &data);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

    }
}
