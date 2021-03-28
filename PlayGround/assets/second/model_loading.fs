#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct Light {

    vec3 position;
    vec3 ambient;
    vec3 diffuse;
};

layout (std140) uniform Lights{
    Light light;
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;

uniform vec3 uColor;
uniform vec3 ambientColor;
uniform float iTime;


void main()
{

    vec4 texture_color = texture(texture_diffuse1, TexCoords);
//    vec4 new_color = vec4(0.0,0.0,0.0,0.0);
//    float it = 0;
//    if (gl_FragCoord.x > 5000 && gl_FragCoord.y < 0){
//        it = 1;
//        new_color = vec4(vec3(sin(gl_FragCoord.x)+ cos(iTime), sin(gl_FragCoord.y) + sin(iTime), cos(iTime)), it);
//    }

    vec3 light_position = light.position;//vec3(-0.0,-10.0,0.0);
    // vec3 color = vec3(gl_FragCoord.x + sin(gl_FragCoord.y) + cos(iTime) + 0.1 ,  cos(gl_FragCoord.y) + 0.3 + sin(iTime) + cos(iTime) ,  sin(iTime));
    // vec3 color = vec3(1.0, 0.3 + sin(iTime),0.4);
    vec3 color = vec3(texture_color.rgb);

    vec3 ambient = light.ambient * ambientColor * color;

    vec3 norm = normalize(Normal);
    vec3 light_dir = normalize(light_position - FragPos);
    float diff = max(dot(light_dir, norm),0.1);
    vec3 diffuse = color * diff ;

    vec3 result = diffuse + ambient;

    // FragColor = texture(texture_diffuse1, TexCoords);
    FragColor = vec4(result, 1.0);
}
