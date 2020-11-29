#include "ofMain.h"
#include "ofApp.h"
#include "displayApp.hpp"

//========================================================================
int main() {
	ofGLFWWindowSettings settings;
	settings.setGLVersion(4, 0);

	//�O�����j�^�[�ɕ\�����邽�߂̃E�B���h�E
	settings.setSize(1080, 720);
	settings.setPosition(ofVec2f(100, 100));
	shared_ptr<ofAppBaseWindow> displayWindow = ofCreateWindow(settings);

	//GUI�Ȃǂ�\�����郁�C���E�B���h�E
	settings.setSize(1080, 360);
	settings.setPosition(ofVec2f(600, 300));
	settings.shareContextWith = displayWindow;
	settings.resizable = false;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	//���҂̃I�u�W�F�N�g�����L���邽�߂̃|�C���^
	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<DisplayApp> displayApp(new DisplayApp);
	displayApp->mainObj = mainApp;

	//���[�v�X�^�[�g
	ofRunApp(displayWindow, displayApp);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();
}
