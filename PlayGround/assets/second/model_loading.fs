#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct Light {

vec3 direction; // 0 - vec4
vec3 ambient;   // vec4 - 2* vec4
vec3 diffuse;   // 2vec4 - 3* vec4
vec3 viewPos;
// vec3 specular
};

struct PointLight{

vec4 position; // 3vec4 - 4* vec4
vec4 ambient;  // 4vec4 - 5* vec4
vec4 diffuse;  // 5vec4 - 6* vec4
// vec3 specular
float constant;
float linear;
float quadratic;
float pad;
};

struct SpotLight{
vec4 position;
vec4 direction;

vec4 ambient;
vec4 diffuse;
vec4 specular;

float constant;
float linear;
float quadratic;
float cutOff;
float outerCutOff;
};


layout (std140) uniform Lights{
Light light;
PointLight point;
SpotLight spot;
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


void main(){

vec3 light_dir = normalize(spot.position.xyz - FragPos);

vec3 ambient = spot.ambient.rgb * texture(texture_diffuse1, TexCoords).rgb;

vec3 norm = normalize(Normal);
float diff = max(dot(light_dir, norm), 0.0);
vec3 diffuse = spot.diffuse.rgb * diff * texture(texture_diffuse1, TexCoords).rgb;

vec3 viewDir = normalize(light.viewPos - FragPos);
vec3 reflectDir = reflect(-light_dir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.0);
vec3 specular = spot.specular.rgb * spec * texture(texture_specular1, TexCoords).rgb;

float theta = dot(light_dir, normalize(-spot.direction.xyz));
float epsilon = (spot.cutOff - spot.outerCutOff);
float intensity = clamp((theta - spot.outerCutOff)/ epsilon, 0.0, 1.0);
diffuse*=intensity;
specular*= intensity;


float d = length(spot.position.xyz - FragPos);
float attenuation = 1.0 / (spot.constant + spot.linear*d + spot.quadratic*(d*d));

ambient*=attenuation;
diffuse  *= attenuation;
specular *= attenuation;

vec3 result =  ambient*(0.5) + diffuse + specular;
FragColor = vec4(result, 1.0);

}

//void main()
//{

//    vec4 texture_color = texture(texture_diffuse1, TexCoords);
////    vec3 light_position = light.position;//vec3(-0.0,-10.0,0.0);
//    vec3 color = vec3(texture_color.rgb);
//    vec3 ambient = point.ambient.xyz * ambientColor * color;
//    vec3 norm = normalize(Normal);
//    vec3 light_dir = normalize(point.position.xyz - FragPos);
//    float diff = max(dot(light_dir, norm),0.0);
//    vec3 diffuse = point.diffuse.xyz * color * diff ;

//    vec3 viewDir = normalize(light.viewPos - FragPos);
//    vec3 reflectDir = reflect(-light_dir, norm);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.0);
//    vec3 specular =   spec * texture(texture_specular1, TexCoords).rgb;

//    float d = length(point.position.xyz - FragPos);
//    float attenuation = 1.0 / (point.constant + point.linear * d +
//                                point.quadratic * (d * d));

//    ambient *= attenuation;
//    diffuse *= attenuation;
//    specular *= attenuation;

//    vec3 result =  ambient.xyz + diffuse.xyz + specular.xyz ;

//    FragColor = vec4(result, 1.0);
//}
