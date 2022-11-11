// HINT: Don't forget to define the uniforms here after you pass them in in A3.js
uniform float ticks;

// The value of our shared variable is given as the interpolation between normals computed in the vertex shader
// below we can see the shared variable we passed from the vertex shader using the 'in' classifier
in vec3 interpolatedNormal;
in vec3 lightDirection;
in vec3 pointPosition;

float translation(float boxlength, float ticks){
    float percent = mod(ticks, 1.0);
    return percent * boxlength;
}


void main() {
    // HINT: Compute the light intensity the current fragment by determining
    // the cosine angle between the surface normal and the light vector.
    float intensity = dot(interpolatedNormal, lightDirection);

    // HINT: Pick any two colors and blend them based on light intensity
    // to give the 3D model some color and depth.

    // HINT: Render (or not) the current fragment based on its position on the armadillo
    // to get the polkadot effect.

    // HINT: You may find the GLSL mod function to be useful. It computes the modulus of two floats
    // Example: mod(0.3, 0.2) = 0.1

    // HINT: After you've obtained the correct position values on the armadillo, use the distance function
    // to see if they lie within a sphere.

    // HINT: `discard` throws away (does not render) the current fragment.

    // HINT: Set final rendered colour

    vec3 color1 = vec3(1.0, 0.0, 1.0);
    vec3 color2 = vec3(0.0, 1.0, 1.0);

    float trans = translation(0.15, ticks);
    float relativeX = mod(pointPosition.x, 0.15);
    float relativeY = mod(pointPosition.y + trans, 0.15);
    float relativeZ = mod(pointPosition.z, 0.15);
    vec3 relativePos = vec3(relativeX, relativeY, relativeZ);
    float distanceToCenter = distance(relativePos, vec3(0.075,0.075,0.075));
    if (distanceToCenter > sqrt(2.0) / 2.0/ 9.5) discard;
    else gl_FragColor = vec4(mix(color2, color1, intensity), 1.0);
}