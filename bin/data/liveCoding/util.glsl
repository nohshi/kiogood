#define PI 3.14159265358979


mat3 rotate3d(float _radian, vec3 _axis){
    float s = sin(_radian);
    float c = cos(_radian);
    vec3 a = normalize(_axis);
    
    return mat3( c+pow(a.x,2.)*(1-c), a.x*a.y*(1-c)-a.z*s, a.x*a.z*(1-c)+a.y*s,
                 a.y*a.x*(1-c)+a.z*s, c+pow(a.y,2.)*(1-c), a.y*a.z*(1-c)-a.x*s,
                 a.z*a.x*(1-c)-a.y*s, a.z*a.y*(1-c)+a.x*s, c+pow(a.z,2.)*(1-c)  );
}


float rand(float x){
    return fract(sin(x)*100000.0);
}


float rand (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
                 43758.5453123);
}

mat2 rotate2d(float _angle){
    return mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle));
}


vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}