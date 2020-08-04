#version 410


uniform vec4 globalColor;


in vec4 gsColor;
in vec3 gsNormal;
in vec2 gsTexCoord;

out vec4 outputColor;


// Author @patriciogv - 2015
// http://patriciogonzalezvivo.com
float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.5);
    return 1.-smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(dist,dist)*4.0);
}
 
void main(){
    
    vec2 uv = gsTexCoord;
    float pct = circle(uv,.9);
    vec4 color;
    color.rgb = gsColor.rgb * pct;
    color.a = pct;
    
    outputColor = color;
    
    
}
