#version 330 core

in vec3 fcolor;

out vec4 FragColor;

uniform vec3 Filtre;
uniform bool InvisibilitatRick;

void main() {

	if (InvisibilitatRick) FragColor = vec4(0.0, 0.7, 0.0, 1.0);
	else FragColor = vec4(fcolor.x * Filtre.x, fcolor.y * Filtre.y, fcolor.z * Filtre.z, 1);

}
