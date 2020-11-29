//
//  brushRenderer.cpp
//  naruchan_test
//
//  Created by 藤田　恭輔 on 2019/06/04.
//

#include "brushRenderer.hpp"


BrushRenderer::BrushRenderer(){
    // we need to disable ARB textures in order to use normalized texcoords
    shader.load("brushShader/shader.vert","brushShader/shader.frag","brushShader/shader.geom");
}

void BrushRenderer::draw(){
    if(doShader) {
        shader.begin();
        ofEnableAlphaBlending();
        brushTex.getTexture().bind();
    }
    
    //-------------------------------------------二回目以降はupdateAttributeDataを実行した方がいい気がする
    if(!bSetCustomAttributes) {
        vboMesh.getVbo().setAttributeData(shader.getAttributeLocation("pointsize"), &pointsSize[0], 1, pointsSize.size(), GL_DYNAMIC_DRAW, sizeof(float));
        bSetCustomAttributes = true;
    }else {
        vboMesh.getVbo().updateAttributeData(shader.getAttributeLocation("pointsize"), &pointsSize[0], pointsSize.size());
    }
    
    vboMesh.draw();
    
    if(doShader) {
        brushTex.getTexture().unbind();
        shader.end();
    }
    
}
