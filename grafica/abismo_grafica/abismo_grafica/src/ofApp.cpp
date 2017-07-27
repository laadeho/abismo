#include "ofApp.h"
#include <ofTrueTypeFont.h>
/*
ENVIAR OSC de GSR  0 - 255 "\gsr" PROMEDIANDO AMBOS SENSORES
*/

//--------------------------------------------------------------
void ofApp::setup(){
	// OSC SETUP
	receiver.setup(PORT);
	current_msg_string = 0;

	ofSetFrameRate(60);
	ofBackground(0);
	ofEnableAlphaBlending(); // lines have the ability to draw with alpha enabled

	//ofEnableSmoothing();
	//ofSetBackgroundAuto(false);
	//ofTrueTypeFont titulos;
	//titulos.setLineHeight(10);
	
	setupGUI();
	ofSetVerticalSync(true);

	if (fullScreenDisplay)
		ofSetFullscreen(true);

	titulos.loadFont("Helvetica Bold.ttf", 20);
	texto1.loadFont("Helvetica Normal.ttf", 10);

	// ESC 00 /////////////////////////
	logoAbismo.load("images/abismoLogo_1240x600.png");
	
	setupEsc01();
	setupEsc02();
	/*
	ofVec2f test = ofVec2f(10, 10);
	camera.setupPerspective(true, .9, .5, 650, test);
	*/
	//myCam.disableMouseInput();
	//myCam.disableMouseMiddleButton();

	// ESC 03 /////////////////////////
	// ESC 04 /////////////////////////
	// ESC 05 /////////////////////////
	cSrf = ofColor(0, 0, 0, 0);
	// ESC 06 /////////////////////////
	// ESC 07 /////////////////////////
	// ESC 08 /////////////////////////
	
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
	case 0: // LOGO
		if (iniciaTodo&&contador < limiteContador){
			contador++;
		}
		if (contador == limiteContador){
			entraLogo = true;
			iniciaTodo = false;
			contador = 0;
		}
		if (entraLogo) {
			if (opaLogo < 255) {
				opaLogo += velOpa;
			}
			if (opaLogo == 255)
				entraLogo = false;
		}
		if (saleLogo && !entraLogo) {
			if (opaLogo > 0) {
				opaLogo -= velOpa;
			}
			if (opaLogo == 0) {
				escena = 1;
				//escenas = escena;
				saleLogo = false;
				iniciaTodo = true;
			}
		}
		break;
	case 1: // Reconocimiento
		updateEsc01();
		break;
	case 2:
		updateEsc02();
		break;
	case 3:
		updateEsc03();
		break;
	case 4:
		updateEscena04();
		break;
	case 5:
		updateEscena04(); // mismo update para continuar grafico
		break;
	case 6:
		break;
	case 7:
		break;
	default:
		break;
	}
	updateOSC();
	updateEmular();
	camAnim();

	if (switchAlpha) {
		alphaEncendido = !alphaEncendido;
		switchAlpha = false;
	}

	if (alphaEncendido) {
		ofSetBackgroundAuto(false);
	}
	else {
		ofSetBackgroundAuto(true);
	}

	if (apagaMalla) {
		if (alphaSrf02 > 0)
			alphaSrf02 -= 0.25;
		else if (alphaSrf02 == 0) {
			mallaSrf = false;
		}
	}
	else {
		if (!mallaSrf)
			mallaSrf = true;
		if (alphaSrf02 < 255)
			alphaSrf02 += 0.25;
	}
}
//--------------------------------------------------------------
/////////////// DATOS EMULADOS
void ofApp::updateEmular() {
	if (emularSensores) {
		artifacts = true;
		alpha = true;
		beta = true;
		gamma = true;
		delta = true;
		theta = true;

		pulse = true;
		gsr = true;

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

		pulse = false;
		gsr = false;

		acc = false;
		gyro = false;
		isGood = false;
	}
	if (alpha) {
		valSensor1[0] = ofNoise(float(ofGetFrameNum()*.015*(0.25*0.5 + 1)));
		valSensor2[0] = ofNoise(float(ofGetFrameNum()*.0135*(0.125*0.5 + 1)));
	}
	if (beta) {
		valSensor1[1] = ofNoise(float(ofGetFrameNum()*.0035*(0.225 * 1.15 + 1)));
		valSensor2[1] = ofNoise(float(ofGetFrameNum()*.005*(0.25 * 1 + 1)));
	}
	if (gamma) {
		valSensor1[2] = ofNoise(float(ofGetFrameNum()*.0075*(0.25 * 2 + 1)));
		valSensor2[2] = ofNoise(float(ofGetFrameNum()*.00475*(0.225 * 1.75 + 1)));
	}
	if (delta) {
		valSensor1[3] = ofNoise(float(ofGetFrameNum()*.0055*(0.25 * 3 + 1)));
		valSensor2[3] = ofNoise(float(ofGetFrameNum()*.0025*(0.125 * 2.25 + 1)));
	}
	if (theta) {
		valSensor1[4] = ofNoise(float(ofGetFrameNum()*.0085*(0.25 * 4 + 1)));
		valSensor2[4] = ofNoise(float(ofGetFrameNum()*.00385*(0.215 * 4.25 + 1)));
	}
	if (pulse) {
		valSensor1[5] = ofNoise(float(ofGetFrameNum()*.0065*(0.35 * 4 + 1)));
		valSensor2[5] = ofNoise(float(ofGetFrameNum()*.00625*(0.135 * 2.4 + 1)));
	}
	if (gsr) {
		valSensor1[6] = ofNoise(float(ofGetFrameNum()*.0035*(0.225 * 4 + 1)));
		valSensor2[6] = ofNoise(float(ofGetFrameNum()*.00135*(0.1225 * 2.4 + 1)));
	}

	if (acc) {
		accX1 = ofNoise(ofGetFrameNum()*0.0025);
		accY1 = ofNoise(ofGetFrameNum()*0.0005);
		accZ1 = ofNoise(ofGetFrameNum()*0.0075);
		accX2 = ofNoise(ofGetFrameNum()*-0.00325);
		accY2 = ofNoise(ofGetFrameNum()*-0.00025);
		accZ2 = ofNoise(ofGetFrameNum()*-0.0045);
	}
	if (gyro) {
		gyroX1 = ofNoise(ofGetFrameNum()*0.0325);
		gyroY1 = ofNoise(ofGetFrameNum()*0.045);
		gyroZ1 = ofNoise(ofGetFrameNum()*0.0225);
		gyroX2 = ofNoise(ofGetFrameNum()*-0.0225);
		gyroY2 = ofNoise(ofGetFrameNum()*-0.0345);
		gyroZ2 = ofNoise(ofGetFrameNum()*-0.0125);
	}
	if (isGood) {
		EEG11 = ofNoise(ofGetFrameNum()*0.0025);
		EEG21 = ofNoise(ofGetFrameNum()*0.0025);
		EEG31 = ofNoise(ofGetFrameNum()*0.002325);
		EEG41 = ofNoise(ofGetFrameNum()*0.005);
		auxLeft1 = ofNoise(ofGetFrameNum()*0.0075);
		auxRight1 = ofNoise(ofGetFrameNum()*0.0025);
		EEG12 = ofNoise(ofGetFrameNum()*0.00625);
		EEG22 = ofNoise(ofGetFrameNum()*0.00525);
		EEG32 = ofNoise(ofGetFrameNum()*0.00425);
		EEG42 = ofNoise(ofGetFrameNum()*0.0025);
		auxLeft2 = ofNoise(ofGetFrameNum()*0.002675);
		auxRight2 = ofNoise(ofGetFrameNum()*0.00125);
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
		ofxOscMessage m;
		receiver.getNextMessage(m);
		//std::cout << "Mensaje: " << m.getAddress() << endl;
		if (m.getAddress() == "/escena") {
			if (escena == 0 && m.getArgAsInt(0) == 1) {
				if (!entraLogo)
					saleLogo = true;
			}
			else if (escena == 1) {
				cambia01 = true;
			}
			else if (escena == 2) {
				camara02 = true;
				escena++;
			}
			else {
				//escena++;
				escena = m.getArgAsInt(0);
				std::cout << "Mensaje escena Num: " << m.getArgAsInt(0) << endl;
				escena = escena % numEscenas;
			}
		}
		else if (m.getAddress() == "/alpha") {
			if (m.getArgAsInt(0) == 1)
				valSensor1[0] = m.getArgAsFloat(1);
			else if (m.getArgAsInt(0) == 2)
				valSensor2[0] = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/beta") {
			if (m.getArgAsInt(0) == 1)
				valSensor1[1] = m.getArgAsFloat(1);
			else if (m.getArgAsInt(0) == 2)
				valSensor2[1] = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/gamma") {
			if (m.getArgAsInt(0) == 1)
				valSensor1[2] = m.getArgAsFloat(1);
			else if (m.getArgAsInt(0) == 2)
				valSensor2[2] = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/delta") {
			if (m.getArgAsInt(0) == 1)
				valSensor1[3] = m.getArgAsFloat(1);
			else if (m.getArgAsInt(0) == 2)
				valSensor2[3] = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/theta") {
			if (m.getArgAsInt(0) == 1)
				valSensor1[4] = m.getArgAsFloat(1);
			else if (m.getArgAsInt(0) == 2)
				valSensor2[4] = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/accelerometer") {
			if (m.getArgAsInt(0) == 1) {
				accX1 = float(m.getArgAsDouble(1));
				accY1 = float(m.getArgAsDouble(2));
				accZ1 = float(m.getArgAsDouble(3));
			}
			else if (m.getArgAsInt(0) == 2) {
				accX2 = float(m.getArgAsDouble(1));
				accY2 = float(m.getArgAsDouble(2));
				accZ2 = float(m.getArgAsDouble(3));
			}
			//std::cout << "ACCELEROMETER: " << m.getAddress() << endl;
		}
		else if (m.getAddress() == "/gyro") {
			if (m.getArgAsInt(0) == 1) {
				gyroX1 = int(m.getArgAsDouble(1));
				gyroY1 = int(m.getArgAsDouble(2));
				gyroZ1 = int(m.getArgAsDouble(3));
			}
			else if (m.getArgAsInt(0) == 2) {
				gyroX2 = int(m.getArgAsDouble(1));
				gyroY2 = int(m.getArgAsDouble(2));
				gyroZ2 = int(m.getArgAsDouble(3));
			}
			//std::cout << "gX: " << gyroX1 << ", gY: " << gyroY1 << ", gZ: " << gyroZ1 << endl;
		}
		else if (m.getAddress() == "/artifacts") {
			if (m.getArgAsInt(0) == 1) {
				int mOn = int(m.getArgAsDouble(1));
				int bl = int(m.getArgAsDouble(2));
				int jC = int(m.getArgAsDouble(3));

				if (mOn != 0)
					museOn1 = true;
				else
					museOn1 = false;
				if (bl != 0)
					blink1 = true;
				else
					blink1 = false;
				if (jC != 0)
					jawClench1 = true;
				else
					jawClench1 = false;
			}
			else if (m.getArgAsInt(0) == 2) {
				int mOn = int(m.getArgAsDouble(1));
				int bl = int(m.getArgAsDouble(2));
				int jC = int(m.getArgAsDouble(3));
				if (mOn != 0)
					museOn2 = true;
				else
					museOn2 = false;
				if (bl != 0)
					blink2 = true;
				else
					blink2 = false;
				if (jC != 0)
					jawClench2 = true;
				else
					jawClench2 = false;
			}
		}
		else if (m.getAddress() == "/pulse") {
			int pulseAt1 = int(m.getArgAsInt32(0));
			if (pulseAt1 == 1) {
				valSensor1[5] = abs(int(m.getArgAsInt32(1)));
			}
			else if (pulseAt1 == 2) {
				valSensor2[5] = abs(int(m.getArgAsInt32(1)));
			}
		}
		else if (m.getAddress() == "/gsr") {
			int gsrAt1 = int(m.getArgAsInt32(0));
			if (gsrAt1 == 1) {
				valSensor1[6] = abs(int(m.getArgAsInt32(1)));
			}
			else if (gsrAt1 == 2) {
				valSensor2[6] = abs(int(m.getArgAsInt32(1)));
			}
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
void ofApp::muestraValSensores() {
	if (debug) {
		ofPushStyle();
		ofSetColor(255);
		ofDrawBitmapString("SENSOR 01", 100, ofGetHeight() - 315);
		ofDrawBitmapString("SENSOR 02", 300, ofGetHeight() - 315);

		for (int i = 0; i < numSens; i++) {
			ofDrawBitmapString(sensor[i] + ": " + ofToString(valSensor1[i]), 100, ofGetHeight() - numSens * 20 - 150 + i * 20);
		}
		for (int i = 0; i < numSens; i++) {
			ofDrawBitmapString(sensor[i] + ": " + ofToString(valSensor2[i]), 300, ofGetHeight() - numSens * 20 - 150 + i * 20);
		}
		ofPopStyle();
	}
}
//--------------------------------------------------------------
void ofApp::draw(){
	if (alphaActivo) {
		ofEnableAlphaBlending();
	}
	///// DRAW ///////////////////////////////////////////////////////

	
	switch (escena)
	{
	case 0:
		escena00();
		break;
	case 1:
		escena01();
		break;
	case 2:
		escena02();
		break;
	case 3:
		escena03();
		break;
	case 4:
		escena04();
		break;
	case 5:
		escena05();
		break;
	case 6:
		escena06();
		break;
	case 7:
		escena07();
		break;
	case 8:
		escena08();
		break;
	case 9:
		escena09();
		break;
	default:
		break;
	}

	///// DRAW ///////////////////////////////////////////////////////
	if(showGui)
		gui.draw();
	if (debug) {
		debugF();
		muestraValSensores();
	}
	if (titulo) {
		ofSetColor(255);
		ofFill();
		titulos.drawString(ofToString(escena) + ": " + sensaciones[escena], 100, 100);
	}
}

void ofApp::debugF() {
		ofPushStyle();
		ofSetColor(255, 0, 0);
		ofFill();
		ofDrawBitmapString("- D E B U G -", 100, 50);
		for (int i = 0; i < 10; i++) {
			ofDrawBitmapString(ofToString(i)+": "+sensaciones[i], 10, 125 + 20 * i);
		}
		ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate()), 100, 350);

		ofSetColor(255, 0, 0);
		ofFill();
		ofDrawCircle(0,0, 10);
		ofDrawCircle(ofGetWidth(), 0, 10);
		ofDrawCircle(0, ofGetHeight(), 10);
		ofDrawCircle(ofGetWidth(), ofGetHeight(), 10);
		ofPopStyle();
}
//--------------------------------------------------------------
void ofApp::camAnim() {
	////// superficie
	if (camara02) {
		if (rotaParts < 1)
			rotaParts += 0.0025;
		if (rotaParts > 0.95)
			gira2 = true;
		if (gira2) {
			rota360 += 0.25;
			if (rota360 > 360)
				rota360 = 0;
		}
	}
	else {
		if (rotaParts > 0)
			rotaParts -= 0.0025;
		if (gira2) {
			if (rota360 < 180) {
				if (rota360 > 0)
					rota360 -= 0.25;
				if (int(rota360) == 0)
					gira2 = false;
			}
			else if (rota360 > 180)
				if (rota360 < 360)
					rota360 += 0.25;
		}
	}
}
//--------------------------------------------------------------
/////////////// ESCENA 00 
///////////////////////////// LOGO
void ofApp::escena00() {
	if(debug){
		ofSetColor(255);
		ofFill();
		ofDrawBitmapString("Contador: "+ ofToString(contador), 100, 400);
		ofDrawBitmapString("Inicia Todo: "+ ofToString(iniciaTodo), 100, 420);
		ofDrawBitmapString("Entra Logo: "+ ofToString(entraLogo), 100, 440);
		ofDrawBitmapString("Sale Logo: " + ofToString(saleLogo), 100, 460);
		ofDrawBitmapString("Opacidad Logo: " + ofToString(opaLogo), 100, 480);
	}

	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, opaLogo);
	//logoAbismo.draw(-120, ofGetHeight() / 2 - 300);
	logoAbismo.draw(ofGetWidth() / 2 - 620, ofGetHeight() / 2 - 300);
	ofDisableAlphaBlending();
}
//--------------------------------------------------------------
/////////////// ESCENA 01
///////////////////////////// Entendimiento / Tranquilidad
void ofApp::setupEsc01() {
	anchoOndaVentana = ofGetWidth() / 2 - posIniX - sep;
	for (int i = 0; i < numSens*2; i++) {
		ondasFbo[i].allocate(anchoOndaVentana, 100, GL_RGBA);
		ondasFbo[i].begin();
		ofBackground(0);
		ondasFbo[i].end();
	}
}
void ofApp::updateEsc01() {
	if (!cambia01 && opa01 < 255) {
		opa01 += velOpa;
	}
	// Solo switch de esc01
	switch (esc01) {
	case 0:
		posOndaX += velOndaX;
		if (posOndaX > ondasFbo[0].getWidth()) {
			posOndaX = 0;
			pasada++;
			for (int i = 0; i < numSens*2; i++) {
				ondasFbo[i].begin();
				ofBackground(0);
				ondasFbo[i].end();
			}
		}
		if (pasada >= 1) {
			cambia01 = true;
		}
		break;
	case 1:
		for (int i = 0; i < numPart - 2; i++) {
			particulas1[i].set(
				sin((TWO_PI / numPart)*i)*(radio01 + valSensor1[i] * multSensores)*escala01,
				cos((TWO_PI / numPart)*i)*(radio01 + valSensor1[i] * multSensores)*escala01,
				0);
			particulas2[i].set(
				sin((TWO_PI / numPart)*i)*(radio01 + valSensor2[i] * multSensores)*escala01,
				cos((TWO_PI / numPart)*i)*(radio01 + valSensor2[i] * multSensores)*escala01,
				0);
		}
		for (int i = numPart-2; i < numPart; i++) {
			particulas1[i].set(
				sin((TWO_PI / numPart)*i)*(radio01 + ofMap(valSensor1[i], 0, 255, 0, 1) *multSensores)*escala01,
				cos((TWO_PI / numPart)*i)*(radio01 + +ofMap(valSensor1[i], 0, 255, 0, 1) * multSensores)*escala01,
				0);
			particulas2[i].set(
				sin((TWO_PI / numPart)*i)*(radio01 + +ofMap(valSensor2[i], 0, 255, 0, 1) * multSensores)*escala01,
				cos((TWO_PI / numPart)*i)*(radio01 + +ofMap(valSensor2[i], 0, 255, 0, 1) * multSensores)*escala01,
				0);
		}
		if (radio01 < radio01Fin)
			radio01 += 0.5;

		if (valSensor1[5] > 100) {
			if (aumentaCuentaPulso = true) {
				cuentaPulsos++;
				aumentaCuentaPulso = false;
			}
		}
		else if (valSensor1[5] < 5) {
			aumentaCuentaPulso = true;
		}

		if (cuentaPulsos > 80)
			cambia01 = true;

		break;
	case 2:
		if (!partInPos) {
			for (int i = 0; i < numPart; i++) {
				float pTempX = particulas1[i].x;
				particulas1[i].set(
					pTempX, 0, 0
				);

				if (particulas1[i].x < -ofGetWidth() / 2 + (ofGetWidth() / (numPart - 1))*i)
					particulas1[i].x += 5;
				else
					particulas1[i].x -= 5;
			}
			if (particulas1[0].x < -ofGetWidth() / 2 + 2) {
				iniciaOpa01b = true;
				partInPos = true;
			}
		}
		else {
			if (contador < 50)
				contador++;
			if (contador == 50) {
				if (escala01 < 1)
					escala01 += 0.025;
				if (!cambia01) {
					if (opa01b < 255)
						opa01b++;
				}
			}
		}
		for (int i = 0; i < numPart - 2; i++) {
			particulas1[i].set(particulas1[i].x, valSensor1[i] * 150 * escala01, 0);
		}
		//ofLogNotice("Val Sensor 1 [5]" + ofToString(ofMap(valSensor1[numPart - 1], 0, 20, 0, 1) * 150 * escala01));
		//pulso
		particulas1[numPart - 2].set(
			particulas1[numPart - 2].x,
			int(ofMap(valSensor1[numPart - 2], 0, 255, 0, 1) * 150 * escala01),
			0);
		//gsr
		particulas1[numPart - 1].set(
			particulas1[numPart - 1].x,
			ofMap(valSensor1[numPart - 1], 0, 20, 0, 1) * 150 * escala01,
			0);
		

		break;
	}
	// Switch al cambiar de escena o contenido
	if (cambia01) {
		switch (esc01) {
		case 0:
			if (opa01 > 0)
				opa01 -= velOpa;
			if (opa01 == 0) {
				esc01++;
				cambia01 = false;
			}
			break;
		case 1:
			if (opa01 == 255) {
				if (escala01 > 0)
					escala01 -= 0.005;
				if (escala01 < 0.01) {
					esc01++;
					cambia01 = false;
				}
			}
			break;
		case 2:
			if (opa01 > 0)
				opa01 -= velOpa;
			if (opa01b > 0)
				opa01b -= velOpa;
			if (opa01 == 0 && opa01b == 0) {
				iniciaOpa01b = false;
				partInPos = false;
				escena++;
				//escenas = escena;
				cambia01 = false;
			}
			break;
		}
	}
}
void ofApp::escena01() {
	// ENTENDIMIENTO // TRANQUILIDAD //
	ofEnableAlphaBlending();
	ofPushStyle();
	switch (esc01) {
	case 0:
		ofSetColor(255);
		/////////////////////////// CONTENIDO PARA USUARIO 1
		ofPushStyle();
		for (int i = 0; i < numSens - 2; i++) {
			ofColor c;
			c.setHsb((360 / (numSens+1)) * i, 100, 100, opa01);
			dibujaOnda(i, posIniX, ofGetHeight() - 150 - 110 * i, valSensor1[i], c);
		}
		for (int i = numSens - 2; i < numSens; i++) {
			posActY1[i - numSens + 2] = ofGetHeight() - 150 - 110 * i;
			valOnda1 = valSensor1[i];
			ofColor c;
			c.setHsb((360 / (numSens + 1)) * i, 100, 100, opa01);
			dibujaOnda(i, posIniX, ofGetHeight() - 150 - 110 * i, posPrevY1[i - numSens + 2], valOnda1, c);
			valOnda1 = 0;
		}
		posPrevY1[0] = valSensor1[numSens-2];
		posPrevY1[1] = valSensor1[numSens-1];
		ofPopStyle();
		museConectado(ofGetWidth() / 2 - 350, 60, 1);
		// Gyro y Acc
		dibujaOrientaciones(ofGetWidth() / 2 - 200, 100, accX1, accY1, accZ1, ofColor(0, 204, 204), "Acelerometro");
		dibujaOrientaciones(ofGetWidth() / 2 - 100, 100, gyroX1, gyroY1, gyroZ1, ofColor(204, 0, 0), "Giroscopio");
		/////////////////////////// CONTENIDO PARA USUARIO 1

		/////////////////////////// CONTENIDO EN ESPEJO PARA USUARIO 2
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2 - posIniX/2, 0, 0);
		ofPushStyle();
		for (int i = 0; i < numSens - 2; i++) {
			ofColor c;
			c.setHsb((360 / (numSens + 1)) * i, 100, 100, opa01);
			dibujaOnda(i + numSens, posIniX, ofGetHeight() - 150 - 110 * i, valSensor2[i], c);
		}
		for (int i = numSens - 2; i < numSens; i++) {
			posActY1[i - numSens + 2] = ofGetHeight() - 150 - 110 * i;
			valOnda2 = valSensor2[i];
			ofColor c;
			c.setHsb((360 / (numSens + 1)) * i, 100, 100, opa01);
			//dibujaOnda(i + numSens, posIniX, ofGetHeight() - 150 - 110 * i, posPrevY2[i - numSens + 2], valOnda2, c);
			dibujaOnda(i + numSens, posIniX, ofGetHeight() - 150 - 110 * i, posPrevY2[i - numSens + 2], valOnda2, c);

		}
		posPrevY2[0] = valSensor2[numSens - 2];
		posPrevY2[1] = valSensor2[numSens - 1];
		ofPopStyle();
		museConectado(400, 60, 1);
		// Gyro y Acc
		//ofTranslate(-ofGetWidth() / 2, 0, 0);
		dibujaOrientaciones(250, 100, accX2, accY2, accZ2, ofColor(0, 204, 204), "Acelerometro");
		dibujaOrientaciones(150, 100, gyroX2, gyroY2, gyroZ2, ofColor(204, 0, 0), "Giroscopio");
		ofPopMatrix();
		break;
	case 1: // HEXÁGONOS
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
		/////////////////////////////////////////////
		/////////////// USUARIO 1
		/////////////////////////////////////////////
		ofPushMatrix();
		ofRotateX(accX1 * multRotaciones);
		ofRotateY(-multRotaciones + accZ1 * multRotaciones);
		ofRotateZ(accY1 * multRotaciones);
		// Dibujo hexagonos con relleno
		ofSetColor(255, opa01 / anillos);
		ofFill();
		//////////
		ofSetPolyMode(OF_POLY_WINDING_NONZERO);
		for (int j = 0; j < anillos; j++) {
			ofBeginShape();
			for (int i = 0; i < numPart-1; i++) {
				ofVertex(
					particulas1[i].x*((1 + j)*.08),
					particulas1[i].y*((1 + j)*.08),
					sin(i + j*anillos + ofGetElapsedTimeMillis()*.001) * 20
				);
			}
			ofEndShape();
		}
		// Dibujo Hexagonos sin relleno
		for (int j = 0; j < anillos; j++) {
			ofSetColor(0, opa01 - j * 15);
			ofNoFill();
			ofBeginShape();
			for (int i = 0; i < numPart-1; i++) {
				ofVertex(
					particulas1[i].x*((1 + j)*.08),
					particulas1[i].y*((1 + j)*.08)
				);
			}
			ofEndShape();
		}
		// Dibujo elipses
		ofSetColor(255, opa01);
		ofFill();
		for (int j = 0; j < anillos; j++) {
			for (int i = 0; i < numPart-1; i++) {
				ofEllipse(
					particulas1[i].x*((1 + j)*.08),
					particulas1[i].y*((1 + j)*.08),
					(anillos - j) / 2, (anillos - j) / 2);
			}
		}
		ofPopMatrix();
		/////////////////////////////////////////////
		/////////////// USUARIO 2
		/////////////////////////////////////////////
		ofPushMatrix();
		ofRotateX(90 + accX2 * multRotaciones);
		ofRotateY(-multRotaciones + accZ2 * multRotaciones);
		ofRotateZ(accY2 * multRotaciones);
		// Dibujo hexagonos con relleno
		ofSetColor(255, opa01 / anillos);
		ofFill();
		//////////
		ofSetPolyMode(OF_POLY_WINDING_NONZERO);
		for (int j = 0; j < anillos; j++) {
			ofColor c;
			c.setHsb((360 / (numSens + 1)) * j, 100, 100, opa01 / anillos);
			ofFill();
			ofBeginShape();
			for (int i = 0; i < numPart-1; i++) {
				ofVertex(
					particulas2[i].x*((1 + j)*.08),
					particulas2[i].y*((1 + j)*.08),
					sin(i + j*anillos + ofGetElapsedTimeMillis()*.001) * 20
				);
			}
			ofEndShape();
		}
		// Dibujo Hexagonos sin relleno
		for (int j = 0; j < anillos; j++) {
			ofSetColor(0, opa01 - j * 15);
			ofNoFill();
			ofBeginShape();
			for (int i = 0; i < numPart-1; i++) {
				ofVertex(
					particulas2[i].x*((1 + j)*.08),
					particulas2[i].y*((1 + j)*.08)
				);
			}
			ofEndShape();
		}
		
		// Dibujo elipses
		ofSetColor(255, opa01);
		ofFill();
		for (int j = 0; j < anillos; j++) {
			for (int i = 0; i < numPart-1; i++) {
				ofEllipse(
					particulas2[i].x*((1 + j)*.08),
					particulas2[i].y*((1 + j)*.08),
					(anillos - j) / 2, (anillos - j) / 2);
			}
		}
		ofPopMatrix();

		ofPopMatrix();
		break;

	case 2:
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
		ofSetColor(255, opa01);
		ofFill();
		for (int i = 0; i < numPart; i++) {
			ofEllipse(
				particulas1[i].x,
				particulas1[i].y,
				5, 5);
		}
		if (iniciaOpa01b) {
			ofPushStyle();
			ofSetColor(255, opa01b / anillos);
			for (int j = 0; j < anillos; j++) {
				ofBeginShape();
				ofVertex(ofGetWidth() / 2, ofGetHeight() / 2);
				ofVertex(-ofGetWidth() / 2, ofGetHeight() / 2);
				for (int i = 0; i < numPart-1; i++) {
					ofVertex(particulas1[i].x, particulas1[i].y + 25 * j, sin(i + j*anillos + ofGetElapsedTimeMillis()*.001) * 20
					);
				}
				ofEndShape();
			}
			for (int j = 0; j < anillos; j++) {
				ofSetColor(0, opa01b - j * 15);
				ofNoFill();
				ofBeginShape();
				for (int i = 0; i < numPart-1; i++) {
					ofVertex(particulas1[i].x, particulas1[i].y + 25 * j);
				}
				ofEndShape();
			}
			ofPopStyle();
		}
		ofPopMatrix();
		break;
	}
	ofPopStyle();
	ofDisableAlphaBlending();
}
void ofApp::dibujaLineas(int pX, int pY) {
	ofPushStyle();
	ofSetColor(colLine, opa01);
	ofNoFill();
	ofSetLineWidth(1);
	for (int i = 0; i < 6; i++) { // LINEAS VERTICALES
		ofLine(pX + (ondasFbo[0].getWidth() / 5)*i, pY + 30, pX + (ondasFbo[0].getWidth() / 5)*i, pY + 70);
	}
	ofLine(pX, pY + 50, pX + ondasFbo[0].getWidth(), pY + 50); // LINEA HORIZONTAL
	ofPopStyle();
}
void ofApp::dibujaOnda(int indice, int pX, int pY, float val, ofColor col) {
	ofPushStyle();
	ondasFbo[indice].begin();
	ofSetColor(col, opa01 - val * 50);
	ofFill();
	ofEllipse(posOndaX, 50 + ofMap(val, 0, 1, 25, -25), 1 + 8 * val, 1 + 8 * val);
	ondasFbo[indice].end();
	ondasFbo[indice].draw(pX, pY);
	//////////////////////
	ofSetColor(col, opa01);
	ofFill();
	if (indice<numSens)
		texto1.drawString(sensor[indice], pX, pY);
	else
		texto1.drawString(sensor[indice - numSens], pX, pY);
	dibujaLineas(pX, pY);
	ofPopStyle();
}
void ofApp::dibujaOnda(int indice, int pX, int pY, int ppYprev, float val, ofColor col) {
	ofPushStyle();
	ondasFbo[indice].begin();
	ofSetLineWidth(3);
	ofSetColor(col, opa01);// -val * 50);
	ofFill(); 
	if (indice == 5 || indice == 5 + numSens) {
		ofLine(posOndaX, 50 + ofMap(val, 0, 255, 25, -25), posOndaX - 1, 50 + ofMap(ppYprev, 0, 255, 25, -25));
	}
	else {
		ofLine(posOndaX, 50 + ofMap(val, 0, 10, 25, -25), posOndaX - 1, 50 + ofMap(ppYprev, 0, 10, 25, -25));
	}
	ondasFbo[indice].end();
	ondasFbo[indice].draw(pX, pY);
	//////////////////////
	ofSetColor(col, opa01);
	ofFill();
	if (indice<numSens)
		texto1.drawString(sensor[indice], pX, pY);
	else
		texto1.drawString(sensor[indice - numSens], pX, pY);
	dibujaLineas(pX, pY);
	ofPopStyle();
}
//--------------------------------------------------------------
/////////////// ESCENA 02
///////////////////////////// Expectativa
void ofApp::setupEsc02() {
	// ESC 02 /////////////////////////
	sep2X = ofGetWidth() / (numPart2X - 1);
	sep2Y = ofGetHeight() / (numPart2Y - 1);

	for (int i = 0; i < 6; i++) {
		sensorPosiciones[i] = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
		velSensores[i] = ofVec2f(0, 0);
	}

	for (int j = 0; j < numPart2Y; j++) {
		for (int i = 0; i < numPart2X; i++) {
			nodos[i + j*numPart2X] = ofVec3f(sep2X*i, sep2Y*j, 0);
			tamNodos[i + j*numPart2X] = 5.0f;
		}
	}

	numPart02 = numPart2X*numPart2Y; // cambiar variable a setup
	incCol02 = 125 / numPart02;

	superficie02.setMode(OF_PRIMITIVE_TRIANGLES);
	for (int j = 0; j < numPart2Y; j++) {
		for (int i = 0; i < numPart2X; i++) {
			superficie02.addVertex(ofPoint(nodos[i + j*numPart2X]));
			superficie02.addColor(ofColor(125 + incCol02*(i + j*numPart2X)));
			//superficie02.addColor(ofColor((1 / (numPart2X*numPart2Y))*i + j*numPart2X));
		}
	}
	for (int j = 0; j < numPart2Y - 1; j++) {
		for (int i = 0; i < numPart2X - 1; i++) {
			superficie02.addIndex(i + j*numPart2X);
			superficie02.addIndex((i + 1) + j*numPart2X);
			superficie02.addIndex(i + (j + 1)*numPart2X);

			superficie02.addIndex((i + 1) + j*numPart2X);
			superficie02.addIndex((i + 1) + (j + 1)*numPart2X);
			superficie02.addIndex(i + (j + 1)*numPart2X);
		}
	}
}
void ofApp::escena02() {
	myCam.begin();
	ofPushMatrix();
	ofRotateX(180 - rotaParts * 50);

	if (gira2)
		ofRotateZ(rota360);

	ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2, -300);

	if (mallaSrf) {
		ofPushStyle();
		if (ampNodo02 < 1)
			ampNodo02 += 0.0125;
		for (int j = 0; j < numPart2Y; j++) {
			for (int i = 0; i < numPart2X; i++) {
				superficie02.setVertex(i + j*numPart2X, nodos[i + j*numPart2X]);
				if(escena<=4)
					superficie02.setColor(i + j*numPart2X, ofColor(colNodo02[i + j*numPart2X] * ampNodo02, alphaSrf02));
				else if (escena == 5) {
					superficie02.setColor(i + j*numPart2X, ofColor(cSrfR, cSrfG ,cSrfB, cSrfA));
				}
			}
		}
		superficie02.drawFaces();
		ofPopStyle();
	}
	/*else
		ampNodo02 = 0;
		*/
	if(ejes02){
		if (colEjes02 < ejesGral)
			colEjes02 += 0.25;
		else if (colEjes02 > ejesGral)
			colEjes02 -= 0.25;

		if (escena != 6) {
			ejesGral = 100;
		}
		else {
			ejesGral = 255;
		}

		for (int j = 0; j < numPart2Y; j++) {
			for (int i = 0; i < numPart2X; i++) {
				superficie02.setColor(i + j*numPart2X, ofColor(colEjes02));
				superficie02.setVertex(i + j*numPart2X, nodos[i + j*numPart2X]);
			}
		}
		superficie02.drawWireframe();
	}
	else
		colEjes02 = 0;
	
	if (puntos02) {
		ofPushStyle();
		if (colPuntos02 < 255)
			colPuntos02 += 0.25;

		if (escena == 2) {
			c = ofColor(255, 255, 255, colPuntos02);
		} else if (escena == 3) {
			if (!cambiaColorNodo03) {
				c = ofColor(255, 255, 255, colPuntos02);
			}
			else {
				if (colRed < 255) {
					colRed += 0.25;
				}
			}
		}

		for (int j = 0; j < numPart2Y; j++) {
			for (int i = 0; i < numPart2X; i++) {
				if (cambiaColorNodo03 && escena == 3) {
					if (colRed < 255) {
						c = ofColor(255, 255 - colRed, 255 - colRed);
					}
					else {
						c = ofColor(ofNoise(ofGetElapsedTimeMillis()*.001 + i + j*numPart2X)*colRed, 0, 0);
					}
				}

				ofSetColor(c);
				ofFill();

				if (switchEllipse) {
					ofEllipse(nodos[i + j*numPart2X].x, nodos[i + j*numPart2X].y, nodos[i + j*numPart2X].z, tamNodos[i + j*numPart2X], tamNodos[i + j*numPart2X]);
				}
				else {
					if (i % 2 == 0 && j % 2 == 0)
						ofEllipse(nodos[i + j*numPart2X].x, nodos[i + j*numPart2X].y, nodos[i + j*numPart2X].z, tamNodos[i + j*numPart2X], tamNodos[i + j*numPart2X]);
				}
			}
		}
		ofPopStyle();
	}
	else
		colPuntos02 = 0;
		
	ofPopMatrix();
	myCam.end();
	
	if (dibujaPosiciones) {
		ofPushStyle();
		for (int j = 0; j < numSens; j++) {
			ofColor cL;
			cL.setHsb((360 / (numSens + 1)) * j, 100, 100, opa02);
			ofSetColor(cL);
			ofFill();
			ofEllipse(sensorPosiciones[j].x, sensorPosiciones[j].y, 20, 20);
		}
		ofPopStyle();
	}
}
//--------------------------------------------------------------
void ofApp::updateEsc02() {
	if (debug) {
		ofLogNotice(ofToString(cuenta02));
	}
	if (entra02) {
		if (opa02 < 255)
			opa02 += 0.25;
	}
	else {
		if (opa02 > 0)
			opa02 -= 0.25;
		if (opa02 == 0)
			dibujaPosiciones = false;
	}

	if(opa02>254)
		cuenta02++;
	if (autom02) {
		if (cuenta02 > 300 && cuenta02 < 320) {
			puntos02 = true;
		}
		else if (cuenta02 > 850 && cuenta02 < 870) {
			ejes02 = true;
		}
		else if (cuenta02 > 1900 && cuenta02 < 1920) {
			apagaMalla = false;
			dibujaPosiciones = false;
		}
		else if (cuenta02 > 2300 && cuenta02 < 2310) {
			cambiaRadios02 = true;
			camara02 = true;
		}

		if (cambiaRadios02) {
			if (velMult < 10) {
				if (ofGetFrameNum() % 60 == 0) {
					velMult++;
				}
			}

			dist02 = 170 + sin(ofGetElapsedTimeMillis()*.0001) * 150;
			if (ofGetFrameNum() % 650 == 0)
				switchEllipse = !switchEllipse;
		}
		
	}
	for (int i = 0; i < numSens; i++) {
		if (i == numSens - 2) {
			valSensor1[i] = ofMap(valSensor1[i], 0, 255, 0.1, 2);
			valSensor2[i] = ofMap(valSensor2[i], 0, 255, 0.1, 2);
		}
		else if (i == numSens - 1) {
			valSensor1[i] = ofMap(valSensor1[i], 0, 10, 0, 2);
			valSensor2[i] = ofMap(valSensor2[i], 0, 10, 0, 2);
		}

		if (direcciones2X[i]) {
			velSensores[i].x = valSensor1[i] * velMult;
		}
		else {
			velSensores[i].x = -valSensor1[i] * velMult;
		}
		
		///// Cambiar al sensor 2 movimiento en X lo da un sensor y movimiento en Y lo dará el segundo
		if (direcciones2Y[i]) {
			velSensores[i].y = valSensor2[i] * velMult;
		}
		else {
			velSensores[i].y = -valSensor2[i] * velMult;
		}

		sensorPosiciones[i].set(sensorPosiciones[i].x + velSensores[i].x, sensorPosiciones[i].y + velSensores[i].y);

		// Invertir las direcciones al tener colisión
		if (sensorPosiciones[i].x > ofGetWidth() || sensorPosiciones[i].x < 0) {
			direcciones2X[i] = !direcciones2X[i];
			cuentaFueraPantalla[i]++;
		}

		if (sensorPosiciones[i].y > ofGetHeight() || sensorPosiciones[i].y < 0) {
			direcciones2Y[i] = !direcciones2Y[i];
			cuentaFueraPantalla[i]++;
		}
		if (cuentaFueraPantalla[i] > 30) {
			sensorPosiciones[i].x = ofGetWidth() / 2;
			sensorPosiciones[i].y = ofGetHeight() / 2;
			cuentaFueraPantalla[i] = 0;
		}
	}
	ofSetCircleResolution(30);
	for (int j = 0; j < numPart2Y; j++) {
		for (int i = 0; i < numPart2X; i++) {
			// estados al estar cerca de un nodo
			for (int k = 0; k < numSens; k++) {////////////////////////////////////////
				int distancia = ofDist(nodos[i + j*numPart2X].x, nodos[i + j*numPart2X].y, sensorPosiciones[k].x, sensorPosiciones[k].y);
				
				if (distancia < dist02) {
					tamNodos[i + j*numPart2X] = ofMap(distancia, 0, dist02, 50, 5);
					if (!invertir02) {
						nodos[i + j*numPart2X].z = distancia;
					}
					else {
						nodos[i + j*numPart2X].z = -distancia;
					}
				}
				
				if (distancia > 1 && distancia < dist02) {
					colNodo02[i + j*numPart2X] = distancia;
				}
			}

			// regreso progresivo a su estado inicial
			if (tamNodos[i + j*numPart2X] > 5)
				tamNodos[i + j*numPart2X] -= 0.5;

			if (!invertir02) {
				if (nodos[i + j*numPart2X].z < 0)
					nodos[i + j*numPart2X].z++;
			}
			else {
				if (nodos[i + j*numPart2X].z > 0)
					nodos[i + j*numPart2X].z--;
			}

			if (colNodo02[i + j*numPart2X] < 125 + incCol02*(i + j*numPart2X))
				colNodo02[i + j*numPart2X]++;
			else
				colNodo02[i + j*numPart2X]--;

		}
	}
}
/////////////// ESCENA 03
///////////////////////////// MIEDO
void ofApp::escena03() {
	escena02();
}
void ofApp::updateEsc03() {
	cuenta03++;
	if (cuenta03 < 15) {
		ofSetSphereResolution(4);
		ejes02 = false;
		puntos02 = true; 
		fondo03 = true;
		cambiaColorNodo03 = true;
		apagaMalla = true;
	}
	else if (cuenta03 > 1500 && cuenta03 < 1550) {
		ajusta03 = false;
	}
	else if (cuenta03 > 1750 && cuenta03 < 1760) {
		ejes02 = true;
	}
	else if (cuenta03 > 2100 && cuenta03 < 2120) {
		cambiaTamNodo03 = true;
	}
	else if (cuenta03 > 2300 && cuenta03 < 2320) {	
		ejes02 = false;
	}

	if (fondo03) {
		if (valSensor1[5] > 200 || valSensor2[5] > 200) {
			ofBackground(205, 0, 0);
		}
		else {
			ofBackground(0);
		}
	}

	switchEllipse = true;

	int radio02 = 500;
	
	int theta = 360 / numPart2X;
	int phi = 360 / numPart2Y;
	float mil03 = ofGetElapsedTimeMillis();
	if (ajusta03) {
		for (int j = 0; j < numPart2Y; j++) {
			for (int i = 0; i < numPart2X; i++) {
				nodosTemp[i + j*numPart2X].x = ofGetWidth() / 2 + (sin(phi*j)*cos(theta*i))*radio02;
				nodosTemp[i + j*numPart2X].y = ofGetHeight() / 2 + (sin(phi*j)*sin(theta*i))*radio02;
				nodosTemp[i + j*numPart2X].z = radio02/2+cos(theta*j)*radio02;

				if (nodos[i + j*numPart2X].x > nodosTemp[i + j*numPart2X].x)
					nodos[i + j*numPart2X].x--;
				else
					nodos[i + j*numPart2X].x++;
				if (nodos[i + j*numPart2X].y > nodosTemp[i + j*numPart2X].y)
					nodos[i + j*numPart2X].y--;
				else
					nodos[i + j*numPart2X].y++;
				if (nodos[i + j*numPart2X].z > nodosTemp[i + j*numPart2X].z)
					nodos[i + j*numPart2X].z--;
				else
					nodos[i + j*numPart2X].z++;
			}
		}
	}
	else {
		camara02 = false;
		for (int j = 0; j < numPart2Y; j++) {
			for (int i = 0; i < numPart2X; i++) {
				nodos[i + j*numPart2X].x = ofGetWidth() / 2 + (sin(phi*j)*cos(theta*i))*(radio02 + (ofNoise(mil03*0.001+i+j*numPart2X)*120));
				nodos[i + j*numPart2X].y = ofGetHeight() / 2 + (sin(phi*j)*sin(theta*i))*(radio02 + ofNoise(mil03 + i + j*numPart2X)*20);
				nodos[i + j*numPart2X].z = cos(theta*j)*(radio02+sin(mil03*.001 + i + j*numPart2X)*50);
			}
		}
	}
	for (int i = 0; i < numSens; i++) {
		if (i == numSens - 2) {
			valSensor1[i] = ofMap(valSensor1[i], 0, 255, 0.1, 2);
			valSensor2[i] = ofMap(valSensor2[i], 0, 255, 0.1, 2);
		}
		else if (i == numSens - 1) {
			valSensor1[i] = ofMap(valSensor1[i], 0, 10, 0, 2);
			valSensor2[i] = ofMap(valSensor2[i], 0, 10, 0, 2);
		}

		if (direcciones2X[i]) {
			velSensores[i].x = valSensor1[i] * velMult;
		}
		else {
			velSensores[i].x = -valSensor1[i] * velMult;
		}

		///// Cambiar al sensor 2 movimiento en X lo da un sensor y movimiento en Y lo dará el segundo
		if (direcciones2Y[i]) {
			velSensores[i].y = valSensor2[i] * velMult;
		}
		else {
			velSensores[i].y = -valSensor2[i] * velMult;
		}

		sensorPosiciones[i].set(sensorPosiciones[i].x + velSensores[i].x, sensorPosiciones[i].y + velSensores[i].y);

		// Invertir las direcciones al tener colisión
		if (sensorPosiciones[i].x > ofGetWidth() || sensorPosiciones[i].x < 0) {
			direcciones2X[i] = !direcciones2X[i];
			cuentaFueraPantalla[i]++;
		}

		if (sensorPosiciones[i].y > ofGetHeight() || sensorPosiciones[i].y < 0) {
			direcciones2Y[i] = !direcciones2Y[i];
			cuentaFueraPantalla[i]++;
		}
		if (cuentaFueraPantalla[i] > 30) {
			sensorPosiciones[i].x = ofGetWidth() / 2;
			sensorPosiciones[i].y = ofGetHeight() / 2;
			cuentaFueraPantalla[i] = 0;
		}
	}
	// NODOS
	if (cambiaTamNodo03) {
		for (int j = 0; j < numPart2Y; j++) {
			for (int i = 0; i < numPart2X; i++) {
				tamNodos[i + j*numPart2X] = 1 + abs(ofNoise(ofGetFrameNum()*(i + j*numPart2X) + ofGetElapsedTimeMillis()*.0015) * 25);
			}
		}
	}
}
/////////////// ESCENA 04
///////////////////////////// ASOMBRO
void ofApp::escena04() {
	escena02();
}
void ofApp::updateEscena04() {
	if (cuenta04 == 0) {
		camara02 = false;
		cambiaColorNodo03 = false;
	}
	else if (cuenta04 < 600) {
		if (c.r > 0)
			c.r -= 1;
		if (c.g > 0)
			c.g -= 1;
		if (c.b < 255)
			c.b += 1;
		if (c.a > 110)
			c.a--;
	}
	else if (cuenta04 == 601) {
		switchAlpha = true;
	}
	else if (cuenta04 > 700 && cuenta04 < 710) {
		if (!alphaEncendido)
			alphaEncendido;
			noiseSrf = true;
	}
	else if (cuenta04 > 800 && cuenta04 < 1810) {
		if (ofGetFrameNum() % 60 == 0) {
			camara02 = !camara02;
			reset04 = true;
			c.r = ofRandom(255);
			c.b = ofRandom(255);
			c.g = ofRandom(255);
		}
	}
	else if (cuenta04 == 2480) {
		camara02 = true;
		switchAlpha = true;
	}
	else if (cuenta04 > 2600 && escena == 4) {
		c.a = 255;
		c.r = ofMap((valSensor1[0] + valSensor2[0]), 0, 2, 0, 255);
		c.g = ofMap((valSensor1[1] + valSensor2[1]), 0, 2, 0, 255);
		c.b = ofMap((valSensor1[4] + valSensor2[4]), 0, 2, 0, 255);
		if (valSensor1[5] > 200) {
			cuentaPulsos++;
		}
		if (escena == 4) {
			if (cuentaPulsos > 2) {
				ejes02 = !ejes02;
				cuentaPulsos = 0;
			}
		}
	} 

	if (escena == 5) {
		cuenta05++; 		
		if(cuenta05<20)
			ejes02 = true;
		else if (cuenta05 > 300 && cuenta05 < 310) {
			camara02 = false;
			mallaSrf = true;
			apagaMalla = false;
		}
		if(ofGetFrameNum()%120)
			maxNoise = ofRandom(-1350, 2500);

	/*	if (alphaSrf02 != 255) {
			if (alphaSrf02 < 254)
				alphaSrf02++;
		}
		*/
		if (c.r > 0)
			c.r *= 0.995;
		if (c.g > 0)
			c.g *= 0.995;
		if (c.b > 0)
			c.b *= 0.995;
	}

	if (noiseSrf) {
		if (escena == 4){
			if (tamNoise < maxNoise) 
				tamNoise += 0.125;
		}
		else if (escena == 5) {
			if (tamNoise < maxNoise)
				tamNoise *= 1.01;
			else
				tamNoise *= 0.99;
		}
	}

	if (escena == 4)
		cuenta04++;
	else
		cuenta04 = 0;

	for (int j = 0; j < numPart2Y; j++) {
		for (int i = 0; i < numPart2X; i++) {
			if (reset04) {
				nodosTemp[i + j*numPart2X] = ofVec3f(sep2X*i, sep2Y*j, 0);
				reset04 = false;
			}
			if (noiseSrf) {
				if (escena == 4) {
					nodos[i + j*numPart2X] = ofVec3f(
						sep2X*i, 
						sep2Y*j*1.75, 
						ofNoise(ofGetElapsedTimeMillis()*velNoise + i + j*numPart2X) * tamNoise);
					tamNodos[i + j*numPart2X] = ofNoise(ofGetElapsedTimeMillis()*.0005 + i + j*numPart2X) * 15;
				}
				else if (escena == 5){
					if(colNodo02[i + j*numPart2X]<255)
						colNodo02[i + j*numPart2X]++;

					if (valSin05 < 50)
						valSin05 *= 1.005;
					nodos[i + j*numPart2X] = ofVec3f(
						sep2X*i,
						sep2Y*j*1.75,
						sin(ofGetElapsedTimeMillis()*0.0005 + (360 / numPart2X)*i) * valSin05 + cos(ofGetElapsedTimeMillis()*0.005 + (360 / numPart2Y)*j) * valSin05 + ofNoise(ofGetElapsedTimeMillis()*velNoise + i + j*numPart2X) * tamNoise);
					tamNodos[i + j*numPart2X] = ofNoise(ofGetElapsedTimeMillis()*.0000005 + i + j*numPart2X) * (25+valSensor1[2]*5+valSensor2[2]*5);
				}
			}
			else {
				nodosTemp[i + j*numPart2X] = ofVec3f(sep2X*i, sep2Y*j, 0);

				if (nodos[i + j*numPart2X].x > nodosTemp[i + j*numPart2X].x)
					nodos[i + j*numPart2X].x--;
				else
					nodos[i + j*numPart2X].x++;
				if (nodos[i + j*numPart2X].y > nodosTemp[i + j*numPart2X].y)
					nodos[i + j*numPart2X].y--;
				else
					nodos[i + j*numPart2X].y++;
				if (nodos[i + j*numPart2X].z > nodosTemp[i + j*numPart2X].z)
					nodos[i + j*numPart2X].z--;
				else
					nodos[i + j*numPart2X].z++;


				if (escena == 5) {
					if (cSrfR < 255)
						cSrfR += 0.5;
					if (cSrfG < 255)
						cSrfG += 0.5;
					if (cSrfB < 255)
						cSrfB += 0.5;
					if (cSrfA < 255)
						cSrfA += 0.5;
				}
			}
		}
	}
}
/////////////// ESCENA 05
///////////////////////////// Euforia
void ofApp::escena05() {
	escena02();
}
/////////////// ESCENA 06
///////////////////////////// Tristeza / Soledad
void ofApp::escena06() {

}
/////////////// ESCENA 07
///////////////////////////// Abismo
void ofApp::escena07() {

}
/////////////// ESCENA 08
///////////////////////////// Felicidad
void ofApp::escena08() {

}
/////////////// ESCENA 09
///////////////////////////// Reconocimiento
void ofApp::escena09() {

}
/////////////// ESCENA 10
///////////////////////////// Proximidad
void ofApp::escena10() {

}

