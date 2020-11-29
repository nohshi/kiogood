#version 400

#define PI 3.14159265358979


uniform sampler2D tex0; ////this is "draw in the shader"
uniform sampler2D tex1;

in vec2 varyingtexcoord;
out vec4 outputColor;

uniform vec2 u_resolution;
uniform float u_time;
uniform float u_val0;

//input 0<x<1, putput 0<y<1
/*
float shift(float _x) {
    _x -= 1;
    return pow(min(cos(PI*_x/2.),  1.-abs(_x)), 2.5);
}
*/

vec2 tornado(float _r) {
    float t = u_time * 5.1;
    vec2 p;
    p.x = cos(t) * _r;
    p.y = sin(t) * _r;
    return p;
}

void main (void){
    
    vec2 uv =  varyingtexcoord.xy;
    
    float limit = 0.0300;
    float shift = min(u_val0, limit);
    
    float r = texture(tex1,uv + tornado(shift)).r;
    float g = texture(tex1,uv).g;
    float b = texture(tex1,uv - tornado(shift)).b;
    
    vec3 col = vec3(r, g, b);
    
    outputColor = vec4(col, 1.);

}