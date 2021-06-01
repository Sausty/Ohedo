#version 450

out vec4 FragColor;

const float PI = 3.14159265359;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicRoughnessMap;
uniform sampler2D aoMap;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 camPos;

in vec2 f_Texcoords;
in vec3 f_Normal;
in vec3 f_WorldPos;

vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(normalMap, f_Texcoords).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(f_WorldPos);
    vec3 Q2  = dFdy(f_WorldPos);
    vec2 st1 = dFdx(f_Texcoords);
    vec2 st2 = dFdy(f_Texcoords);

    vec3 N   = normalize(f_Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}

void main()
{
    vec3 albedo     = pow(texture(albedoMap, f_Texcoords).rgb, vec3(2.2));
    vec4 metallicRoughness = texture(metallicRoughnessMap, f_Texcoords);
    float metallic = metallicRoughness.x;
    float roughness = metallicRoughness.y;
    float ao        = texture(aoMap, f_Texcoords).r;

    vec3 N = getNormalFromMap();
    vec3 V = normalize(camPos - f_WorldPos);

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);
    vec3 Lo = vec3(0.0);

    vec3 L = normalize(lightPos - f_WorldPos);
    vec3 H = normalize(V + L);
    float distance = length(lightPos - f_WorldPos);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = lightColor * attenuation;

    float NDF = DistributionGGX(N, H, roughness);   
    float G   = GeometrySmith(N, V, L, roughness);      
    vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
       
    vec3 numerator    = NDF * G * F; 
    float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; 
    vec3 specular = numerator / denominator;
    
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;	  

    float NdotL = max(dot(N, L), 0.0);        

    Lo += (kD * albedo / PI + specular) * radiance * NdotL; 

    vec3 ambient = vec3(0.03) * albedo * ao;
    
    vec3 color = ambient + Lo;

    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(color, 1.0);
}