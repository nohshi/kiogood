#version 400

#define PI 3.14159265358979


uniform sampler2D tex0; ////this is "draw in the shader"

in vec2 varyingtexcoord;
out vec4 outputColor;

uniform vec2 u_resolution;
uniform float u_time;




void main (void){
    
    vec2 uv =  varyingtexcoord.xy;
    
    
    
    vec3 col = vec3(uv.x, uv.y, 0.);
    
    outputColor = vec4(col, 1.);

}
