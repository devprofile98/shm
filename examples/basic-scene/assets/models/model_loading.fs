#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLightSpace;

struct DirectionalLight {

  vec4 direction;
  vec4 ambient;
  vec4 diffuse;
  vec4 viewPos;

  // vec3 specular
};

struct PointLight {
  vec4 position;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  vec4 properties; // 1-constant, 2-linear, 3-quadratic 4-pad
};

struct SpotLight {
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

layout(std140) uniform Lights {
  DirectionalLight light;
  PointLight point[NUMBER_OF_POINT_LIGHT];
};

#define NUMBER_OF_SPOT_LIGHT 12

layout(std140) uniform Spots { SpotLight spots[NUMBER_OF_POINT_LIGHT]; };

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;
uniform sampler2D shadowMap;
uniform vec3 uColor;
uniform vec3 ambientColor;
uniform float iTime;
uniform vec4 kd;
uniform bool has_material = false;

float ShadowCalculation(vec4 fragPosLightSpace) {
  // perform perspective divide
  vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
  // transform to [0,1] range
  projCoords = projCoords * 0.5 + 0.5;
  // get closest depth value from light's perspective (using [0,1] range
  // fragPosLight as coords)
  float closestDepth = texture(shadowMap, projCoords.xy).r;

  // get depth of current fragment from light's perspective
  float currentDepth = projCoords.z;
  // check whether current frag pos is in shadow
  float bias = 0.005;
  float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

  //    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

  return shadow;
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal,
                               vec3 view_dir) {

  vec3 light_dir = normalize(-light.direction.xyz);
  vec3 ambient = light.ambient.rgb * texture(texture_diffuse1, TexCoords).rgb;
  float diff = max(dot(light_dir, normal), 0.0);
  vec3 diffuse = vec3(0.5, 0.3, 0.2) * kd.rgb * diff *
                 texture(texture_diffuse1, TexCoords).rgb;
  vec3 reflectDir = reflect(-light_dir, normal);
  float spec = pow(max(dot(view_dir, reflectDir), 0.0), 64.0);

  vec3 specular =
      vec3(0.5, 0.3, 0.2) * spec * texture(texture_diffuse1, TexCoords).rgb;
  float shadow = ShadowCalculation(FragPosLightSpace);
  if (!has_material)
    return ambient / 2 + (diffuse + specular) * (1 - shadow); // specular +
  //        return light.direction.rgb;
  else
    return kd.rgb;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos,
                         vec3 view_dir) {
  vec3 light_dir = normalize(light.position.xyz - fragPos);
  float d = length(light.position.xyz - fragPos);
  float attenuation = 4.0 / (light.properties.x + light.properties.y * d +
                             light.properties.z * (d * d));
  vec3 ambient = light.ambient.rgb * texture(texture_diffuse1, TexCoords).rgb;
  float diff = max(dot(light_dir, normal), 0.0);
  vec3 diffuse = light.diffuse.rgb * kd.rgb * diff *
                 texture(texture_diffuse1, TexCoords).rgb;
  vec3 reflectDir = reflect(-light_dir, normal);
  float spec = pow(max(dot(view_dir, reflectDir), 0.0), 6.0);
  vec3 specular =
      light.specular.rgb * spec * texture(texture_specular1, TexCoords).rgb;
  float shadow = ShadowCalculation(FragPosLightSpace);

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;
  if (!has_material)
    return (ambient / 2 + diffuse) * (1.0 - shadow);
  //        return vec3(0.5, 0.0, 0.5);
  else
    return kd.rgb;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos,
                        vec3 view_dir) {
  vec3 light_dir = normalize(light.position.xyz - fragPos);
  float d = length(light.position.xyz - fragPos);
  float attenuation =
      3.0 / (light.constant + light.linear * d + light.quadratic * (d * d));

  vec3 ambient = light.ambient.rgb * texture(texture_diffuse1, TexCoords).rgb;

  float diff = max(dot(light_dir, normal), 0.0);
  vec3 diffuse = light.diffuse.rgb * kd.rgb * diff *
                 texture(texture_diffuse1, TexCoords).rgb;

  vec3 reflectDir = reflect(-light_dir, normal);
  float spec = pow(max(dot(view_dir, reflectDir), 0.0), 64.0);

  vec3 specular =
      light.specular.rgb * spec * texture(texture_specular1, TexCoords).rgb;

  float theta = dot(light_dir, normalize(-light.direction.xyz));
  float epsilon = (light.cutOff - light.outerCutOff);
  float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
  diffuse *= intensity;
  specular *= intensity;

  float shadow = ShadowCalculation(FragPosLightSpace);

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;
  if (!has_material)
    return (ambient / 5) + (diffuse + specular) * (1.0 - shadow);
  //        return vec3(0.5, 0.0, 0.5);
  else
    return kd.rgb;
}

void main() {

  vec3 norm = normalize(Normal);

  vec3 viewDir = normalize(light.viewPos.xyz - FragPos);
  vec3 result = vec3(0);
  result += CalculateDirectionalLight(light, norm, viewDir);

  for (int i = 0; i < 3; i++) {
    result += CalculateSpotLight(spots[i], norm, FragPos, viewDir);
  }

  for (int j = 0; j < 4; j++) {
    result += CalculatePointLight(point[j], norm, FragPos, viewDir);
  }

  float shadow = ShadowCalculation(FragPosLightSpace);

  FragColor = vec4(result, texture(texture_diffuse1, TexCoords).a);
}
