//
//  waveBorder.hpp
//  kiogood
//
//  Created by 藤田　恭輔 on 2019/12/08.
//

#ifndef waveBorder_hpp
#define waveBorder_hpp

#include "ofMain.h"
#include "ofxGui.h"

class WaveBorder {
public:
    
    ofShader shader;
    ofPlanePrimitive plane;
    ofTexture gradTex;
    float eTime = 0;
    ofxPanel gui;
    ofxToggle g_bDraw;
    ofxFloatSlider g_speed, g_alph;
    
    WaveBorder(const float &_w = 1080, const float &_h = 720) {
        plane.set(_w, _h, 2, 2);
        plane.setPosition({_w/2, _h/2, 0.0f});
        ofDisableArbTex();
        ofLoadImage(gradTex, "gradient/gradient3.png");
        ofEnableArbTex();
        shader.load("backShaders/shader.vert", "backShaders/shader.frag");
        
        gui.setup("waveBorder");
        gui.add(g_bDraw.setup("bDraw", true));
        gui.add(g_alph.setup("alph", 0, 0, 255));
        gui.add(g_speed.setup("speed", 1, 0, 5));
    }
    
    
    void draw() {
        if(!g_bDraw) return;
        
        eTime += ofGetLastFrameTime() * g_speed;
        
        ofPushStyle();
        ofSetColor(255, g_alph);
        
        shader.begin();
        shader.setUniformTexture("gradTex", gradTex, 0);
        shader.setUniform2f("u_resolution", plane.getWidth(), plane.getHeight());
        shader.setUniform1f("u_time", eTime);
        plane.draw();
        shader.end();
        
        ofPopStyle();
    }
    
    void drawGui() {
        gui.draw();
    }
    
};

#endif /* waveBorder_hpp */
