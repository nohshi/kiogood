

#include "displayApp.hpp"

void DisplayApp::setup(){
    ofSetBackgroundColor(0);
    
}

void DisplayApp::update(){
    
}

void DisplayApp::draw(){
    ofSetColor(255, mainObj->g_screenAlph);
    mainObj->displayFbo.draw(0,0, ofGetWidth(), ofGetHeight());
   
}

//--------------------------------------------------------------
void DisplayApp::exit(){
   
}

//--------------------------------------------------------------
void DisplayApp::keyPressed(int key){
    
    if (key == 'f') {
        ofToggleFullscreen();
    }
    /*
    if (key == 's') {
        ofSetWindowShape(mainObj->WIDTH, mainObj->HEIGHT);
    }*/
    
}

//--------------------------------------------------------------
void DisplayApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void DisplayApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void DisplayApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void DisplayApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void DisplayApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void DisplayApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void DisplayApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void DisplayApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void DisplayApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void DisplayApp::dragEvent(ofDragInfo dragInfo){
    
}



