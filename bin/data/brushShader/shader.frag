#version 400


uniform vec4 globalColor;
uniform sampler2D tex;

in vec4 gsColor;
in vec3 gsNormal;
in vec2 gsTexCoord;

out vec4 outputColor;



 
void main(){
    
    vec2 uv = gsTexCoord;
    vec4 color = texture(tex, uv);
    color.rgb = gsColor.rgb * color.rgb;
    
    outputColor = color;
    
    
}
