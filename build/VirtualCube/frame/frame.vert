#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 mMat;
uniform mat4 vMat;
uniform mat4 pMat;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    gl_Position = pMat * vMat * mMat * vec4(aPosition, 1.0);

    FragPos = vec3(mMat * vec4(aPosition, 1.0));
    //法向量修正
    Normal = mat3(transpose(inverse(mMat))) * aNormal;
    TexCoord = aTexCoord;
}
