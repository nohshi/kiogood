#version 400
#pragma include "noise.glsl"

#define PI 3.14159265358979


uniform sampler2D tex0; ////this is "draw in the shader"

in vec2 varyingtexcoord;
out vec4 outputColor;

uniform vec2 u_resolution;
uniform float u_time;
uniform float u_val1;


float usnoise(vec4 a) {
    return (snoise( a ) + 1.) * 0.5;
}

float usnoise(vec3 a) {
    return (snoise( a ) + 1.) * 0.5;
}


float usnoise(vec2 a) {
    return (snoise( a ) + 1.) * 0.5;
}


void main (void){
    
    vec2 uv =  varyingtexcoord.xy;
    uv += usnoise(vec2(uv*1.3 + u_time*0.3)) * .5 * u_val1;
    uv = fract(uv);
    
    vec3 t = texture(tex0,uv).rgb;
    vec3 col = vec3(0.);
    col = 1.-t;
    
    outputColor = vec4(col, 1.);

}
