#include "ofApp.h"
#include <ofTrueTypeFont.h>

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(0);
	ofSetBackgroundAuto(false);
	//ofTrueTypeFont titulos;
	//titulos.setLineHeight(10);
	titulos.loadFont("Helvetica Bold.ttf", 20);
	texto1.loadFont("Helvetica Normal.ttf", 10);

	sensaciones[0] = "Entendimiento / Tranquilidad";
	sensaciones[1] = "Expectativa ";
	sensaciones[2] = "Miedo";
	sensaciones[3] = "Asombro";
	sensaciones[4] = "Euforia";
	sensaciones[5] = "Tristeza, Soledad";
	sensaciones[6] = "Abismo";
	sensaciones[7] = "Felicidad";
	sensaciones[8] = "Reconocimiento";
	sensaciones[9] = "Proximidad";
	// ESC 01 /////////////////////////
	ondas[0] = "alpha";
	ondas[1] = "beta";
	ondas[2] = "gamma";
	ondas[3] = "delta";
	ondas[4] = "theta";

	///////////////////// GUI ///////////////
	gui.setup();
	gui.setPosition(ofGetWidth() - 250, 50);
	gui.setName("abismo // proximo UI");
	gui.add(escenas.setup("Escena",0,0,9));
	// Brain
	gui.add(alpha.setup("alpha", false));
	gui.add(beta.setup("beta", false));
	gui.add(gamma.setup("gamma", false));
	gui.add(delta.setup("delta", false));
	gui.add(theta.setup("theta", false));
	// Artifacts
	gui.add(artifacts.setup("artifacts", false));
	gui.add(museOn.setup("museOn", false));
	gui.add(blink.setup("blink",false));
	gui.add(jawClench.setup("jawClench",false));
	// Acc
	gui.add(acc.setup("acc", false));
	gui.add(accX.setup("accX", 0.1f,0.0f,1.0f));
	gui.add(accY.setup("accY", 0.1f, 0.0f, 1.0f));
	gui.add(accZ.setup("accZ", 0.1f, 0.0f, 1.0f));
	// Gyro
	gui.add(gyro.setup("gyro", false));
	gui.add(gyroX.setup("gyroX", 0.1f, 0.0f, 1.0f));
	gui.add(gyroY.setup("gyroY", 0.1f, 0.0f, 1.0f));
	gui.add(gyroZ.setup("gyroZ", 0.1f, 0.0f, 1.0f));
	// Connection
	gui.add(isGood.setup("isGood", false));
	gui.add(EEG1.setup("eeg1", 0.1f, 0.0f, 1.0f));
	gui.add(EEG2.setup("eeg2", 0.1f, 0.0f, 1.0f));
	gui.add(EEG3.setup("eeg3", 0.1f, 0.0f, 1.0f));
	gui.add(EEG4.setup("eeg4", 0.1f, 0.0f, 1.0f));
	gui.add(auxLeft.setup("auxLeft", 0.1f, 0.0f, 1.0f));
	gui.add(auxRight.setup("auxRight", 0.1f, 0.0f, 1.0f));
	////////////// GUI //////////////////

	/*
	std::cout << "Ancho: " << ofGetScreenWidth() << endl;
	std::cout << "Alto: " << ofGetScreenHeight() << endl;
	*/

	
}

