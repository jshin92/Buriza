#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 model;

void main() {
    gl_Position = projection * model * vec4(aPosition, 1.0);
    TexCoord = vec2(aTexCoord.x, 1.0f - aTexCoord.y);
}