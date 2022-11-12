#version 330 core
// The uniform variable is set up in the javascript code and the same for all vertices
uniform vec3 spherePosition;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normalMat;


layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoordinate;

// The shared variable is initialized in the vertex shader and attached to the current vertex being processed,
// such that each vertex is given a shared variable and when passed to the fragment shader,
// these values are interpolated between vertices and across fragments,
// below we can see the shared variable is initialized in the vertex shader using the 'out' classifier
out vec3 interpolatedNormal;
out vec3 lightDirection;
out vec3 viewPosition;
out vec2 aTextureCoordinate;

void main() {
    // HINT: Compute the vertex position in VCS
    viewPosition = (view * model * vec4(position, 1.0)).xyz;

    // HINT: Compute the light direction in VCS
    lightDirection = normalize(view * vec4(spherePosition, 1.0) - view * model * vec4(position, 1.0)).xyz;
    
    // HINT: Interpolate the normal
    interpolatedNormal = normalize((normalMat * vec4(normal,0.0f)).xyz);

    aTextureCoordinate = textureCoordinate;

    // Multiply each vertex by the model matrix to get the world position of each vertex, 
    // then the view matrix to get the position in the camera coordinate system, 
    // and finally the projection matrix to get final vertex position
    gl_Position = projection * view * model * vec4(position, 1.0);
}