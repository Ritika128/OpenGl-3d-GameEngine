#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

uniform sampler2D albedoMap;                                            //  all required material parameters
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;

uniform vec3 lightPositions[4];                                         //  positions of all light sources
uniform vec3 lightColors[4];                                            //  colors of all light sources

uniform vec3 camPos;                                                    //  camera position value

const float myPi = 3.14159265359;


void main()
{       
    vec3 albedo = pow(texture(albedoMap, TexCoords).rgb, vec3(2.2));    //  get all required textures
    float metallic = texture(metallicMap, TexCoords).r;
    float roughness = texture(roughnessMap, TexCoords).r;
    float ao = texture(aoMap, TexCoords).r;

                                         
    vec3 V = normalize(camPos - WorldPos);                              //  calculate the view vector

    vec3 F0 = vec3(0.04);                                               //  calculate reflectance at normal incidence
    F0 = mix(F0, albedo, metallic);                                     //  use F0 of 0.04 for dia-electric and F0 for metal material

    vec3 Lo = vec3(0.0);                                                //  holds result of the reflectance equation, so it is sum of radiance values for all light sources

    for (int i = 0; i < 4; i++)                                         //  we need to handle all present light sources and calculate radiance
    {
        vec3 L = normalize(lightPositions[i] - WorldPos);               //  calculate light direction vector
        vec3 H = normalize(V + L);                                      //  calculate halfway vector

        float distance = length(lightPositions[i] - WorldPos);          //  get distance and attenuation values of the light source
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lightColors[i] * attenuation;                   //  calculate radiance vector of light
                                                                        //  we have to calculate Cook-Torrance BRDF
                                               

       

             
    }   

    vec3 ambient = vec3(0.03) * albedo * ao;                            //  calculate ambient lighting vector from albedo and ambient occlusion maps

    vec3 color = ambient + Lo;                                          //  final color value is sum of ambient and radiance values
    color = color / (color + vec3(1.0));                                //  we need to use HDR tonemapping
    color = pow(color, vec3(1.0 / 2.2));                                //  now apply the gamma correction

    FragColor = vec4(color, 1.0);
}
