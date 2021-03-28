#version 330 core

layout(std140) uniform MyMat{
    vec4 color;
};

out vec4 FragColor;

void main(){
//     vec3 color = vec3( gl_FragCoord.x + sin(gl_FragCoord.y) + cos(iTime) + 0.1 ,
//                        cos(gl_FragCoord.y) + 0.3 + sin(iTime) + cos(iTime) ,
//                        sin(iTime));
    FragColor = color;
}
