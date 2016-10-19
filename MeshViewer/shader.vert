#version 430
 
in vec4 position;
in vec4 normal;

out vec4 pos2;
out vec4 pos;
out vec4 n;

uniform float time;
uniform mat4 MV;
uniform mat4 P;

void main()
{
	pos = position;
	pos2=position;
	n = normal;


	float scale_movement = 700.0;
	pos.z += scale_movement * sin((time*5.0 + 0.2 * pos.z)/2.0);
	pos.y += scale_movement * sin((time*5.0 + 0.2 * pos.x)/2.0);
	pos.x += scale_movement * sin((time*5.0 + 0.2 * pos.y)/2.0);
    gl_Position = P * MV * position;
} 