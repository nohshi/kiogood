#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "nikoMetaball.hpp"
#include "waveBorder.hpp"
#include "liveCoder.hpp"
#include "postEffects.hpp"
#include "ballEmitter.hpp"

class ofApp : public ofBaseApp {

public:
	void setup(); //������
	void update(); //���t���[���Ă΂����
	void draw(); //���t���[���Ă΂���A���C���f�B�X�v���C�ւ̕`��p
	void exit(); //�I�����ɌĂ΂����
	void audioIn(ofSoundBuffer & input); //���̏���

	//�ȉ��}�E�X�A�L�[�C�x���g�֐�
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	//-------------gui�֌W
	ofxPanel gui;
	ofxFloatSlider g_screenAlph, g_liveCodingAlph, g_effectsVal;
	ofxToggle g_bPostEffects;
	ofxIntSlider peId;

	//-------------displayApp�ɑ���p��fbo
	ofFbo displayFbo;

	//---------------��
	vector <float> left; //���`�����l��
	vector <float> right; //�E�`�����l��
	float smoothedVol; //��������������
	float vol; //���t���[���Ŏ󂯎��������
	float scaledVol; //smoothedVol�𒲐���������
	ofSoundStream soundStream; //���p�̃I�u�W�F�N�g
	ofxFloatSlider g_amp; //���ʒ����p�̃p�����[�^

	//-------------Assets �R���e���c
	WaveBorder wBorder; //�g�G�t�F�N�g
	NikoMetaball nMeta; //���^�{�[��
	LiveCoder liveCoder; //���C�u�R�[�f�B���O�G�t�F�N�g
	BallEmitter ballEmitter; //�p�[�e�B�N��

	//----------post effects
	PostEffects pe;

};
