//
//  nikoMetaball.hpp
//  kiogood
//
//  Created by 藤田　恭輔 on 2019/12/08.
//

#ifndef nikoMetaball_hpp
#define nikoMetaball_hpp

#include "ofMain.h"
#include "ofxGui.h"

class NikoMetaball {
public:
    
    ofShader shader;
    ofPlanePrimitive plane;
    ofTexture nikoTex, gradTex, pikaTex;
    float nikoTime = 0;
    float slideTime = 0;
    ofxPanel gui;
    ofxToggle g_bDraw;
    ofxFloatSlider g_nikoSpeed, g_slideSpeed, g_alph, g_scale;
    bool bPika = false;
    
    NikoMetaball(const float &_w = 1080, const float &_h = 720) {
        plane.set(_w, _h, 2, 2);
        plane.setPosition({_w/2, _h/2, 0.0f});
        ofDisableArbTex();
        ofLoadImage(nikoTex, "nikonikoman-eye.png");
        ofLoadImage(gradTex, "gradient/gradient1.png");
        ofLoadImage(pikaTex, "pt56mDny_400x400.jpg");
        ofEnableArbTex();
        shader.load("shaders/shader.vert", "shaders/metaBall.frag");
        
        gui.setup("nikoMetaball");
        gui.add(g_bDraw.setup("bDraw", true));
        gui.add(g_alph.setup("alph", 0, 0, 255));
        gui.add(g_nikoSpeed.setup("nikoSpeed", 1, 0, 5));
        gui.add(g_slideSpeed.setup("slideSpeed", 1, 0, 10));
        gui.add(g_scale.setup("scale", 3, 1, 20));
    }
    
    
    void draw() {
        if(!g_bDraw) return;
        
        nikoTime += ofGetLastFrameTime() * g_nikoSpeed;
        slideTime += ofGetLastFrameTime() * g_slideSpeed;
        
        ofPushStyle();
        ofSetColor(255, g_alph);
        
        shader.begin();
        if (!bPika) {
            shader.setUniformTexture("nikoTex", nikoTex, 0);
            shader.setUniform1f("u_val", 0.7);
        }else{
            shader.setUniformTexture("nikoTex", pikaTex, 0);
            shader.setUniform1f("u_val", 0.05);
        }
        shader.setUniformTexture("gradTex", gradTex, 1);
        shader.setUniform2f("u_resolution", plane.getWidth(), plane.getHeight());
        shader.setUniform1f("u_nikoTime", nikoTime);
        shader.setUniform1f("u_slideTime", slideTime);
        shader.setUniform1f("u_scale", g_scale);
        plane.draw();
        shader.end();
        
        ofPopStyle();
    }
    
    void drawGui() {
        gui.draw();
    }
    
};

#endif /* nikoMetaball_hpp */
