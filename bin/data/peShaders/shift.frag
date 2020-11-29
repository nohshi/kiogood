#version 400

#pragma include "util.glsl"

#define PI 3.14159265358979


uniform sampler2D tex0; ////this is "draw in the shader"

in vec2 varyingtexcoord;
out vec4 outputColor;

uniform vec2 u_resolution;
uniform float u_time;
uniform float u_val1;
uniform float u_rand;


void main (void){
    
    vec2 uv =  varyingtexcoord.xy;
    float shiftId = floor(uv.y*10);
    
    uv.x += rand(shiftId*13. + u_time*0.1) * 0.1 * u_val1;
    
    vec3 t = texture(tex0,uv).rgb;
    vec3 col = vec3(0);
    col = t;
    
    outputColor = vec4(col, 1.);

}
