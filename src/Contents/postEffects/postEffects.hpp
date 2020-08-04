//
//  postEffects.hpp
//  kiogood
//
//  Created by 藤田　恭輔 on 2019/12/08.
//

#ifndef postEffects_hpp
#define postEffects_hpp

#include "ofMain.h"

class PostEffects {
public:
    ofFbo *fbo;
    vector<ofShader> shaders;
    float u_val0 = 0;
    float u_val1 = 0;
    
    PostEffects() { }
    
    PostEffects(ofFbo* _fbo) {
        fbo = _fbo;
    }
    
    void setFbo(ofFbo* _fbo) {
        fbo = _fbo;
    }
    
    void load(string _vShader, string _fShader) {
        shaders.emplace_back();
        shaders.back().load(_vShader, _fShader);
    }
    
    void setUniformVal0(const float & _val) {
        u_val0 = _val;
    }
    
    void setUniformVal1(const float & _val) {
        u_val1 = _val;
    }
    
    void draw(const int & _shaderId) {
        
        int index = _shaderId;
        if (index >= shaders.size() || index < 0){
            cout << "There is no shader having this id." << endl;
            return;
        }
        ofPushStyle();
        
        ofSetColor(255);
        shaders[index].begin();
        shaders[index].setUniform2f("u_resolution", fbo->getWidth(), fbo->getHeight());
        shaders[index].setUniform1f("u_time", ofGetElapsedTimef());
        shaders[index].setUniform1f("u_val0", u_val0);
        shaders[index].setUniform1f("u_val1", u_val1);
        shaders[index].setUniform1f("u_rand", ofRandom(1));
        fbo->draw(0,0);
        shaders[index].end();
        
        ofPopStyle();
    }
    
    
};

#endif /* postEffects_hpp */
