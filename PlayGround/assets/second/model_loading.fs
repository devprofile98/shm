#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct DirectionalLight {

    vec4 direction;
    vec4 ambient;
    vec4 diffuse;
    vec4 viewPos;

    // vec3 specular
};

struct PointLight{

    vec4 position;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 properties; // 1- constant, 2-linear, 3-quadratic 4-pad
//    float constant;
//    // vec3 specular
//    float linear;
//    float quadratic;
//    float pad;
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
    float pad;
    float pad1;
    float pad2;

};

#define NUMBER_OF_POINT_LIGHT 12

layout (std140) uniform Lights{
    DirectionalLight light;
    PointLight point[NUMBER_OF_POINT_LIGHT];

};

#define NUMBER_OF_SPOT_LIGHT 12

layout (std140) uniform Spots{

    SpotLight spots[NUMBER_OF_POINT_LIGHT];

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


//vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 view_dir){

//    vec3 light_dir = normalize(-light.direction.xyz);

//    vec3 ambient = light.ambient.rgb * texture(texture_diffuse1, TexCoords).rgb;

//    float diff = max(dot(light_dir,normal), 0.0);
//    vec3 diffuse = light.diffuse.rgb * diff * texture(texture_diffuse1, TexCoords).rgb;

//    vec3 reflectDir = reflect(-light_dir, normal);
//    float spec = pow(max(dot(view_dir, reflectDir), 0.0), 64.0);

//    vec3 specular = light.specular.rgb * spec * texture(texture_specular1, TexCoords).rgb;

//    return (specular + ambient + diffuse);
//}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 view_dir ){
    vec3 light_dir = normalize(light.position.xyz - fragPos);
    float d = length(light.position.xyz - fragPos);
    float attenuation = 1.0 / (light.properties.x + light.properties.y*d + light.properties.z*(d*d));

    vec3 ambient = light.ambient.rgb * texture(texture_diffuse1, TexCoords).rgb;

    float diff = max(dot(light_dir,normal), 0.0);
    vec3 diffuse = light.diffuse.rgb * diff * texture(texture_diffuse1, TexCoords).rgb;

    vec3 reflectDir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflectDir), 0.0), 6.0);

    vec3 specular = light.specular.rgb * spec * texture(texture_specular1, TexCoords).rgb;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 view_dir){
    vec3 light_dir = normalize(light.position.xyz - fragPos);
    float d = length(light.position.xyz - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear*d + light.quadratic*(d*d));

    vec3 ambient = light.ambient.rgb * texture(texture_diffuse1, TexCoords).rgb;

    float diff = max(dot(light_dir, normal), 0.0);
    vec3 diffuse = light.diffuse.rgb * diff * texture(texture_diffuse1, TexCoords).rgb;

    vec3 reflectDir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflectDir), 0.0), 64.0);

    vec3 specular = light.specular.rgb * spec * texture(texture_specular1, TexCoords).rgb;

    float theta = dot(light_dir, normalize(-light.direction.xyz));
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff)/ epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}



void main(){

    vec3 norm = normalize(Normal);

    vec3 viewDir = normalize(light.viewPos.xyz - FragPos);
    vec3 result= vec3(0);
    for(int i = 0; i < 3; i++)
       result += CalculateSpotLight(spots[i], norm, FragPos, viewDir);

    for(int j = 0; j < 2; j++){
        result += CalculatePointLight(point[j], norm, FragPos, viewDir);
        }
    //vec3 temp = CalculateSpotLight(spots[1], norm, FragPos, viewDir );

    FragColor = vec4(result, 1.0);

}
