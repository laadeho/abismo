#include "ofApp.h"
#include <ofTrueTypeFont.h>

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(200);
	ofSetCircleResolution(50);
	//ofTrueTypeFont titulos;
	//titulos.setLineHeight(10);
	titulos.loadFont("Helvetica Bold.ttf", 20);

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
	if(alpha)
		std::cout << "Alpha: " << alpha << endl;

}

//--------------------------------------------------------------
void ofApp::draw(){
	if (debug) {
		for (int i = 0; i < 10; i++) {
			//ofDrawBitmapString(sensaciones[i], 100, 125+20*i);
		}
	}
	///// DRAW ///////////////////////////////////////////////////////
	//ofDrawBitmapString(sensaciones[escena], ofGetWidth()/2, 225 + 20);
	ofSetColor(255);
	ofFill();
	titulos.drawString(escena +": "+sensaciones[escena], 100, 100);

	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 100);
	switch (escena)
	{
	case 0:
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'd' || key == 'D')
		debug = !debug;
	if (key == 'g' || key == 'G')
		showGui = !showGui;
	if (key == OF_KEY_LEFT)
		escena--;
	if (key == OF_KEY_RIGHT)
		escena++;
	escena = escena % numEscenas;
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
