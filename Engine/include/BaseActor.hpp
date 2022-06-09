#ifndef SHM_ENGINE_BASE_ACTOR_H
#define SHM_ENGINE_BASE_ACTOR_H

#include <memory>
#include "shader.hpp"

namespace SHM {
    class BaseActor {
        public: 
            virtual void Load()=0;
            virtual std::shared_ptr<shader> setShader(const char*, const char*)=0;
            virtual std::shared_ptr<shader> setShader(std::shared_ptr<shader>)=0;
            virtual std::shared_ptr<shader> getShader()=0;
            virtual int loadModel(const char* file_path)=0;
            int model_id;
        protected:
            std::shared_ptr<shader> m_object_shader;
    };
}

#endif //SHM_ENGINE_BASE_ACTOR_H