#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

//uniform mat4 projection;

void main() {
    //gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    gl_Position = vec4(aPosition, 1.0);
    TexCoord = aTexCoord;
}