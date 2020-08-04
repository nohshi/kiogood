//
//  liveCording.hpp
//  kiogood
//
//  Created by 藤田　恭輔 on 2019/12/08.
//

#ifndef liveCording_hpp
#define liveCording_hpp

#include "ofMain.h"
#include "ofxGui.h"

class LiveCoder {
public:
    
    ofShader shader;
    ofPlanePrimitive plane;
    float val0 = 0;
    float val1 = 0;
    ofxPanel gui;
    ofxFloatSlider g_alph;
    ofParameter<string> g_shaderName;
    
    LiveCoder(const float &_w = 1080, const float &_h = 720) {
        plane.set(_w, _h, 2, 2);
        plane.setPosition({_w/2, _h/2, 0.0f});
        
        shader.load("liveCoding/shader.vert", "liveCoding/shader.frag");
        
        gui.setup("livecoder");
        gui.add(g_shaderName.set("shaderName", "shader"));
    }
    
    void draw() {
        ofPushStyle();
        
        shader.begin();
        //shader.setUniform2f("u_mouse", ofGetMouseX(), ofGetMouseY());
        shader.setUniform2f("u_resolution", plane.getWidth(), plane.getHeight());
        shader.setUniform1f("u_time", ofGetElapsedTimef());
        shader.setUniform1f("u_val0", val0);
        shader.setUniform1f("u_val1", val1);
        plane.draw();
        shader.end();
        
        ofPopStyle();
    }
    
    
    void draw(const float &_x, const float &_y, const float &_w, const float &_h) {
        ofPushMatrix();
        ofTranslate(_x,_y);
        ofScale(_w/plane.getWidth(), _h/plane.getHeight());
        this->draw();
        ofPopMatrix();
    }
    
    void drawGui() {
        gui.draw();
    }
    
    
    void reload() {
        shader.load("liveCoding/shader.vert", "liveCoding/" + ofToString(g_shaderName) + ".frag");
    }
    
};

#endif /* liveCording_hpp */
