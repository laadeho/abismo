#include "ofApp.h"
#include <ofTrueTypeFont.h>

//--------------------------------------------------------------
void ofApp::setup(){
	// listen on the given port
	//cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	current_msg_string = 0;

	ofBackground(0);
	//ofSetBackgroundAuto(false);
	//ofTrueTypeFont titulos;
	//titulos.setLineHeight(10);
	titulos.loadFont("Helvetica Bold.ttf", 20);
	texto1.loadFont("Helvetica Normal.ttf", 10);

	sensaciones[0] = "...";
	sensaciones[1] = "Entendimiento / Tranquilidad";
	sensaciones[2] = "Expectativa ";
	sensaciones[3] = "Miedo";
	sensaciones[4] = "Asombro";
	sensaciones[5] = "Euforia";
	sensaciones[6] = "Tristeza, Soledad";
	sensaciones[7] = "Abismo";
	sensaciones[8] = "Felicidad";
	sensaciones[9] = "Reconocimiento";
	sensaciones[10] = "Proximidad";

	// ESC 01 /////////////////////////
	ondas[0] = "alpha";
	ondas[1] = "beta";
	ondas[2] = "gamma";
	ondas[3] = "delta";
	ondas[4] = "theta";
	anchoOndaVentana = ofGetWidth() / 2 - posIniX-sep;
	for (int i = 0; i < 5; i++) {
		ondasFbo[i].allocate(anchoOndaVentana, 100, GL_RGBA);
		ondasFbo[i].begin();
		ofBackground(0);
		ondasFbo[i].end();
	}
	
	///////////////////// GUI ///////////////
	gui.setup();
	gui.setPosition(ofGetWidth() - 250, 50);
	gui.setName("abismo // proximo UI");
	gui.add(escenas.setup("Escena", 0, 0, 11));
	gui.add(guardaFrame.setup("Salvar Frames ", false));
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
	if (guardaFrame) {
		captura.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		captura.save("frames/" + ofToString(ofGetFrameNum()) + ".tif");
		//ofSaveScreen("frames/"+ ofToString(ofGetFrameNum()) + ".tif");
		//ofSaveImage("frames/" + ofToString(ofGetFrameNum()) + ".tif");
	}

	switch (escena)
	{
	case 0:
		if (opa01 != 0) {
			opa01 = 0;
			for (int i = 0; i < 5; i++) {
				ondasFbo[i].begin();
				ofBackground(0);
				ondasFbo[i].end();
			}
		}
			
		break;
	case 1:
		//ofSetCircleResolution(50);
		if (opa01 < 255) {
			opa01 += 1;
		}
		if (opaGral < 255) {
			opaGral += 1;
		}
		posOndaX += velOndaX;

		if (posOndaX > ondasFbo[0].getWidth()) {
			posOndaX = 0;
			for (int i = 0; i < 5; i++) {
				ondasFbo[i].begin();
				ofBackground(0);
				ondasFbo[i].end();
			}
		}
		break;
	default:
		break;
	}
	escena = escenas;

	updateOSC();
	/////////////// DATOS EMULADOS
	if (emularSensorMuse) {
		artifacts = true;
		alpha = true;
		beta = true;
		gamma = true;
		delta = true;
		theta = true;
		acc = true;
		gyro = true;
		isGood = true;
	}
	else {
		artifacts = false;
		alpha = false;
		beta = false;
		gamma = false;
		delta = false;
		theta = false;
		acc = false;
		gyro = false;
		isGood = false;
	}

	if (alpha)
		valSensores[0] = ofNoise(float(ofGetFrameNum()*.015*(0.25*0.5 + 1)));
	if (beta)
		valSensores[1] = ofNoise(float(ofGetFrameNum()*.005*(0.25*1 + 1)));
	if (gamma)
		valSensores[2] = ofNoise(float(ofGetFrameNum()*.0075*(0.25*2 + 1)));
	if (delta)
		valSensores[3] = ofNoise(float(ofGetFrameNum()*.0055*(0.25*3 + 1)));
	if (theta)
		valSensores[4] = ofNoise(float(ofGetFrameNum()*.0085*(0.25*4 + 1)));
	if (acc) {
		accX = ofNoise(ofGetFrameNum()*0.00025);
		accY = ofNoise(ofGetFrameNum()*0.00005);
		accZ = ofNoise(ofGetFrameNum()*0.00075);
	}
	if (gyro) {
		gyroX = ofNoise(ofGetFrameNum()*0.00325);
		gyroY = ofNoise(ofGetFrameNum()*0.0045);
		gyroZ = ofNoise(ofGetFrameNum()*0.00225);
	}
	if (isGood) {
		EEG1 = ofNoise(ofGetFrameNum()*0.0025);
		EEG2 = ofNoise(ofGetFrameNum()*0.0025);
		EEG3 = ofNoise(ofGetFrameNum()*0.002325);
		EEG4 = ofNoise(ofGetFrameNum()*0.005);
		auxLeft = ofNoise(ofGetFrameNum()*0.0075);
		auxRight = ofNoise(ofGetFrameNum()*0.0025);
	}
}