//////// Funcion para Gyro y Acc
void ofApp::dibujaOrientaciones(int pX, int pY, float rX, float rY, float rZ, ofColor col, string texto) {
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(pX, pY, 0);
	if (texto == "Acelerometro") {
		ofRotateX(-200 + rX * 90);
		ofRotateZ(-rY * 90);
		ofRotateY(90-rZ * 90);
	}
	else {
		ofRotateX(-200 + rX * 0.1);
		ofRotateZ(rY * 0.1);
		ofRotateZ(rZ * 0.1);
	}

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

	ofSetColor(col, opa01/8);
	ofFill();
	ofBox(50);
	ofSetColor(255, opa01);
	ofNoFill();
	ofBox(50);
	ofPopMatrix();
	texto1.drawString(texto, pX-45, pY + 70);
	ofPopStyle();
}
//////// Funcion muse conectado
void ofApp::museConectado(int pX, int pY, int numS) {
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(pX, pY);
	if (numS == 1) {
		if (museOn1) {
			ofSetColor(64, 255, 0, opa01);
			ofFill();
			ofRect(0, 0, 10, 10);

			ofSetColor(255, opa01);
			ofNoFill();
			ofRect(0, 0, 10, 10);
		}
		if (blink1) {
			ofSetColor(64, 255, 0, opa01);
			ofFill();
			ofRect(0, 20, 10, 10);

			ofSetColor(255, opa01);
			ofNoFill();
			ofRect(0, 20, 10, 10);
		}
		if (jawClench1) {
			ofSetColor(64, 255, 0, opa01);
			ofFill();
			ofRect(0, 40, 10, 10);

			ofSetColor(255, opa01);
			ofNoFill();
			ofRect(0, 40, 10, 10);
		}
		if (isGood) {
			ofSetColor(64, 255, 0, opa01);
			ofFill();
			ofRect(30, 0, EEG11 * 50, 10);
			ofRect(30, 20, EEG21 * 50, 10);
			ofRect(30, 40, EEG31 * 50, 10);
			ofRect(30, 60, EEG41 * 50, 10);
			ofRect(30, 80, auxLeft1 * 50, 10);
			ofRect(30, 100, auxRight1 * 50, 10);
			ofSetColor(255, opa01);
			ofNoFill();
			ofRect(30, 0, 50, 10);
			ofRect(30, 20, 50, 10);
			ofRect(30, 40, 50, 10);
			ofRect(30, 60, 50, 10);
			ofRect(30, 80, 50, 10);
			ofRect(30, 100, 50, 10);
		}
	}
	else if (numS == 2) {
		if (museOn2) {
			ofSetColor(64, 255, 0, opa01);
			ofFill();
			ofRect(0, 0, 10, 10);

			ofSetColor(255, opa01);
			ofNoFill();
			ofRect(0, 0, 10, 10);
		}
		if (blink2) {
			ofSetColor(64, 255, 0, opa01);
			ofFill();
			ofRect(0, 20, 10, 10);

			ofSetColor(255, opa01);
			ofNoFill();
			ofRect(0, 20, 10, 10);
		}
		if (jawClench2) {
			ofSetColor(64, 255, 0, opa01);
			ofFill();
			ofRect(0, 40, 10, 10);

			ofSetColor(255, opa01);
			ofNoFill();
			ofRect(0, 40, 10, 10);
		}
		if (isGood) {
			ofSetColor(64, 255, 0, opa01);
			ofFill();
			ofRect(30, 0, EEG12 * 50, 10);
			ofRect(30, 20, EEG22 * 50, 10);
			ofRect(30, 40, EEG32 * 50, 10);
			ofRect(30, 60, EEG42 * 50, 10);
			ofRect(30, 80, auxLeft2 * 50, 10);
			ofRect(30, 100, auxRight2 * 50, 10);
			ofSetColor(255, opa01);
			ofNoFill();
			ofRect(30, 0, 50, 10);
			ofRect(30, 20, 50, 10);
			ofRect(30, 40, 50, 10);
			ofRect(30, 60, 50, 10);
			ofRect(30, 80, 50, 10);
			ofRect(30, 100, 50, 10);
		}
	}
	ofPopMatrix();
	ofPopStyle();
}
//////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if(key=='!')
		ofSetWindowPosition(ofGetWindowWidth(), 0);
	if(key=='"')
		ofSetWindowPosition(0, 0);
	if (key == 'd' || key == 'D')
		debug = !debug;
	if (key == 'g' || key == 'G')
		showGui = !showGui;
	if (key == 'e' || key == 'E')
		emularSensores = !emularSensores;
	if (key == 'h' || key == 'H')
		help = !help;
	if (key == 'b' || key == 'B') {
		ofBackground(0);
	}
	if (key == 't' || key == 'T')
		titulo = !titulo;
	if (key == 'i' || key == 'I')
		isGood = !isGood;
	if (key == 's' || key == 'S')
		switchEllipse = !switchEllipse;
		//guardaFrame = !guardaFrame;
	if (key == 'f' || key == 'F'){
		fullScreenDisplay = !fullScreenDisplay;
		if(fullScreenDisplay)
			ofSetFullscreen(true);
		else
			ofSetFullscreen(false);
	}

	if (key == '0') escena = 0;
	if (key == '1') escena = 1;
	if (key == '2') escena = 2;
	if (key == '3') escena = 3;
	if (key == '4') escena = 4;
	if (key == '5') escena = 5;
	if (key == '6') escena = 6;
	if (key == '7') escena = 7;
	if (key == '8') escena = 8;
	if (key == '9') escena = 9;

	if (key == OF_KEY_LEFT) {
		escena--;
		if(escena < 0)
			escena = numEscenas - 1;
	}
	if (key == OF_KEY_RIGHT) {
		if (escena == 0) {
			if (!entraLogo)
				saleLogo = true;
		}
		else if (escena == 1) {
			cambia01 = true;
		}
		else {
			escena++;
		}
		escena = escena % numEscenas;
	}
}
///////////////////// EXIT ///////////////
void ofApp::exit() {
}
///////////////////// GUI ///////////////
void ofApp::setupGUI() {
	gui.setup();
	gui.setPosition(ofGetWidth() - 250, 50);
	gui.setName("abismo // proximo UI");
	gui.add(escenas.setup("Escena", 0, 0, 11));
	gui.add(guardaFrame.setup("Salvar Frames ", false));
	gui.add(emularSensores.setup("Emular", false));
	gui.add(radio02.setup("radio02", 300, 100, 5000));
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
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
/* NOTAS CAMARA 3d
// ofCamera myCam;
float tweenvalue = (ofGetElapsedTimeMillis() % 6000) / 6000.f; // this will slowly change from 0.0f to 1.0f, resetting every 2 seconds

ofQuaternion startQuat;
ofQuaternion targetQuat;
ofVec3f startPos;
ofVec3f targetPos;

// we define the camer's start and end orientation here:
startQuat.makeRotate(90, 0, 0, 1);			// zero rotation.
targetQuat.makeRotate(180, 0, 0, 1);			// rotation 90 degrees around y-axis.

// we define the camer's start and end-position here:
startPos.set(0, 0, 0);
targetPos.set(0, 0, 0);


ofQuaternion tweenedCameraQuaternion;	// this will be the camera's new rotation.

// calculate the interpolated orientation
tweenedCameraQuaternion.slerp(tweenvalue, startQuat, targetQuat);

ofVec3f lerpPos;					//this will hold our tweened position.

// calculate the interpolated values.
lerpPos.x = ofLerp(tweenvalue, startPos.x, targetPos.x);
lerpPos.y = ofLerp(tweenvalue, startPos.y, targetPos.y);
lerpPos.z = ofLerp(tweenvalue, startPos.z, targetPos.z);

// alternative way to calculate interpolated values:
//lerpPos = startPos + ((targetPos-startPos) * tweenvalue);

// now update the camera with the calculated orientation and position.


// myCam.setOrientation(tweenedCameraQuaternion);
// myCam.setGlobalPosition(lerpPos);
*/

