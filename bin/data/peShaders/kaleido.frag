#version 410

#pragma include "util.glsl"

#define PI 3.14159265358979
#define TWO_PI (2*PI)

uniform sampler2D tex0; ////this is "draw in the shader"

in vec2 varyingtexcoord;
out vec4 outputColor;

uniform vec2 u_resolution;
uniform float u_time;
uniform float u_val1;
uniform float u_rand;


void main (void){
    
    vec2 uv =  varyingtexcoord.xy;
    float aspect = u_resolution.x/u_resolution.y;
    uv.x *= aspect;
    vec2 center = vec2(0.5 * aspect ,0.5);
    vec2 v = uv - center;
    v = rotate2d(u_time*0.2) * v;
    float r = length( v );
    float a = atan( v.y, v.x );
    
    float A = TWO_PI / float(6.);
    a = mod( a, A );
    if ( a > A/2.0 ) a = A - a;
    a -= u_time*0.2;
    
    vec2 u = vec2( cos(a), sin(a) ) * r;
    u += center;
    
    vec3 col = texture(tex0 ,u).rgb;
    
    outputColor = vec4(col, 1.);

}
