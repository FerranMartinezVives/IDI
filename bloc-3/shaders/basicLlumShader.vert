#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

out vec3 matambFrag;
out vec3 matdiffFrag;
out vec3 matspecFrag;
out float matshinFrag;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

out vec4 posSCO;
out vec3 normSCO;

void main()
{	
    matambFrag = matamb;
    matdiffFrag = matdiff;
    matspecFrag = matspec;
    matshinFrag = matshin;
      
    posSCO = view * TG * vec4(vertex, 1.0);
    mat3 NormalMatrix = inverse(transpose(mat3(view * TG)));
    normSCO = NormalMatrix * normal;

    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
