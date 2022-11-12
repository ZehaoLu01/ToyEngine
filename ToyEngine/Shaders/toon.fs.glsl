#version 330 core
// The value of our shared variable is given as the interpolation between normals computed in the vertex shader
// below we can see the shared variable we passed from the vertex shader using the 'in' classifier
in vec3 interpolatedNormal;
in vec3 lightDirection;
in vec3 viewPosition;
in float fresnel;

void main() {
    // HINT: Compute the light intensity the current fragment by determining
    // the cosine angle between the surface normal and the light vector
    float cosVal = dot(interpolatedNormal, lightDirection);
    // HINT: Define ranges of light intensity values to shade. GLSL has a
    // built-in `ceil` function that you could use to determine the nearest
    // light intensity range.
    // float intensity1 = 0.0;
    // float intensity2 = 1.0;
    // float intensity3 = 2.0;
    // float intensity4 = 3.0;
    float actualIntensity = ceil(cosVal * 4.0)/4.0;


    // HINT: You should use two tones of colors here; `toonColor` is a yellow
    // color for brighter areas and `toonColor2` is a red color for darker areas.
    // Use the light intensity to blend the two colors.
    vec3 toonColor = vec3(1.0,1.0,0);
    vec3 toonColor2 = vec3(1.0,0.0,0.0);
    

    // HINT: To achieve the toon silhouette outline, set a dark fragment color
    // if the current fragment is located near the edge of the 3D model.
    // Use a reasonable value as the threshold for the silhouette thickness
    // (i.e. proximity to edge).


    // HINT: Set final rendered colour
    if(fresnel<0.4) gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    else gl_FragColor = vec4(mix(toonColor2,toonColor,actualIntensity), 1.0);
    
}