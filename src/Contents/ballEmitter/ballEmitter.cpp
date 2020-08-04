
#include "ballEmitter.hpp"

BallEmitter::BallEmitter() {
    balls.resize(300);
    timer = Timer(0.02);
    ofAddListener(timer.tick, this, &BallEmitter::tick);
    brenderer.loadTexture("nikonikoman2-1.png");
    ofImage img;
    img.load("gradient/gradient4.png");
    gradient.loadFromImage(img, 3);
}

void BallEmitter::setEmitPosition(const glm::vec3 & _p) {
    emitPos = _p;
}

void BallEmitter::update() {
    timer.update();
    
    for (auto & b : balls) {
        b.update();
    }
}

void BallEmitter::debugDraw(){
    for (const auto & b : balls) {
        b.debugDraw();
    }
}

void BallEmitter::draw(){
    //brenderer.add(
    for (const auto & b : balls) {
        brenderer.addPoint(b.p, b.col, b.r);
    }
    brenderer.draw();
    brenderer.clear();
}

//--------------------------------------------------------------
void BallEmitter::tick(int & taskNum) {
    //cout << taskNum << endl;
    if (ofGetKeyPressed(OF_KEY_SHIFT)) {
        for (auto & b : balls) {
            if (!b.bActive) {
                glm::vec3 p = glm::vec3(emitPos);
                float l = ofRandomf() * 40;
                p.x += cos(ofRandom(PI*2)) * l;
                p.y += sin(ofRandom(PI*2)) * l;
                ofFloatColor col = gradient.getColorAtPercent(ofRandom(1));
                Ball b_new(p, 90 * (0.2 + ofRandom(1)), 10. * (0.2 + ofRandom(1)), col);
                b.activate(b_new);
                break;
            }
        }
    }
}
