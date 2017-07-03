#include "ofApp.h"
#include <winsock2.h> 

//--------------------------------------------------------------
void ofApp::setup(){
	//setupEscena03();
}

//--------------------------------------------------------------
void ofApp::update(){
	//updateEscena03();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	drawEscena03();
}

void ofApp::drawEscena03() {
	cam03.begin();
	ofPushMatrix();
	//ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	float rotacion = ofGetElapsedTimeMillis() * 0.005;
	//rotacion = rotacion % 360;
	ofRotateY(rotacion);
	for (int i = 0; i < numBox; i++) {
		//coords[i] = ofVec3f(100, 100, 100);
		ofPushMatrix();
		ofTranslate(coords[i].x, coords[i].y, coords[i].z);
		ofBox(tamBox);
		ofPopMatrix();
	}
	
	ofPopMatrix();
	cam03.end();
}

void ofApp::nuevoEnte03() {
	if (numBox >= 50)return;
	int newPosX = int(ofRandom(2));
	newPosX = int(ofMap(newPosX, 0, 1, -1, 1))*tamBox;
	int newPosY = int(ofRandom(2));
	newPosY = int(ofMap(newPosY, 0, 1, -1, 1))*tamBox;

	coords.push_back(ofVec3f(newPosX, newPosY, ofRandom(100)));
	numBox = coords.size();
	//numBox++;
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	nuevoEnte03();
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
