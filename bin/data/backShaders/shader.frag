#version 400

#pragma include "noise.glsl"
#pragma include "util.glsl"

#define PI 3.14159265358979


uniform sampler2D gradTex;

in vec2 varyingtexcoord;
out vec4 outputColor;

uniform vec2 u_resolution;
uniform float u_time;
uniform vec4 globalColor;


float usnoise(vec4 a) {
    return (snoise( a ) + 1.) * 0.5;
}

float usnoise(vec3 a) {
    return (snoise( a ) + 1.) * 0.5;
}


float usnoise(vec2 a) {
    return (snoise( a ) + 1.) * 0.5;
}

struct patternSet {
    float pct;
    vec3 col;
};

patternSet getPattern(vec2 _uv, float _rseed) {
    vec2 uv = _uv;
    
    float aspect = u_resolution.x/u_resolution.y;
    uv.x *= aspect;
    
    uv -= vec2(aspect*0.5 , 0.5);
    uv = rotate2d(PI*0.25) * uv;
    uv += vec2(aspect*0.5 , 0.5);;
    
    uv += snoise(vec3(uv*1.1+_rseed*.6, u_time*0.1+_rseed*3.)) * 0.1;
    uv += u_time * 0.2;
    uv.x *= 10.;
    float pattern = fract(uv.x);
    pattern = step(0.7 + snoise(vec2(floor(uv.x)+_rseed,floor(uv.x)+_rseed*2.))*0.2, pattern);
    
    vec3 patCol = texture(gradTex, vec2(rand(floor(uv.x)+_rseed), _rseed*0.5)).rgb;
    
    patternSet pSet;
    pSet.pct = pattern;
    pSet.col = patCol;
    
    return pSet;
}


void main (void){
    
    vec2 uv =  varyingtexcoord.xy;
    vec3 col = vec3(0);//texture(gradTex, vec2(fract(u_time*0.1), 0.5)).rgb; //vec3(1);
    
    for (int i=0; i<3; i++) {
        patternSet pSet = getPattern(uv, 40.*float(i));
        col = mix(col, pSet.col, pSet.pct);
    }
    
    if (col.r < 0.01) {
        discard;
    }
    
    outputColor = vec4(col, 1.) * globalColor;

}
