
#ifndef ballEmitter_hpp
#define ballEmitter_hpp

#include "ofMain.h"
#include "timer.hpp"
#include "brushRenderer.hpp"
#include "ofxColorGradient.h"

//BallEmitterで使うパーティクルの中身
class Ball {
public:
    glm::vec3 p = glm::vec3(0);
    glm::vec3 v = glm::vec3(0); //初速度
    glm::vec3 g = glm::vec3(-0.05*1080/720., 0.05, 0); //重力加速度
    
    float lifetime = 10;
    float age = 0;
    float r = 10;
    float r_max;
    ofFloatColor col = ofFloatColor(1);
    bool bActive = false;
    
    Ball() {
        r_max = r;
    }
    
    Ball( const glm::vec3 &_p, const float &_r, const float &_lifetime,
         const ofFloatColor &_col = ofFloatColor(1)) {
        p = _p;
        r = _r;
        r_max = r;
        lifetime = _lifetime;
        col = _col;
    }
    
    bool isActive() {
        bool jumyo = age < lifetime ? true : false;
        bool jogai = true;
        if (p.x<0 || p.x>1080 || p.y<0 || p.y>720) jogai = false;
        
        return jumyo && jogai;
    }
    
    void activate(const Ball &_b) {
        *this = _b;
        bActive = true;
    }
    
    void update() {
        v += g;
        p += v;
        
        if (this->isActive()) {
            age += ofGetLastFrameTime();
            r = myWave(0.5+age/lifetime*0.5) * r_max;
        }else {
            bActive = false;
            r = 0;
        }
    }
    
    void debugDraw() const{
        ofPushStyle();
        ofSetColor(col);
        ofDrawCircle(p, r);
        ofPopStyle();
    }
    
    float & myWave(const float &_x) const { //_x=0~1
        float x = (_x - 0.5) * 2;
        float y;
        if (x < 0) {
            y = 1 - pow( abs(sin(PI * x/2)), 2.5 );
        }else{
            y = pow( cos(PI * x/2), 2 );
        }
        return y;
    }
};

//マウスを押したところにパーティクルを放つクラス
class BallEmitter {
public:
    BallEmitter();
    
    void tick(int & taskNum); //一定時間間隔で実行
    void setEmitPosition(const glm::vec3 & _p);
    void update(); //座標更新
    void debugDraw();
    void draw();
    
    Timer timer;
    
    vector<Ball> balls;
    BrushRenderer brenderer; //ポイントスプライトの簡易レンダラー
    
    glm::vec3 emitPos = glm::vec3(-10000);
    
    ofxColorGradient<ofFloatColor> gradient;
};

#endif /* ballEmitter_hpp */
