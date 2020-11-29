#version 400

#define PI 3.14159265358979


uniform sampler2D tex0; ////this is "draw in the shader"

in vec2 varyingtexcoord;
out vec4 outputColor;

uniform vec2 u_resolution;
uniform float u_time;
uniform float u_val;



void main (void){
    
    vec2 uv =  varyingtexcoord.xy;
    
    vec2 shift = vec2(0.02, 0);
    vec3 t;
    t.r = texture(tex0,uv + shift).r;
    t.g = texture(tex0,uv).g;
    t.b = texture(tex0,uv - shift).b;
    vec3 col = vec3(0);
    col += (t.r + t.g + t.b)/3.;
    
    
    
    outputColor = vec4(col, 1.);

}
