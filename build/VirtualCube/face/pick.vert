#version 430

layout (location = 0) in vec3 aPosition;



uniform mat4 mMat;
uniform mat4 vMat;
uniform mat4 pMat;


void main(void)
{	gl_Position = pMat * vMat * mMat * vec4(aPosition, 1.0);

}