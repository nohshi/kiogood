
#pragma once

#include "ofMain.h"
#include "pointsRenderer.hpp"

class BrushRenderer : public PointsRenderer {
public:
    
    BrushRenderer();
    void draw();
    ofImage brushTex;
    
    void loadTexture(string _filepath) {
        ofDisableArbTex(); //テクスチャ読み込み時に呼ぶ
        brushTex.load(_filepath);
        ofEnableArbTex();
    }
    
};
