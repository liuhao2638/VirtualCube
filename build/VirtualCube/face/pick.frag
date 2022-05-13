#version 430

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform vec4 pickingColor;

void main(void){
	
	color = pickingColor;

}
