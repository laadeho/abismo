#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include <winsock2.h>
// importando este archivo se elimina el error de netdb.h sys/socket.h y netinet/in.h
//#include "ofxSimpleSerial.h"
#include <vector>
#include "ofUtils.h"

// OSC
#define PORT 7000
#define NUM_MSG_STRINGS 20
// OSC

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);

		void exit();
		
		///////  DESARROLLADOR
		bool help = false;
		bool debug = true;
		void debugF();
		bool showGui = false;
		/////////////////////////////

		bool fullScreenDisplay = false;
		string sensaciones[11] = {
			"Logo", "Entendimiento / Tranquilidad", "Expectativa ", "Miedo",
		"Asombro", "Euforia", "Tristeza, Soledad", "Abismo", "Felicidad", "Reconocimiento", "Proximidad"
		};
		ofTrueTypeFont titulos, texto1;
		int numSens = 7;
		float valSensor1[7] = { 0,0,0,0,0,0,0 };
		float valSensor2[7] = { 0,0,0,0,0,0,0 };
		string sensor[7] = {
			"Alpha", "Beta ", "Gamma", "Delta", "Theta",
			"Pulso" , "G S R"
		};
		ofFbo ondasFbo[14];
		// Fbo para render en grafico independiente

		/////// ESCENAS //////////////////////////
		void muestraValSensores();
		bool titulo = true;
		float velOpa = 1.0f; // Velocidad de opacidad
		int escena = 0; // escena actual
		int numEscenas = 11;
		void setupEsc01();
		void updateEsc01();

		void escena00(), escena01(), escena02(), escena03(),
			escena04(), escena05(), escena06(), escena07(), 
			escena08(), escena09(), escena10();
		// escena 00
		bool iniciaTodo = true;
		int contador, limiteContador = 50;
		bool entraLogo = false; 
		bool saleLogo = false;
		ofImage logoAbismo;
		float opaLogo;
		// escena 01
		void museConectado(int, int, int);
		void dibujaOnda(int, int, int, float);
		void dibujaOnda(int, int, int, int, int, int, float);
		void dibujaOrientaciones(int, int, float, float, float, ofColor, string);
		int posActY1[2], posActY2[2];
		int posPrevY1[2], posPrevY2[2];

		float opa01 = 0.0;
		int ppX, ppY;

		int anchoOndaVentana;
		int posIniX = 100;
		int sep = 50;
		float posOndaX = 0;
		float velOndaX = 0.5;
		int multSensores = 175; // MULTIPLICADOR DE LOS SENSORES
		int multRotaciones = 45;

		int esc01 = 0;
		bool cambia01 = false;
		float opa01b = 0.0;

		int numPart = 7;
		ofVec3f particulas1[7], particulas2[7];
		float radio01Fin = 500;
		float tamPart[7];

		int anillos = 10;
		int sepAnillos = 30;
		float radio01 = 0.25;
		float escala01 = 1.0f;
		bool partInPos = false;
		bool iniciaOpa01b = false;

		// escena 02
		int numPart2X = 30, numPart2Y = 18;
		int sep2X, sep2Y;
		ofVec3f nodos[30 * 18];
		float tamNodos[30 * 18];
		int colNodo02[30 * 18];

		ofVec2f sensorPosiciones[7];
		ofVec2f velSensores[7];
		bool direcciones2X[7], direcciones2Y[7];

		int velMult = 10;
		float colEjes02 = 0, colPuntos02 = 0;
		float ampNodo02 = 0;
		// ahora a modificarlo en una superficie
		ofxToggle camara02;
		ofxToggle puntos02;
		ofxToggle ejes02;
		ofxToggle malla02;
		ofxToggle invertir02;
		ofxFloatSlider dist02;
		ofxToggle circular02;
		ofxFloatSlider radio02;

		ofVec3f posCam;
		ofEasyCam myCam;
		float rotaParts = 0;
		bool gira2 = false;	
		float rota360 = 0;

		ofMesh superficie02;
		float numPart02;
		double incCol02;

		// escenas END

		ofImage captura;
		///// OSC ////////////////////////////
		ofTrueTypeFont font;
		ofxOscReceiver receiver;
		int current_msg_string;
		string msg_strings[NUM_MSG_STRINGS];
		float timers[NUM_MSG_STRINGS];
		void updateOSC();
		///// OSC ////////////////////////////

		/////////// GUI //////////////////
		void setupGUI();
		ofxIntSlider escenas;
		ofxToggle guardaFrame;
		bool alpha, beta, gamma, delta, theta;
		bool artifacts, museOn1, museOn2, blink1, blink2, jawClench1, jawClench2;
		bool acc, gyro, isGood;
		float accX1, accX2, accX3, accY1, accY2, accY3, accZ1, accZ2, accZ3;
		float gyroX1, gyroX2, gyroX3, gyroY1, gyroY2, gyroY3, gyroZ1, gyroZ2, gyroZ3;
		float EEG11, EEG12, EEG13, EEG21, EEG22, EEG23, EEG31, EEG32, EEG33, EEG41, EEG42, EEG43;
		float auxLeft1, auxLeft2, auxRight1, auxRight2;
		ofxToggle emularSensores = false;

		bool pulse = false;
		bool gsr = false;

		// GUI
		ofxPanel gui;
		/////////////// GUI //////////////////		
};
