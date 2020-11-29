#version 400

#pragma include "util.glsl"

#define PI 3.14159265358979


uniform sampler2D tex0; ////this is "draw in the shader"

in vec2 varyingtexcoord;
out vec4 outputColor;

uniform vec2 u_resolution;
uniform float u_time;
uniform float u_rand;
uniform float u_val1;

vec2 tornado(float _r) {
    float t = u_time * 5.1;
    vec2 p;
    p.x = cos(t) * _r;
    p.y = sin(t) * _r;
    return p;
}

float ussin(float _x){
    return (sin(_x) + 1) * 0.5;
}

void main (void){
    
    vec2 uv =  varyingtexcoord.xy;
    float shiftId = floor(uv.y*10);
    
    uv.x += rand(shiftId*13. + u_time*0.1) * 0.1 * u_val1;
    
    float shift = u_rand * PI;
    
    float r = texture(tex0,uv + tornado(shift)*0.01).r;
    float g = texture(tex0,uv).g;
    float b = texture(tex0,uv - tornado(shift)*0.01).b;
    
    vec3 col = vec3(r,g,b);
    col *= 1 + ussin(u_time)*0.1;
    
    outputColor = vec4(col, 1.);

}