//--------------------------------------------------------------
void ofApp::updateOSC() {
	// hide old messages
	for (int i = 0; i < NUM_MSG_STRINGS; i++) {
		if (timers[i] < ofGetElapsedTimef()) {
			msg_strings[i] = "";
		}
	}

	// check for waiting messages
	while (receiver.hasWaitingMessages()) {
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);
		
		std::cout << "Mensaje: " << m.getAddress() << endl;
		
		// check for mouse moved message
		if (m.getAddress() == "/alpha") {
			valSensores[0] = m.getArgAsFloat(0);
		}
		if (m.getAddress() == "/beta") {
			valSensores[1] = m.getArgAsFloat(0);
		}
		if (m.getAddress() == "/gamma") {
			valSensores[2] = m.getArgAsFloat(0);
		}
		if (m.getAddress() == "/delta") {
			valSensores[3] = m.getArgAsFloat(0);
		}
		if (m.getAddress() == "/theta") {
			valSensores[4] = m.getArgAsFloat(0);
		}
		if (m.getAddress() == "/accelerometer") {
			std::cout << "ACCELEROMETER: " << m.getAddress() << endl;
		}
		else {
			// unrecognized message: display on the bottom of the screen
			string msg_string;
			msg_string = m.getAddress();
			msg_string += ": ";
			for (int i = 0; i < m.getNumArgs(); i++) {
				// get the argument type
				msg_string += m.getArgTypeName(i);
				msg_string += ":";
				// display the argument - make sure we get the right type
				if (m.getArgType(i) == OFXOSC_TYPE_INT32) {
					msg_string += ofToString(m.getArgAsInt32(i));
				}
				else if (m.getArgType(i) == OFXOSC_TYPE_FLOAT) {
					msg_string += ofToString(m.getArgAsFloat(i));
				}
				else if (m.getArgType(i) == OFXOSC_TYPE_STRING) {
					msg_string += m.getArgAsString(i);
				}
				else {
					msg_string += "unknown";
				}
			}
			// add to the list of strings to display
			msg_strings[current_msg_string] = msg_string;
			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
			current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
			// clear the next line
			msg_strings[current_msg_string] = "";
		}

	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	///// DRAW ///////////////////////////////////////////////////////
	if (titulo) {
		ofSetColor(255);
		ofFill();
		titulos.drawString(ofToString(escena) + ": " + sensaciones[escena], 100, 100);
	}
	
	switch (escena)
	{
	case 0:
		escena00();
		break;
	case 1:
		escena01();
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
	debugF();
}

void ofApp::debugF() {
	if (debug) {
		ofSetColor(255, 0, 0);
		ofFill();
		ofDrawBitmapString("- D E B U G -", 100, 50);
		for (int i = 0; i < 10; i++) {
			ofDrawBitmapString(sensaciones[i], 100, 125 + 20 * i);
		}
		ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 100);
	}
}

/////////////// ESCENA 00
void ofApp::escena00() {

}
/////////////// ESCENA 01
void ofApp::escena01() {
	// ENTENDIMIENTO // TRANQUILIDAD //
	ofPushStyle();
	for (int i = 0; i < 5; i++) {
		dibujaOnda(i, posIniX, ofGetHeight() - 150 - 130 * i, valSensores[i], anchoOndaVentana);
	}
	ofPopStyle();
	museConectado(100, 150);
	// Gyro y Acc
	dibujaOrientaciones(ofGetWidth() / 2 - 200, 100, accX, accY, accZ, ofColor(0,204,204));
	dibujaOrientaciones(ofGetWidth() / 2 - 100, 100, gyroX, gyroY, gyroZ, ofColor(204,0,0));

	ofPushMatrix();
	ofTranslate(ofGetWidth(),0,0);
	ofScale(-1, 1, 1);

	ofPushStyle();
	for (int i = 0; i < 5; i++) {
		dibujaOnda(i, posIniX, ofGetHeight() - 150 - 130 * i, valSensores[i], anchoOndaVentana);
	}
	ofPopStyle();
	museConectado(100, 150);
	// Gyro y Acc
	dibujaOrientaciones(ofGetWidth() / 2 - 200, 100, accX, accY, accZ, ofColor(0, 204, 204));
	dibujaOrientaciones(ofGetWidth() / 2 - 100, 100, gyroX, gyroY, gyroZ, ofColor(204, 0, 0));

	ofPopMatrix();

	/*
	float val = ofNoise(ofRandomf());
	std::cout << val << endl;
	*/
}
/////////////// ESCENA 00
void ofApp::escena02() {

}
/////////////// ESCENA 00
void ofApp::escena03() {

}
/////////////// ESCENA 00
void ofApp::escena04() {

}
/////////////// ESCENA 00
void ofApp::escena05() {

}
/////////////// ESCENA 00
void ofApp::escena06() {

}
/////////////// ESCENA 00
void ofApp::escena07() {

}
/////////////// ESCENA 00
void ofApp::escena08() {

}
/////////////// ESCENA 00
void ofApp::escena09() {

}
/////////////// ESCENA 00
void ofApp::escena10() {

}