//--------------------------------------------------------------
void ofApp::update() {
	if (alpha)
		valSensores[0] = ofNoise(float(ofGetElapsedTimeMillis()*.005*(0.25*0.5 + 1)));
	if (beta)
		valSensores[1] = ofNoise(float(ofGetElapsedTimeMillis()*.005*(0.25*1 + 1)));
	if (gamma)
		valSensores[2] = ofNoise(float(ofGetElapsedTimeMillis()*.005*(0.25*2 + 1)));
	if (delta)
		valSensores[3] = ofNoise(float(ofGetElapsedTimeMillis()*.005*(0.25*3 + 1)));
	if (theta)
		valSensores[4] = ofNoise(float(ofGetElapsedTimeMillis()*.005*(0.25*4 + 1)));
	if (acc) {
		accX = ofNoise(ofGetElapsedTimeMillis()*0.00025);
		accY = ofNoise(ofGetElapsedTimeMillis()*0.0005);
		accZ = ofNoise(ofGetElapsedTimeMillis()*0.00075);
	}


	if (emularSensorMuse) {
		for (int i = 0; i < 5; i++) {
			valSensores[i] = ofNoise(float(ofGetElapsedTimeMillis()*.005*(0.25 * i + 1)));
		}
	}

	switch (escena)
	{
	case 0:
		//ofSetCircleResolution(50);
		if (ofGetFrameNum() > 500) {
			if (opa01 < 255) {
				opa01 += 0.025;
			}
			if (opaGral < 255) {
				opaGral += 0.05;
			}
			posOndaX += 0.25;
		}
		if (posOndaX > ofGetWidth() / 2) {
			posOndaX = posIniX;
			ofBackground(0);
		}
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (debug) {
		ofSetColor(255, 0, 0);
		ofFill();
		ofDrawBitmapString("- D E B U G -", 100, 50);
		for (int i = 0; i < 10; i++) {
			ofDrawBitmapString(sensaciones[i], 100, 125+20*i);
		}
		ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 100);
	}
	///// DRAW ///////////////////////////////////////////////////////
	ofSetColor(0);
	ofFill();
	ofRect(95,75,450,35);
	ofSetColor(255, opaGral);
	ofFill();
	titulos.drawString(ofToString(escena) +": "+sensaciones[escena], 100, 100);

	switch (escena)
	{
	case 0:
		escena01();
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	default:
		break;
	}

	///// DRAW ///////////////////////////////////////////////////////
	if(showGui)
		gui.draw();
}

/////////////// ESCENA 01
void ofApp::escena01() { 
	// ENTENDIMIENTO // TRANQUILIDAD //

	for (int i = 0; i < 5; i++) {
		dibujaOnda(i, posIniX, ofGetHeight() - 100 - 120 * i, valSensores[i]);
	}
	dibujaOrientacion(ofGetWidth()/2-100, 100);

	ofPushMatrix();
	ofTranslate(ofGetWidth(),0,0);
	ofScale(-1, 1, 1);
	for (int i = 0; i < 5; i++) {
		dibujaOnda(i, posIniX, ofGetHeight() - 100 - 120 * i, valSensores[i]);
	}
	dibujaOrientacion(ofGetWidth() / 2 - 100, 100);
	ofPopMatrix();

	/*
	float val = ofNoise(ofRandomf());
	std::cout << val << endl;
	*/
}

void ofApp::dibujaOnda(int indice, int pX, int pY, float val) {
	ofSetColor(0);
	ofFill();
	ofRect(pX-5, pY-20, 50,25);
	ofSetColor(255, opa01);
	ofFill();
	texto1.drawString(ondas[indice], pX, pY);

	ofSetLineWidth(0.15);
	ofSetColor(100, opa01);
	ofNoFill();
	ofLine(pX, pY - 50, ofGetWidth()/2, pY - 50);

	ofSetColor(255, opa01);
	ofNoFill();
	ofSetLineWidth(1);
	for (int i = 0; i < 6; i++) {
		ofLine(pX+((ofGetWidth() - pX * 2) /10)*i, pY - 25, pX + ((ofGetWidth() - pX * 2) / 10)*i, pY - 75);
	}
	ofSetColor(255, opa01);
	ofFill();
	ofEllipse(posOndaX, pY-50+ofMap(val, 0, 1, 25, -25), 5*val,5*val);
}
void ofApp::dibujaOrientacion(int pX, int pY) {
	ofPushMatrix();
	ofTranslate(pX, pY, 0);
	ofSetColor(0);
	ofFill();
	ofRect(-50, -50, 100, 100);
	ofRotateX(accX*360);
	ofRotateY(accY*360);
	ofRotateZ(accZ*360);

	ofSetColor(255, 0, 0, 50);
	ofFill();
	ofBox(50);
	ofSetColor(255);
	ofNoFill();
	ofBox(50);
	ofPopMatrix();
}

//////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'd' || key == 'D')
		debug = !debug;
	if (key == 'g' || key == 'G')
		showGui = !showGui;
	if (key == 'e' || key == 'E')
		emularSensorMuse = !emularSensorMuse;
	if (key == OF_KEY_LEFT)
		escena--;
	if (key == OF_KEY_RIGHT)
		escena++;
	escena = escena % numEscenas;
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