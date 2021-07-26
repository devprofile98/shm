#ifndef SHYS
#define SHYS

#include "iostream"
#include "string"
#include <iostream>
#include <fstream>
#include <sstream>

namespace shys {
    class __declspec(dllexport) ShaderMaker{
        int a = 2;
        std::ofstream fragment_code;
        const char* shader_name;

        void fileReader(const char* path){
            std::ifstream file;
            file.exceptions(std::ifstream::failbit || std::ifstream::badbit);

            try {
                file.open(path);

                std::stringstream file_content;
                file_content << file.rdbuf();
                file.close();

                fragment_code << file_content.rdbuf();

            } catch (std::ifstream::failure e) {
                std::cout << "Shader Maker failed to open/close files ::: EXIT"<<std::endl;
            }
        }
    public:

        ShaderMaker(const char* shaderfile_name){
            this->shader_name = shaderfile_name;
        }

        ~ShaderMaker(){
            fragment_code.close();
        }

        std::string fragMain(){
            fragment_code.open(this->shader_name);
            fragment_code.close();
            // call all the functions here
            return std::string{}; // write main function
        }

        std::string resultToColor(){
            return std::string{"change color"};
        }

        std::string pixelateShader(){
            return std::string{"pixlate algorithm"};
        }
    };
}


#endif // SHYS
