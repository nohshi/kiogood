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

// Author @patriciogv - 2015
// http://patriciogonzalezvivo.com
float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.5);
    return 1.-smoothstep(_radius-(_radius*1.),
                         _radius+(_radius*1.),
                         dot(dist,dist)*4.0);
}

float ussin(float _x){
    return (sin(_x) + 1) * 0.5;
}


void main (void){
    
    vec2 uv =  varyingtexcoord.xy;
    
    float size = 100.;
    vec2 st = uv;
    st.x *= u_resolution.x/u_resolution.y;
    float cir = circle(fract(st*size), 0.5) * 2.;
    
    vec3 t = texture(tex0,uv).rgb;
    vec3 col = vec3(0);
    col = t * cir;
    
    col *= 1 + ussin(u_time)*0.2;
    
    outputColor = vec4(col, 1.);

}
