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
	void setup(); //初期化
	void update(); //毎フレーム呼ばれるやつ
	void draw(); //毎フレーム呼ばれるやつ、メインディスプレイへの描画用
	void exit(); //終了時に呼ばれるやつ
	void audioIn(ofSoundBuffer & input); //音の処理

	//以下マウス、キーイベント関数
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

	//-------------gui関係
	ofxPanel gui;
	ofxFloatSlider g_screenAlph, g_liveCodingAlph, g_effectsVal;
	ofxToggle g_bPostEffects;
	ofxIntSlider peId;

	//-------------displayAppに送る用のfbo
	ofFbo displayFbo;

	//---------------音
	vector <float> left; //左チャンネル
	vector <float> right; //右チャンネル
	float smoothedVol; //平滑化した音量
	float vol; //現フレームで受け取った音量
	float scaledVol; //smoothedVolを調整したもの
	ofSoundStream soundStream; //音用のオブジェクト
	ofxFloatSlider g_amp; //音量調整用のパラメータ

	//-------------Assets コンテンツ
	WaveBorder wBorder; //波エフェクト
	NikoMetaball nMeta; //メタボール
	LiveCoder liveCoder; //ライブコーディングエフェクト
	BallEmitter ballEmitter; //パーティクル

	//----------post effects
	PostEffects pe;

};
