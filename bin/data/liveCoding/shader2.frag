#version 410

#pragma include "noise.glsl"
#pragma include "util.glsl"

#define PI 3.14159265358979

uniform vec4 globalColor;

in vec2 varyingtexcoord;
out vec4 outputColor;

uniform vec2 u_resolution;
uniform float u_time;
uniform float u_val0;
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
    uv += snoise(uv) * 0.2;

    float pct = fract(uv.x *10.+ u_time*2.);
    
    vec3 col = vec3(0);
    col.r += step(0.6, pct) * 0.5;
    col.g += step(0.9, pct + .3) * 0.2;
    col.b += step(0.9, pct + 0.1) * 0.2;
    col *= 0.8;
    
    outputColor = vec4(col, col.r) * globalColor;
}
