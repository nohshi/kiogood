#include "ofMain.h"
#include "ofApp.h"
#include "displayApp.hpp"

//========================================================================
int main() {
	ofGLFWWindowSettings settings;
	settings.setGLVersion(4, 0);

	//外部モニターに表示するためのウィンドウ
	settings.setSize(1080, 720);
	settings.setPosition(ofVec2f(100, 100));
	shared_ptr<ofAppBaseWindow> displayWindow = ofCreateWindow(settings);

	//GUIなどを表示するメインウィンドウ
	settings.setSize(1080, 360);
	settings.setPosition(ofVec2f(600, 300));
	settings.shareContextWith = displayWindow;
	settings.resizable = false;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	//両者のオブジェクトを共有するためのポインタ
	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<DisplayApp> displayApp(new DisplayApp);
	displayApp->mainObj = mainApp;

	//ループスタート
	ofRunApp(displayWindow, displayApp);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();
}
