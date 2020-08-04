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

float ussin(float _x) {
    return (sin(_x)+1.) * .5;
}


void main (void){
    
    vec2 uv =  varyingtexcoord.xy;
    uv += snoise(uv) * 0.2;

    float pct = ussin(uv.x *30.+ u_time);
    
    vec3 col = vec3(0);
    col.r += step(0.9, pct);
    col.g += step(0.9, pct + .3);
    col.b += step(0.9, pct + 0.1);
    col *= 0.4;
    
    outputColor = vec4(col, .4) * globalColor;
}
