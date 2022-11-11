#version 330 core
// HINT: Don't forget to define the uniforms here after you pass them in in A3.js
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float kAmbient;
uniform float kDiffuse;
uniform float kSpecular;
uniform float shininess;
// The value of our shared variable is given as the interpolation between normals computed in the vertex shader
// below we can see the shared variable we passed from the vertex shader using the 'in' classifier
in vec3 interpolatedNormal;
in vec3 lightDirection;
in vec3 viewPosition;

out vec4 FragColor;

void main() {
    // HINT: Compute the ambient component. This component is uniform across surface.
    vec3 lambientColor = kAmbient * ambientColor;

    // HINT: Compute the diffuse component. This component varies with direction.
    // You may find it useful to review Chapter 14.2 in the textbook.
    vec3 linterpolatedNormal = normalize(interpolatedNormal);
    vec3 ldiffuseColor= kDiffuse * dot(linterpolatedNormal, lightDirection) * diffuseColor;

    // HINT: Compute the specular component. This component varies with direction,
    // and is what gives the model its "shine." You may find it useful to review
    // Chapter 14.3 in the textbook.
    vec3 lviewDirection = -normalize(viewPosition);
    vec3 bounceVec = normalize(-lightDirection + 2.0f * dot(lightDirection, linterpolatedNormal) * linterpolatedNormal);
    vec3 lspecularColor = kSpecular * pow(clamp(dot(bounceVec, lviewDirection), 0.0, 1.0), shininess) * specularColor;


    // HINT: Set final rendered colour to be a combination of the three components
    FragColor = vec4(lambientColor + ldiffuseColor + lspecularColor, 1.0);
    
}