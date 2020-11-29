#version 400

#define PI 3.14159265358979


uniform sampler2D nikoTex;
uniform sampler2D gradTex;

in vec2 varyingtexcoord;
out vec4 outputColor;

uniform vec2 u_resolution;
uniform float u_nikoTime;
uniform float u_slideTime;
uniform float u_scale;
uniform float u_val;

uniform vec4 globalColor;



mat2 rotate2d(float _angle){
    return mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle));
}


float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
                 43758.5453123);
}

vec2 random2( vec2 p ) {
    return fract(sin(vec2(dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3))))*43758.5453);
}

void main() {
    
    /*
    vec2 st = varyingtexcoord.xy;
    st.x *= u_resolution.x/u_resolution.y;
    */
    vec2 st = varyingtexcoord.xy;
    /*
    vec2 ast = st;
    st -= 0.5;
    st.x = cos(ast.y*PI*2);
    st.y = sin(ast.x*PI*2);
    st += 0.5;
     */
    st.x *= u_resolution.x/u_resolution.y;
    
    
    // Scale
    st *= u_scale;
    st += u_slideTime*0.2;
    
    // Tile the space
    vec2 i_st = floor(st);
    vec2 f_st = fract(st);
    
    float col_m_dist = 6.;  // minimun distance
    vec2 m_point = vec2(-1,-1);
    float m_dist = 0.4;  // minimun distance
    vec2 m_diff = vec2(1.);
    float meta_dist = m_dist;  // minimun distance
    for (int y= -1; y <= 1; y++) {
        for (int x= -1; x <= 1; x++) {
            // Neighbor place in the grid
            vec2 neighbor = vec2(float(x),float(y));
            
            // Random position from current + neighbor place in the grid
            vec2 point = random2(i_st + neighbor);
            vec2 p2 = point;
            
            
            // Animate the point
            point = 0.5 + 0.5*sin(u_nikoTime*1.3 + 6.2831*point);
            
            // Vector between the pixel and the point
            vec2 diff = neighbor + point - f_st;
            
            // Distance to the point
            float dist = length(diff);
            
            // Keep the closer distance
            if(m_dist>dist){
                m_dist = dist;
                m_diff = diff;
            }
            
            meta_dist = min(meta_dist, meta_dist*dist);
    
            if(col_m_dist>dist){
                col_m_dist = dist;
                m_point = p2;
            }
        }
    }
    m_diff = (m_diff+1.)*0.5;
    m_diff = 1.-m_diff;
    
    vec2 ptId = floor(m_point * 100.);
    
    float amp = meta_dist*90.;
    
    
    vec4 color = vec4(0,0,0,.0);
    color += 1.-step(0.060, meta_dist);
    //if (color.r<0.01) discard;
    
    vec3 nCol;
    float colSeed = random(ptId + vec2(0, 10));
    colSeed = fract(colSeed+u_nikoTime);
    nCol = texture(gradTex, vec2(colSeed,0.5)).rgb;
    //nCol *= 0.1;
    /*
    nCol.r = random(ptId + vec2(0, 10));
    nCol.g = random(ptId + vec2(0,700));
    nCol.b = random(ptId + vec2(300,0));
    */
    //color.rgb -= backCol;
    float faceRad = min( pow((1.-col_m_dist),6.), 0.2 ) * 4.0;
    color.rgb *= 1.-(1.-nCol) * faceRad;// * (1.-step(0.5,m_point.r));
    //color.rgb -= faceRad * backCol;
    float alph = 1.-step(0.062, meta_dist);
    
    //nikoniko-man texture
    amp = pow(amp, u_val);
    amp *= 3.;
    m_diff -= 0.5;
    m_diff = rotate2d(random(ptId)*PI*2 + u_nikoTime) * m_diff;
    m_diff *= amp;
    m_diff += 0.5;
    m_diff.y = 1.-m_diff.y;
    color.rgb *= texture(nikoTex, m_diff).rgb;
    
    //color *= vec3(1., 0.4, 1.);
    outputColor = vec4(color.rgb, alph) * globalColor;
}







