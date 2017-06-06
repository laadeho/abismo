#include "ofApp.h"
#include <ofTrueTypeFont.h>

//--------------------------------------------------------------
void ofApp::setup(){
	// listen on the given port
	//cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);
	current_msg_string = 0;
	ofSetFrameRate(60);
	ofBackground(0);
	ofEnableAlphaBlending(); // lines have the ability to draw with alpha enabled

	///// SERIAL /////
	setupSerial();

	//ofEnableSmoothing();
	//ofSetBackgroundAuto(false);
	//ofTrueTypeFont titulos;
	//titulos.setLineHeight(10);
	
	setupGUI();
	if (fullScreenDisplay)
		ofSetFullscreen(true);

	titulos.loadFont("Helvetica Bold.ttf", 20);
	texto1.loadFont("Helvetica Normal.ttf", 10);

	sensaciones[0] = "Logo";
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

	// ESC 00 /////////////////////////
	logoAbismo.load("images/abismoLogo_1240x600.png");
	setupEsc01();
	// ESC 02 /////////////////////////
	sep2X = ofGetWidth() / (numPart2X-1);
	sep2Y = ofGetHeight() / (numPart2Y-1);

	for (int i = 0; i < 6; i++) {
		sensorPosiciones[i] = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
		velSensores[i] = ofVec2f(0, 0);
	}

	for (int j = 0; j < numPart2Y; j++) {
		for (int i = 0; i < numPart2X; i++) {
			nodos[i + j*numPart2X] = ofVec3f(sep2X*i ,sep2Y*j, 0);
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
	for (int j = 0; j < numPart2Y-1; j++) {
		for (int i = 0; i < numPart2X-1; i++) {
			superficie02.addIndex(i + j*numPart2X);
			superficie02.addIndex((i + 1) + j*numPart2X);
			superficie02.addIndex(i + (j + 1)*numPart2X);

			superficie02.addIndex((i + 1) + j*numPart2X);
			superficie02.addIndex((i + 1) + (j + 1)*numPart2X);
			superficie02.addIndex(i + (j + 1)*numPart2X);

		}
	}
	/*
	ofVec2f test = ofVec2f(10, 10);
	camera.setupPerspective(true, .9, .5, 650, test);
	*/
	//myCam.disableMouseInput();
	//myCam.disableMouseMiddleButton();

	// ESC 03 /////////////////////////
	// ESC 04 /////////////////////////
	// ESC 05 /////////////////////////
	// ESC 06 /////////////////////////
	// ESC 07 /////////////////////////
	// ESC 08 /////////////////////////
	
	/*
	std::cout << "Ancho: " << ofGetScreenWidth() << endl;
	std::cout << "Alto: " << ofGetScreenHeight() << endl;
	*/
}

void ofApp::setupSerial() {
	ofSetVerticalSync(true);
	serial.listDevices();

	ofSetLogLevel(OF_LOG_VERBOSE);
	if (!serial.setup("COM3", 9600)) {
		ofLogError() << "could not open serial port - listing serial devices";
		serial.listDevices();
		//OF_EXIT_APP(0);
		cout << "==================================" << endl;
		cout << "NO HAY SERIAL" << endl;
		cout << "==================================" << endl;
	}
	else {
		serialConectado = true;
	}

	//serial.startContinuousRead();
	//ofAddListener(serial.NEW_MESSAGE,this,&testApp::onNewMessage);

	message = "";
}

//--------------------------------------------------------------
void ofApp::update() {
	if (guardaFrame) {
		captura.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		captura.save("frames/" + ofToString(ofGetFrameNum()) + ".tif");
		//ofSaveScreen("frames/"+ ofToString(ofGetFrameNum()) + ".tif");
		//ofSaveImage("frames/" + ofToString(ofGetFrameNum()) + ".tif");
	}
	if (serialConectado) {
		updateSerial();
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
				escenas = 1;
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
		for (int i = 0; i < 6; i++) {
			if (direcciones2X[i])
				velSensores[i].x = valSensor1[i]* velMult;
			else
				velSensores[i].x = -valSensor1[i]* velMult;
			///// Cambiar al sensor 2 movimiento en X lo da un sensor y movimiento en Y lo dará el segundo
			if (direcciones2Y[i])
				velSensores[i].y = valSensor1[i]* velMult;
			else
				velSensores[i].y = -valSensor1[i]* velMult;

			sensorPosiciones[i].set(sensorPosiciones[i].x+velSensores[i].x, sensorPosiciones[i].y+velSensores[i].y);

			// Invertir las direcciones al tener colisión
			if (sensorPosiciones[i].x > ofGetWidth() || sensorPosiciones[i].x < 0) {
				direcciones2X[i] =! direcciones2X[i];
			}
			if (sensorPosiciones[i].y > ofGetHeight() || sensorPosiciones[i].y < 0) {
				direcciones2Y[i] =! direcciones2Y[i];
			}
		}
		ofSetCircleResolution(30);
		for (int j = 0; j < numPart2Y; j++) {
			for (int i = 0; i < numPart2X; i++) {
				// estados al estar cerca de un nodo
				for (int k = 0; k < 6; k++) {
					int distancia = ofDist(nodos[i + j*numPart2X].x, nodos[i + j*numPart2X].y, sensorPosiciones[k].x, sensorPosiciones[k].y);
					if (distancia < dist02) {
						tamNodos[i + j*numPart2X] = ofMap(distancia, 0, dist02, 50, 5);
						if (!invertir02) {
							nodos[i + j*numPart2X].z = -distancia;
						} else {
							nodos[i + j*numPart2X].z = distancia;
						}
					}
					if (distancia > 1 && distancia < dist02) {
						colNodo02[i + j*numPart2X] = distancia;
					}
				}
				
				// regreso progresivo a su estado inicial
				if (tamNodos[i + j*numPart2X] > 5)
					tamNodos[i + j*numPart2X]-=0.5;

				if(!invertir02){
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
		////// superficie
		if (camara02) {
			if (rotaParts < 1)
				rotaParts += 0.0025;
			if (rotaParts > 0.95)
				gira2 = true;
			if (gira2) {
				rota360 += 0.25;
			}
		}
		break;
	case 3:
		break;
	default:
		break;
	}
	escena = escenas;

	updateOSC();
	/////////////// DATOS EMULADOS
	if (emularSensores) {
		artifacts = true;
		alpha = true;
		beta = true;
		gamma = true;
		delta = true;
		theta = true;

		pSensor1 = true;
		pSensor2 = true;
		gsr = true;

		acc = true;
		gyro = true;
		isGood = true;
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
	if (delta){
		valSensor1[3] = ofNoise(float(ofGetFrameNum()*.0055*(0.25 * 3 + 1)));
		valSensor2[3] = ofNoise(float(ofGetFrameNum()*.0025*(0.125 * 2.25 + 1)));
	}
	if (theta){
		valSensor1[4] = ofNoise(float(ofGetFrameNum()*.0085*(0.25 * 4 + 1)));
		valSensor2[4] = ofNoise(float(ofGetFrameNum()*.00385*(0.215 * 4.25 + 1)));
	}
	if (pulseSensor) { //////////////////////falta 2
		valSensor1[5] = ofNoise(float(ofGetFrameNum()*.0065*(0.35 * 4 + 1)));
		valSensor2[5] = ofNoise(float(ofGetFrameNum()*.00625*(0.135 * 2.4 + 1)));
	}
	if (gsr){
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

void ofApp::updateSerial(){
	if (serial.available()) {
		int myByte = 0;
		myByte = serial.readByte();
		if (debug) {
			if (myByte == OF_SERIAL_NO_DATA)
				printf("No hubo lectura Serial");
			else if (myByte == OF_SERIAL_ERROR)
				printf("Error en lectura Serial");
			else {
				printf("myByte is %d", myByte);
				cout << endl;
			}
		}

		if (myByte != 0) {
			if (myByte == 'A') { // 65 Sensor1
				pSensor1 = true;
				/*
				printf("sensor 1");
				cout << endl;
				*/
			}
			if (myByte == 'B') { // 66 Sensor2
				pSensor2 = true;
				/*
				printf("sensor 2");
				cout << endl;
				*/
			}
			////////////// de p5
			if (pSensor1) { // 20 GSR
						   // COMPROBAR SI ES 20 DEL GSR
				if (myByte == 50) // 2
					esDos = true;
				/*if (esDos && val == 48) { // 0
				esCero = true;
				} */
				if (esDos && myByte != 50 && myByte != 44) {
					if (myByte>thressGSR)
						valGSR = myByte;
					if (debug) {
						printf("Val GSR: " + valGSR);
						cout << endl;
					}
				}
			}
			if (pSensor2) {
				//////////////////////////
				// COMPROBAR SI ES 15 DEL SENSOR DE PULSO
				if (myByte == 49) // 1
					esUno = true;
				/*if (esUno && val == 53) { // 5
				esCinco = true;
				}*/
				if (esUno && myByte != 49 && myByte != 44) {
					valPulso1 = myByte;
					if (debug)
						printf("Pulso: " + myByte);
				}
				else
					valPulso1 = 0;
			}


			if (myByte == 44 && pSensor1) {
				pSensor1 = false;
				esDos = false;
				esCero = false;
			}
			if (myByte == 44 && pSensor2) {
				pSensor2 = false;
				esUno = false;
				// esCinco = false;
			}
			/////////////// de p5


			/*
			if (pulsoSensor1) {
				if (myByte == 49) {
					pulso1Dato1 = true;
				}
				if (myByte == 53) {
					pulso1Dato2 = true;
				}
				if (myByte == 3) {
					pulso1Dato3 = true;
				}
			}
			*/
			if (pulso1Dato1 && pulso1Dato2 && pulso1Dato3) {
				pulso = true;
				serial.flush();
			}
			else
				pulso = false;

			if (myByte == 2) {
				pulsoSensor1 = false;
				pulso1Dato1 = false;
				pulso1Dato2 = false;
				pulso1Dato3 = false;
			}
		}
	}

	if (pulso) {
		//red = !red; // Revisar ejemplo que hice testApp con conexion serial
		printf("PULSO");
		cout << endl;
		ofBackground(255, 0, 0);
		pulso = !pulso;
	}
	else {
		ofBackground(0);
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
		
		// std::cout << "Mensaje: " << m.getAddress() << endl;
		
		// check for mouse moved message
		if (m.getAddress() == "/alpha") {
			if(m.getArgAsInt(0)==1)
				valSensor1[0] = m.getArgAsFloat(1);
			else if (m.getArgAsInt(0) == 2)
				valSensor2[0] = m.getArgAsFloat(1);
		} else if (m.getAddress() == "/beta") {
			if (m.getArgAsInt(0) == 1)
				valSensor1[1] = m.getArgAsFloat(1);
			else if (m.getArgAsInt(0) == 2)
				valSensor2[1] = m.getArgAsFloat(1);
		} else if (m.getAddress() == "/gamma") {
			if (m.getArgAsInt(0) == 1)
				valSensor1[2] = m.getArgAsFloat(1);
			else if (m.getArgAsInt(0) == 2)
				valSensor2[2] = m.getArgAsFloat(1);
		} else if (m.getAddress() == "/delta") {
			if (m.getArgAsInt(0) == 1)
				valSensor1[3] = m.getArgAsFloat(1);
			else if (m.getArgAsInt(0) == 2)
				valSensor2[3] = m.getArgAsFloat(1);
		} else if (m.getAddress() == "/theta") {
			if (m.getArgAsInt(0) == 1)
				valSensor1[4] = m.getArgAsFloat(1);
			else if (m.getArgAsInt(0) == 2)
				valSensor2[4] = m.getArgAsFloat(1);
		}
		else if (m.getAddress() == "/accelerometer") {
			if (m.getArgAsInt(0) == 1) {
				accX1 = int(m.getArgAsDouble(1));
				accY1 = int(m.getArgAsDouble(2));
				accZ1 = int(m.getArgAsDouble(3));
			} else if (m.getArgAsInt(0) == 2) {
				accX2 = int(m.getArgAsDouble(1));
				accY2 = int(m.getArgAsDouble(2));
				accZ2 = int(m.getArgAsDouble(3));
			}
			//std::cout << "ACCELEROMETER: " << m.getAddress() << endl;
		} else if (m.getAddress() == "/gyro") {
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
			//std::cout << "gX: " << gyroX << ", gY: " << gyroY << ", gZ: " << gyroZ << endl;
		} else if (m.getAddress() == "/artifacts") {
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
/*
		for (int i = 0; i < numSensores; i++) {
			if (valSensor1[i] ) {

			}
		}
	*/
}
}

void ofApp::muestraValSensores() {
	if (debug) {
		ofPushStyle();
		ofSetColor(0, 0, 255);
		for (int i = 0; i < numSensores; i++) {
			ofDrawBitmapString(sensor[i] + ": " + ofToString(valSensor1[i]), 100, ofGetHeight() - numSensores * 20 - 50 + i * 20);
		}
		for (int i = 0; i < numSensores; i++) {
			ofDrawBitmapString(sensor[i] + ": " + ofToString(valSensor2[i]), /*ofGetWidth()-300 + */300, ofGetHeight() - numSensores * 20 - 50 + i * 20);
		}
		ofPopStyle();
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
	debugF();
	muestraValSensores();
}

void ofApp::debugF() {
	if (debug) {
		ofDrawBitmapString("- Serial Data:", ofGetWidth() - 300, ofGetHeight() - 50);
//		if (fmod(5, ofGetFrameNum()) == 0) {
			if (serialConectado) {
				ofDrawBitmapString(serial.readByte(), ofGetWidth() - 180, ofGetHeight() - 50);
			} else
				ofDrawBitmapString("revisar conexión", ofGetWidth() - 180, ofGetHeight() - 50);
	//	}
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
}

/////////////// ESCENA 00
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
	logoAbismo.draw(ofGetWidth() / 2 - 620, ofGetHeight() / 2 - 300);
	ofDisableAlphaBlending();
}
/////////////// ESCENA 01
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
			for (int i = 0; i < numSens*2; i++) {
				ondasFbo[i].begin();
				ofBackground(0);
				ondasFbo[i].end();
			}
		}
		break;
	case 1:
		for (int i = 0; i < numPart; i++) {
			particulas1[i].set(
				sin((TWO_PI / numPart)*i)*(radio01 + valSensor1[i] * multSensores)*escala01,
				cos((TWO_PI / numPart)*i)*(radio01 + valSensor1[i] * multSensores)*escala01,
				0);			
			particulas2[i].set(
					sin((TWO_PI / numPart)*i)*(radio01 + valSensor2[i] * multSensores)*escala01,
					cos((TWO_PI / numPart)*i)*(radio01 + valSensor2[i] * multSensores)*escala01,
					0);
		}
		if (radio01 < radio01Fin)
			radio01 += 0.5;
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
		for (int i = 0; i < numPart; i++) {
			particulas1[i].set(particulas1[i].x, valSensor1[i] * 150 * escala01, 0);
		}
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
				escenas = escena;
				cambia01 = false;
			}
			break;
		}
	}
}

void ofApp::dibujaOnda(int indice, int pX, int pY, float val) {
	ofPushStyle();
	ofSetColor(255, opa01);
	ondasFbo[indice].begin();
	ofSetColor(255, opa01 - val * 50);
	ofFill();
	ofEllipse(posOndaX, 50 + ofMap(val, 0, 1, 25, -25), 1 + 8 * val, 1 + 8 * val);
	ondasFbo[indice].end();

	ofSetColor(255, 255, 255, opa01);
	ondasFbo[indice].draw(pX, pY);
	//////////////////////
	ofFill();
	ofSetColor(255, opa01);
	if (indice<numSens)
		texto1.drawString(sensor[indice], pX, pY);
	else
		texto1.drawString(sensor[indice - numSens], pX, pY);
	ofSetLineWidth(1);
	ofNoFill();
	ofSetColor(255, opa01);
	for (int i = 0; i < 6; i++) { // LINEAS VERTICALES
		ofLine(pX + (ondasFbo[0].getWidth() / 5)*i, pY + 30, pX + (ondasFbo[0].getWidth() / 5)*i, pY + 70);
	}

	ofNoFill();
	ofSetLineWidth(1);
	ofSetColor(255, opa01);
	ofLine(pX, pY + 50, pX + ondasFbo[0].getWidth(), pY + 50);
	ofPopStyle();

}
void ofApp::dibujaOnda(int indice, int pX, int pY, int ppXloc, int ppYloc, float val, bool lineal, int pulso) {
	ofPushStyle();
	ofSetColor(255, opa01);
	ondasFbo[indice].begin();
	ofSetColor(255, opa01 - val * 50);
	ofFill();
	if (!lineal)
		ofEllipse(posOndaX, 50 + ofMap(val, 0, 1, 25, -25), 1 + 8 * val, 1 + 8 * val);
	else
		ofLine(pX, 100 + pulso, ppXloc, 100 + ppYloc);

	ondasFbo[indice].end();

	ofSetColor(255, 255, 255, opa01);
	ondasFbo[indice].draw(pX, pY);
	//////////////////////
	ofFill();
	ofSetColor(255, opa01);
	if (indice<numSens)
		texto1.drawString(sensor[indice], pX, pY);
	else
		texto1.drawString(sensor[indice - numSens], pX, pY);
	ofSetLineWidth(1);
	ofNoFill();
	ofSetColor(255, opa01);
	for (int i = 0; i < 6; i++) { // LINEAS VERTICALES
		ofLine(pX + (ondasFbo[0].getWidth() / 5)*i, pY + 30, pX + (ondasFbo[0].getWidth() / 5)*i, pY + 70);
	}

	ofNoFill();
	ofSetLineWidth(1);
	ofSetColor(255, opa01);
	ofLine(pX, pY + 50, pX + ondasFbo[0].getWidth(), pY + 50);
	ofPopStyle();

}
void ofApp::escena01() {
	// ENTENDIMIENTO // TRANQUILIDAD //
	ofEnableAlphaBlending();
	ofPushStyle();

	if (debug) {
		ofDrawBitmapString("Esc01: "+ofToString(esc01), 250,50);
	}
	int cuenta = 0; ////////////////////////////////////////////////////////////////////// BORRAR BORRAR BORRAR BORRAR BORRAR BORRAR
	switch (esc01) {
	case 0:
		/////////////////////////// CONTENIDO PARA USUARIO 1
		ofSetColor(255, opa01);
		ofFill();
		for (int i = 0; i < numSens; i++) {
			dibujaOnda(i, posIniX, ofGetHeight() - 150 - 110 * i, valSensor1[i]);
		}
		ofPopStyle();
		
		museConectado(ofGetWidth()/2-400, 60, 1);
		// Gyro y Acc
		dibujaOrientaciones(ofGetWidth() / 2 - 200, 100, accX1, accY1, accZ1, ofColor(0, 204, 204), "Acelerometro");
		dibujaOrientaciones(ofGetWidth() / 2 - 100, 100, gyroX1, gyroY1, gyroZ1, ofColor(204, 0, 0), "Giroscopio");
		/////////////////////////// CONTENIDO PARA USUARIO 1
		/////////////////////////// CONTENIDO EN ESPEJO PARA USUARIO 2
		ofPushMatrix();
		ofTranslate(ofGetWidth(), 0, 0);
		ofScale(-1, 1, 1);

		ofPushStyle();
		for (int i = 0; i < numSens; i++) {
			dibujaOnda(i+numSens, posIniX, ofGetHeight() - 150 - 110 * i, valSensor2[i]);
		}
		ofPopStyle();
		
		museConectado(ofGetWidth() / 2 - 400, 60, 2);
		// Gyro y Acc
		dibujaOrientaciones(ofGetWidth() / 2 - 200, 100, accX2, accY2, accZ2, ofColor(0, 204, 204), "Acelerometro");
		dibujaOrientaciones(ofGetWidth() / 2 - 100, 100, gyroX2, gyroY2, gyroZ2, ofColor(204, 0, 0), "Giroscopio");
		ofPopMatrix();
		/////////////////////////// CONTENIDO EN ESPEJO PARA USUARIO 2

		break;
	case 1: // HEXÁGONOS
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
		/////////////////////////////////////////////
		/////////////// USUARIO 1
		/////////////////////////////////////////////
		ofPushMatrix();
		ofRotateX(accX1 * multRotaciones);
		ofRotateY(-multRotaciones+accZ1 * multRotaciones);
		ofRotateZ(accY1 * multRotaciones);
		// Dibujo hexagonos con relleno
		ofSetColor(255, opa01 / anillos);
		ofFill();
		//////////
		ofSetPolyMode(OF_POLY_WINDING_NONZERO);
		for (int j = 0; j < anillos; j++) {
			ofBeginShape();
			for (int i = 0; i < numPart; i++) {
				ofVertex(
					particulas1[i].x*((1 + j)*.08),
					particulas1[i].y*((1 + j)*.08),
					sin(i+j*anillos+ofGetElapsedTimeMillis()*.001)*20
				);
			}
			ofEndShape();
		}
		// Dibujo Hexagonos sin relleno
		for (int j = 0; j < anillos; j++) {
			ofSetColor(0, opa01-j*15);
			ofNoFill();
			ofBeginShape();
			for (int i = 0; i < numPart; i++) {
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
			for (int i = 0; i < numPart; i++) {
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
		ofRotateX(90+accX2 * multRotaciones);
		ofRotateY(-multRotaciones + accZ2 * multRotaciones);
		ofRotateZ(accY2 * multRotaciones);
		// Dibujo hexagonos con relleno
		ofSetColor(255, opa01 / anillos);
		ofFill();
		//////////
		ofSetPolyMode(OF_POLY_WINDING_NONZERO);
		for (int j = 0; j < anillos; j++) {
			ofBeginShape();
			for (int i = 0; i < numPart; i++) {
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
			for (int i = 0; i < numPart; i++) {
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
			for (int i = 0; i < numPart; i++) {
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
				5,5);
		}
		/*
		if (!partInPos) {
			for (int i = 0; i < numPart; i++) {
				float pTempX = particulas[i].x;

				particulas[i].set(
					pTempX, 0, 0
				);

				if (particulas[i].x < -ofGetWidth() / 2 + (ofGetWidth() / (numPart - 1))*i)
					particulas[i].x += 5;
				else
					particulas[i].x -= 5;
			}
			if (particulas[0].x < -ofGetWidth() / 2 + 2) {
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
		*/
		if (iniciaOpa01b) {
			ofPushStyle();
			ofSetColor(255, opa01b/anillos);
			for (int j = 0; j < anillos; j++) {
				ofBeginShape();
				ofVertex(ofGetWidth() / 2, ofGetHeight() / 2);
				ofVertex(-ofGetWidth() / 2, ofGetHeight() / 2);
				for (int i = 0; i < numPart; i++) {
					ofVertex(particulas1[i].x, particulas1[i].y+25*j, sin(i + j*anillos + ofGetElapsedTimeMillis()*.001) * 20
					);
				}
				ofEndShape();
			}
			for (int j = 0; j < anillos; j++) {
				ofSetColor(0, opa01b - j * 15);
				ofNoFill();
				ofBeginShape();
				for (int i = 0; i < numPart; i++) {
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

/////////////// ESCENA 02
void ofApp::escena02() {
	if (camara02) {
		myCam.begin();
		ofPushMatrix();
		ofRotateX(-rotaParts * 70);

		if (gira2)
			ofRotateZ(rota360);

		ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
	}


	if (malla02){
		for (int j = 0; j < numPart2Y; j++) {
			for (int i = 0; i < numPart2X; i++) {
				superficie02.setVertex(i + j*numPart2X, nodos[i + j*numPart2X]);
				superficie02.setColor(i + j*numPart2X, ofColor(colNodo02[i+j*numPart2X]));
			}
		}
		superficie02.drawFaces();
	}

	if(ejes02){
		for (int j = 0; j < numPart2Y; j++) {
			for (int i = 0; i < numPart2X; i++) {
				superficie02.setVertex(i + j*numPart2X, nodos[i + j*numPart2X]);
				superficie02.setColor(i + j*numPart2X, ofColor(100));
			}
		}
		superficie02.drawWireframe();
	}
	if (puntos02) {
		for (int j = 0; j < numPart2Y; j++) {
			for (int i = 0; i < numPart2X; i++) {
				//nodos[i + j*numPart2X].z = ofNoise(ofGetElapsedTimeMillis()*0.0005 + i + j*numPart2X) * 250;
				ofEllipse(nodos[i + j*numPart2X].x, nodos[i + j*numPart2X].y, nodos[i + j*numPart2X].z, tamNodos[i + j*numPart2X], tamNodos[i + j*numPart2X]);
			}
		}
	}
	if (camara02) {
		ofPopMatrix();
		myCam.end();
	}

	if (debug) {
		ofDrawBitmapString(ofToString(rotaParts), 200, 200);
		for (int j = 0; j < 6; j++) {
			ofEllipse(sensorPosiciones[j].x, sensorPosiciones[j].y, 20, 20);
		}
	}
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
/////////////// ESCENA 03
void ofApp::escena03() {

}
/////////////// ESCENA 04
void ofApp::escena04() {

}
/////////////// ESCENA 05
void ofApp::escena05() {

}
/////////////// ESCENA 06
void ofApp::escena06() {

}
/////////////// ESCENA 07
void ofApp::escena07() {

}
/////////////// ESCENA 08
void ofApp::escena08() {

}
/////////////// ESCENA 09
void ofApp::escena09() {

}
/////////////// ESCENA 00
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
	if (key == 'd' || key == 'D')
		debug = !debug;
	if (key == 'g' || key == 'G')
		showGui = !showGui;
	if (key == 'e' || key == 'E')
		emularSensores = !emularSensores;
	if (key == 'c' || key == 'C') {
		serial.flush();
		serial.close();
	}
	if (key == 'b' || key == 'B') {
		ofBackground(0);
	}
	if (key == 't' || key == 'T')
		titulo = !titulo;
	if (key == 'i' || key == 'I')
		isGood = !isGood;
	if (key == 's' || key == 'S')
		guardaFrame = !guardaFrame;
	if (key == 'f' || key == 'S'){
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
	escenas = escena;
}
///////////////////// EXIT ///////////////
void ofApp::exit() {
	serial.flush();
	serial.close();
}
///////////////////// GUI ///////////////
void ofApp::setupGUI() {
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
	gui.add(museOn1.setup("museOn1", false));
	gui.add(blink1.setup("blink1", false));
	gui.add(jawClench1.setup("jawClench1", false));
	gui.add(museOn2.setup("museOn2", false));
	gui.add(blink2.setup("blink2", false));
	gui.add(jawClench2.setup("jawClench2", false));
	// Acc
	gui.add(acc.setup("acc", false));
	gui.add(accX1.setup("accX1", 0.1f, 0.0f, 1.0f));
	gui.add(accY1.setup("accY1", 0.1f, 0.0f, 1.0f));
	gui.add(accZ1.setup("accZ1", 0.1f, 0.0f, 1.0f));
	gui.add(accX2.setup("accX2", 0.1f, 0.0f, 1.0f));
	gui.add(accY2.setup("accY2", 0.1f, 0.0f, 1.0f));
	gui.add(accZ2.setup("accZ2", 0.1f, 0.0f, 1.0f));
	// Gyro
	gui.add(gyro.setup("gyro", false));
	gui.add(gyroX1.setup("gyroX1", 0.1f, 0.0f, 1.0f));
	gui.add(gyroY1.setup("gyroY1", 0.1f, 0.0f, 1.0f));
	gui.add(gyroZ1.setup("gyroZ1", 0.1f, 0.0f, 1.0f));
	gui.add(gyroX2.setup("gyroX2", 0.1f, 0.0f, 1.0f));
	gui.add(gyroY2.setup("gyroY2", 0.1f, 0.0f, 1.0f));
	gui.add(gyroZ2.setup("gyroZ2", 0.1f, 0.0f, 1.0f));
	// Connection
	gui.add(isGood.setup("isGood", false));
	gui.add(EEG11.setup("eeg11", 0.1f, 0.0f, 1.0f));
	gui.add(EEG21.setup("eeg21", 0.1f, 0.0f, 1.0f));
	gui.add(EEG31.setup("eeg31", 0.1f, 0.0f, 1.0f));
	gui.add(EEG41.setup("eeg41", 0.1f, 0.0f, 1.0f));
	gui.add(auxLeft1.setup("auxLeft1", 0.1f, 0.0f, 1.0f));
	gui.add(auxRight1.setup("auxRight1", 0.1f, 0.0f, 1.0f));
	gui.add(EEG12.setup("eeg12", 0.1f, 0.0f, 1.0f));
	gui.add(EEG22.setup("eeg22", 0.1f, 0.0f, 1.0f));
	gui.add(EEG32.setup("eeg32", 0.1f, 0.0f, 1.0f));
	gui.add(EEG42.setup("eeg42", 0.1f, 0.0f, 1.0f));
	gui.add(auxLeft2.setup("auxLeft2", 0.1f, 0.0f, 1.0f));
	gui.add(auxRight2.setup("auxRight2", 0.1f, 0.0f, 1.0f));
	// Pulse & GSR
	gui.add(pulseSensor.setup("Pulse", false));
	gui.add(gsr.setup("GSR", false));

	gui.add(camara02.setup("camara02", false));
	gui.add(puntos02.setup("puntos02", false));
	gui.add(ejes02.setup("ejes02", false));
	gui.add(malla02.setup("malla02", false));
	gui.add(invertir02.setup("invertir02", false));
	gui.add(dist02.setup("dist02", 300, 50, 500));
	gui.add(circular02.setup("circular02", false));
	gui.add(radio02.setup("radio02", 300, 100, 5000));

}
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