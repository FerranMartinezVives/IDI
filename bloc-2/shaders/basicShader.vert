#version 330 core

in vec3 vertex;
in vec3 color;

uniform mat4 TG;

uniform mat4 ProjM;
uniform mat4 ViewM;

out vec3 fcolor;

void main()  {
    fcolor = color;
    gl_Position = ProjM * ViewM * TG * vec4 (vertex, 1.0);
}
