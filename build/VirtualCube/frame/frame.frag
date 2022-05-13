#version 330 core
 
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 lightColor;//光强
uniform vec3 lightPos;//光的颜色
uniform vec3 viewPos;//观察者坐标

uniform sampler2D texture;

void main()
{
    //环境光
    float ambientStrength = 0.1;//环境光强参数
    vec3 ambient = ambientStrength * lightColor;//环境光强
 
    //漫反射
    vec3 norm = normalize(Normal);//法向量标准化
    vec3 lightDir = normalize(lightPos - FragPos);//光线向量标准化
    float diff = max(dot(norm, lightDir), 0.0);//norm, lightDir点乘
    vec3 diffuse = diff * lightColor;
 
    //镜面反射
    float specularStrength = 0.5;//0.5
    vec3 viewDir = normalize(viewPos - FragPos);//观察者视线
    vec3 reflectDir = reflect(-lightDir, norm);//法线轴的反射向量
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
 
    vec4 objectColor = texture2D(texture,TexCoord);//物体颜色是纹理贴图
    //vec3 objectColor = vec3(1.0f,0.5f,0.31f);
    //vec3 objectColor = vec3(0.0f,0.0f,0.0f);
    vec3 result = (ambient + diffuse + specular);

    FragColor = vec4(result, 1.0) * objectColor;

}
