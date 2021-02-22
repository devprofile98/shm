#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;


uniform sampler2D texture_diffuse1;
uniform vec3 uColor;
uniform vec3 ambientColor;
uniform float iTime;


void main()
{    

    // vec4 texture_color = texture(texture_diffuse1, TexCoords);
    // texture_color.w = 0.5;

    vec2 coordinate = vec2(1920.0, 1080.0);
    vec3 sgt= vec3(1.0,1.0,1.0);
    vec4 new_color = vec4(0.0,0.0,0.0,0.0);
    float it = 0;
    if (gl_FragCoord.x > 1000 && gl_FragCoord.y < 0){
        it = 1;
        new_color = vec4(vec3(sin(gl_FragCoord.x)+ cos(iTime), sin(gl_FragCoord.y) + sin(iTime), cos(iTime)), it);
    }

    vec3 light_position = vec3(10.0,10.0,1.0);
    vec3 color = vec3(gl_FragCoord.x + gl_FragCoord.y ,  max(sin(gl_FragCoord.y) + sin(iTime), 0.2)  ,  max(cos(iTime), 0.2));

    vec3 ambient = ambientColor * vec3(0.0,0.0,0.0);

    vec3 norm = normalize(Normal);
    vec3 light_dir = normalize(light_position -FragPos);
    float diff = max(dot(light_dir, norm),0.0);
    vec3 diffuse = color * diff;

    

    vec3 result = diffuse + ambient;

    FragColor = vec4(mix(result, new_color.xyz, new_color.a), 1.0);
}

//* texture(texture_diffuse1, TexCoords)