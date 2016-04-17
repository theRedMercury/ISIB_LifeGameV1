#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("Life Game ISIB V1");
	ofSetBackgroundColor(ofColor(46, 47, 48));

	this->manageLife = new LifeManagement();
	
	ofSetFrameRate(60);
	ofSetVerticalSync(false);

	ofSetCircleResolution(100);
	//ofSetFullscreen(true);
	//ofSetWindowShape(1200, 800);
	//ofSetupScreenOrtho(ofGetWidth(), ofGetHeight());

	this->manageLife->init();
}

//--------------------------------------------------------------
void ofApp::update(){
	this->manageLife->update();
}


//--------------------------------------------------------------
void ofApp::draw(){
	this->manageLife->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 32) {
		this->manageLife->setInvasiv();
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
