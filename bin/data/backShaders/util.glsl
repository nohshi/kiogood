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
