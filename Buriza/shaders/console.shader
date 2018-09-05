[vertex shader]
#version 330 core
layout (location = 0) in vec2 aPosition;

uniform mat4 projection;
uniform mat4 model;

void main() {
    gl_Position = projection * model * vec4(aPosition, 0.0, 1.0);
}


[fragment shader]
#version 330 core

out vec4 color;

void main() {
    color = vec4(0.0, 0.0, 0.0, 0.8);
}
