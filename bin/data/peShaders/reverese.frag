#version 410

#define PI 3.14159265358979


uniform sampler2D tex0; ////this is "draw in the shader"

in vec2 varyingtexcoord;
out vec4 outputColor;

uniform vec2 u_resolution;
uniform float u_time;
uniform float u_val;



void main (void){
    
    vec2 uv =  varyingtexcoord.xy;
    
    
    
    vec3 t = texture(tex0,uv).rgb;
    vec3 col = vec3(0);
    col = 1.-t.rgb;
    
    outputColor = vec4(col, 1.);

}
