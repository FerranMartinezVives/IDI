#version 330 core

in vec3 vertex;

uniform mat4 TG;

uniform vec3 color;

void main()  {

    gl_Position = TG * vec4 (vertex, 1.0);
}
