#version 430
 
out vec4 outputF;

in vec4 pos2;
in vec4 pos;
in vec4 n;

uniform float time;
uniform vec3 lDir;

void main()
{

	vec3 normal = vec3(n.x, n.y, n.z);
	// Colors 
	vec3 ambient_color = vec3(1.0, 1.0, 1.0);
	vec3 diffuse_color = vec3(0.4, 0.2, 0.6);
	vec3 specular_color = vec3(0.9, 0.9, 0.9);

	// Diffuse
	float a = clamp( dot( normal, lDir ), 0.0, 1.0);
    vec3 diffuse = a * diffuse_color;

	// Ambient
	float b = 0.2;
	vec3 ambient = ambient_color * b;

	// Output
	outputF = vec4( diffuse + ambient, 1.0);
	outputF = vec4(normal, 1.0);

} 