#include "ofApp.h"

//--------------------------------------------------------------������
void ofApp::setup() {
	//ofSetLogLevel(OF_LOG_VERBOSE);

	ofSetVerticalSync(false);
	ofSetFrameRate(60);

	//----------------------------GUI�����ݒ�
	gui.setup();
	gui.setName("main");
	gui.add(g_screenAlph.setup("screenAlph", 255, 0, 255));
	gui.add(g_liveCodingAlph.setup("liveCodingAlph", 0, 0, 255));
	gui.add(g_amp.setup("amp", 0, 0, 1));
	gui.add(g_bPostEffects.setup("bPostEffects", false));
	gui.add(peId.setup("PostEffectsID", 0, 0, 9));
	gui.add(g_effectsVal.setup("effectsVal", 0, 0, 1));

	gui.setPosition(10, 30);

	//----------------------------�R���e���c�̏����ݒ�
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

	//-----------------------------�|�X�g�t�F�N�g�����ݒ�/�V�F�[�_�ǂݍ���
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


	//---------------------------------------�����͏����ݒ�
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

//--------------------------------------------------------------���t���[���Ă΂����
void ofApp::update() {
	//lets scale the vol up to a 0-1 range
	//���ʂ̒�����liveCoder�։��p�����[�^��n��
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
	liveCoder.val0 = g_amp * vol;
	liveCoder.val1 = g_amp * scaledVol;

	//displayFbo.begin()/end()�ɋ��܂ꂽdraw()�֐���
	//�R���e���c��displayFbo�ɏ�������
	displayFbo.begin();
	//�O�t���[���̓��e���N���A
	ofSetColor(0, 255);
	ofDrawRectangle(0, 0, displayFbo.getWidth(), displayFbo.getHeight());

	//�ȉ��R���e���c�̏�������
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

	//�|�X�g�G�t�F�N�g��������
	if (g_bPostEffects) {
		displayFbo.begin();
		pe.setUniformVal0(g_amp*vol);
		pe.setUniformVal1(g_effectsVal);
		pe.draw(peId);
		displayFbo.end();
	}
}

//--------------------------------------------------------------���t���[���Ă΂����
//�����ŌĂ΂ꂽdraw()�֐��Ń��C���f�B�X�v���C�֕`������
void ofApp::draw() {
	ofSetColor(255);
	displayFbo.draw(0, 0, 540, 360); //���̉�ʂ̏�Ԃ��v���r���[
	liveCoder.draw(540, 0, 540, 360); //���C�u�R�[�f�B���O�p�̃V�F�[�_�v���r���[

	//-----------------GUI�̕`��
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

//--------------------------------------------------------------�I�����ɌĂ΂����
void ofApp::exit() {
	soundStream.stop(); //�����͗p�̃I�u�W�F�N�g���X�g�b�v����
}

//--------------------------------------------------------------//���̏���
//�����̂��̂����Ȃ�R�s�y�����B512�o���h�̃X�y�N�g�����𖈃t���[���񋟂���
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

//�ȉ��}�E�X�A�L�[�C�x���g�֐�
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'f') ofToggleFullscreen(); //�t���X�N���[����
	if (key == ' ') liveCoder.reload(); //���C�u�R�[�f�B���O�̃V�F�[�_�������[�h
	if (key == 'p') nMeta.bPika = !nMeta.bPika; //���^�{�[���̃e�N�X�`���ύX

	//�|�X�g�G�t�F�N�g �؂�ւ�
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
