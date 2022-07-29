#version 420 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;

out vec2 texCoord;

uniform mat4 transform;
uniform mat4 viewport;
uniform mat4 projection;

void main() {
    gl_Position = transform * viewport * projection * vec4(inPos, 1.0);
    texCoord = vec2(inTexCoord.x, inTexCoord.y);
}