void ofApp::dibujaOnda(int indice, int pX, int pY, float val, int ancho) {
	ofSetColor(255, opaGral);
	ondasFbo[indice].begin();
	ofSetColor(255, opa01-val*50);
	ofFill();
	ofEllipse(posOndaX, 50 + ofMap(val, 0, 1, 25, -25), 5 * val, 5 * val);

	ondasFbo[indice].end();
	ondasFbo[indice].draw(pX, pY);
	//////////////////////
	ofSetColor(255, opa01);
	ofFill();
	texto1.drawString(ondas[indice], pX, pY-10);
	ofSetColor(255, opa01);
	ofSetLineWidth(1);
	ofNoFill();
	for (int i = 0; i < 6; i++) { // LINEAS VERTICALES
		ofLine(pX + (ondasFbo[0].getWidth() / 5)*i, pY+20, pX + (ondasFbo[0].getWidth() / 5)*i, pY+80);
	}

	ofSetLineWidth(1);
	ofSetColor(255, opa01);
	ofNoFill();
	ofLine(pX, pY+50, pX+ondasFbo[0].getWidth(), pY+50);
}
//////// Funcion para Gyro y Acc
void ofApp::dibujaOrientaciones(int pX, int pY, float rX, float rY, float rZ, ofColor col) {
	ofPushMatrix();
	ofTranslate(pX, pY, 0);
	ofRotateX(rX*360);
	ofRotateY(rY*360);
	ofRotateZ(rZ*360);

	ofSetLineWidth(1);
	ofSetColor(255, 0, 0, opa01);
	ofNoFill();
	ofLine(0, 0, 50, 0);
	ofSetColor(0, 255, 0, opa01);
	ofNoFill();
	ofLine(0, 0, 0, 50);
	ofSetColor(0, 0, 255, opa01);
	ofNoFill();
	ofLine(0, 0, 0, 0, 0, 50);

	ofSetColor(col, opa01/5);
	ofFill();
	ofBox(50);
	ofSetColor(255, opa01);
	ofNoFill();
	ofBox(50);
	ofPopMatrix();
}
//////// Funcion muse conectado
void ofApp::museConectado(int pX, int pY) {
	ofPushMatrix();
	ofTranslate(pX, pY);

	if (museOn) {
		ofSetColor(64, 255, 0, opaGral);
		ofFill();
		ofRect(0, 0, 10, 10);
	
		ofSetColor(255, opaGral);
		ofNoFill();
		ofRect(0, 0, 10, 10);
	}
	if (blink) {
		ofSetColor(64, 255, 0, opaGral);
		ofFill();
		ofRect(0, 20, 10, 10);

		ofSetColor(255, opaGral);
		ofNoFill();
		ofRect(0, 20, 10, 10);
	}
	if (jawClench) {
		ofSetColor(64, 255, 0, opaGral);
		ofFill();
		ofRect(0, 40, 10, 10);

		ofSetColor(255, opaGral);
		ofNoFill();
		ofRect(0, 40, 10, 10);
	}
	if (isGood) {
		ofSetColor(64, 255, 0, opaGral);
		ofFill();
		ofRect(30, 0, EEG1*50, 10);
		ofRect(30, 20, EEG2*50, 10);
		ofRect(30, 40, EEG3*50, 10);
		ofRect(30, 60, EEG4*50, 10);
		ofRect(30, 80, auxLeft * 50, 10);
		ofRect(30, 100, auxRight * 50, 10);
		ofSetColor(255, opaGral);
		ofNoFill();
		ofRect(30, 0, 50, 10);
		ofRect(30, 20, 50, 10);
		ofRect(30, 40, 50, 10);
		ofRect(30, 60, 50, 10);
		ofRect(30, 80, 50, 10);
		ofRect(30, 100, 50, 10);
	}
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
	if (key == 'c' || key == 'C')
		ofBackground(0);
	if (key == 't' || key == 'T')
		titulo = !titulo;
	if (key == 'i' || key == 'I')
		isGood = !isGood;
	if (key == 's' || key == 'S')
		guardaFrame = !guardaFrame;

	if (key == OF_KEY_LEFT) {
		escena--;
		if(escena < 0)
			escena = numEscenas - 1;
	}
	if (key == OF_KEY_RIGHT) {
		escena++;
		escena = escena % numEscenas;
	}
	escenas = escena;
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