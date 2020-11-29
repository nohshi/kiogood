#include "ofApp.h"

//--------------------------------------------------------------初期化
void ofApp::setup() {
	//ofSetLogLevel(OF_LOG_VERBOSE);

	ofSetVerticalSync(false);
	ofSetFrameRate(60);

	//----------------------------GUI初期設定
	gui.setup();
	gui.setName("main");
	gui.add(g_screenAlph.setup("screenAlph", 255, 0, 255));
	gui.add(g_liveCodingAlph.setup("liveCodingAlph", 0, 0, 255));
	gui.add(g_amp.setup("amp", 0, 0, 1));
	gui.add(g_bPostEffects.setup("bPostEffects", false));
	gui.add(peId.setup("PostEffectsID", 0, 0, 9));
	gui.add(g_effectsVal.setup("effectsVal", 0, 0, 1));

	gui.setPosition(10, 30);

	//----------------------------コンテンツの初期設定
	wBorder.gui.setPosition(220, 30);
	nMeta.gui.setPosition(440, 30);
	liveCoder.gui.setPosition(20, 300);

	//----------------------------FBO
	ofDisableArbTex();
	ofFbo::Settings setting;
	setting.width = 1080;
	setting.height = 720;
	setting.internalformat = GL_RGB32F;
	setting.numSamples = 0;
	setting.wrapModeVertical = GL_REPEAT;
	setting.wrapModeHorizontal = GL_REPEAT;
	setting.textureTarget = GL_TEXTURE_2D;
	setting.minFilter = GL_LINEAR;
	setting.maxFilter = GL_LINEAR;
	displayFbo.allocate(setting);
	ofEnableArbTex();

	//-----------------------------ポストフェクト初期設定/シェーダ読み込み
	pe.setFbo(&displayFbo);
	pe.load("peShaders/shader.vert", "peShaders/conversion.frag");
	pe.load("peShaders/shader.vert", "peShaders/mono.frag");
	pe.load("peShaders/shader.vert", "peShaders/mosaic.frag");
	pe.load("peShaders/shader.vert", "peShaders/dots.frag");
	pe.load("peShaders/shader.vert", "peShaders/disp.frag");
	pe.load("peShaders/shader.vert", "peShaders/reverese.frag");
	pe.load("peShaders/shader.vert", "peShaders/dispReverse.frag");
	pe.load("peShaders/shader.vert", "peShaders/shift.frag");
	pe.load("peShaders/shader.vert", "peShaders/shiftConversion.frag");
	pe.load("peShaders/shader.vert", "peShaders/kaleido.frag");


	//---------------------------------------音入力初期設定
	//soundStream.printDeviceList();
	int bufferSize = 512;

	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);

	smoothedVol = 0.0;
	scaledVol = 0.0;

	ofSoundStreamSettings settings;
	auto devices = soundStream.getMatchingDevices("default");
	if (!devices.empty()) {
		settings.setInDevice(devices[0]);
	}

	settings.setInListener(this);
	settings.sampleRate = 44100;
	settings.numOutputChannels = 0;
	settings.numInputChannels = 2;
	settings.bufferSize = bufferSize;
	soundStream.setup(settings);
}

//--------------------------------------------------------------毎フレーム呼ばれるやつ
void ofApp::update() {
	//lets scale the vol up to a 0-1 range
	//音量の調整とliveCoderへ音パラメータを渡す
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
	liveCoder.val0 = g_amp * vol;
	liveCoder.val1 = g_amp * scaledVol;

	//displayFbo.begin()/end()に挟まれたdraw()関数で
	//コンテンツをdisplayFboに書き込む
	displayFbo.begin();
	//前フレームの内容をクリア
	ofSetColor(0, 255);
	ofDrawRectangle(0, 0, displayFbo.getWidth(), displayFbo.getHeight());

	//以下コンテンツの書き込み
	ofSetColor(255, 255);
	wBorder.draw();
	nMeta.draw();
	ballEmitter.setEmitPosition(glm::vec3(displayFbo.getWidth() / 540 * ofGetMouseX(),
		displayFbo.getHeight() / 360 * ofGetMouseY(), 0));
	ballEmitter.update();
	ballEmitter.draw();

	ofSetColor(255, g_liveCodingAlph);
	liveCoder.draw();

	displayFbo.end();

	//ポストエフェクトをかける
	if (g_bPostEffects) {
		displayFbo.begin();
		pe.setUniformVal0(g_amp*vol);
		pe.setUniformVal1(g_effectsVal);
		pe.draw(peId);
		displayFbo.end();
	}
}

//--------------------------------------------------------------毎フレーム呼ばれるやつ
//ここで呼ばれたdraw()関数でメインディスプレイへ描きこむ
void ofApp::draw() {
	ofSetColor(255);
	displayFbo.draw(0, 0, 540, 360); //今の画面の状態をプレビュー
	liveCoder.draw(540, 0, 540, 360); //ライブコーディング用のシェーダプレビュー

	//-----------------GUIの描画
	ofSetColor(255);
	gui.draw();
	wBorder.drawGui();
	nMeta.drawGui();
	liveCoder.drawGui();
	ofSetColor(255 - g_screenAlph);
	ofDrawBitmapString("fps : " + ofToString(ofGetFrameRate()), 700, 30);
	ofDrawBitmapString("volume : " + ofToString(vol), 700, 100);
	int sum = 0;
	for (const auto & pt : ballEmitter.balls) {
		if (pt.bActive) {
			sum++;
		}
	}
	ofDrawBitmapString("ballNum : " + ofToString(sum), 700, 200);
}

//--------------------------------------------------------------終了時に呼ばれるやつ
void ofApp::exit() {
	soundStream.stop(); //音入力用のオブジェクトをストップする
}

//--------------------------------------------------------------//音の処理
//公式のものをかなりコピペした。512バンドのスペクトラムを毎フレーム提供する
void ofApp::audioIn(ofSoundBuffer & input) {

	float curVol = 0.0;

	// samples are "interleaved"
	int numCounted = 0;

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (size_t i = 0; i < input.getNumFrames(); i++) {
		left[i] = input[i * 2] * 0.5;
		right[i] = input[i * 2 + 1] * 0.5;

		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted += 2;
	}//cout << input.getNumFrames() << endl;

	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;

	// this is how we get the root of rms :)
	curVol = sqrt(curVol);

	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;

	vol = curVol;
}

//以下マウス、キーイベント関数
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'f') ofToggleFullscreen(); //フルスクリーン化
	if (key == ' ') liveCoder.reload(); //ライブコーディングのシェーダをリロード
	if (key == 'p') nMeta.bPika = !nMeta.bPika; //メタボールのテクスチャ変更

	//ポストエフェクト 切り替え
	if (key == '0') peId = 0;
	if (key == '1') peId = 1;
	if (key == '2') peId = 2;
	if (key == '3') peId = 3;
	if (key == '4') peId = 4;
	if (key == '5') peId = 5;
	if (key == '6') peId = 6;
	if (key == '7') peId = 7;
	if (key == '8') peId = 8;
	if (key == '9') peId = 9;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
