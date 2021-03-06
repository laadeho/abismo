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
		bool debug = false;
		void debugF();
		bool showGui = false;
		/////////////////////////////

		bool fullScreenDisplay = true;
		string sensaciones[11] = {
			"Logo", "Entendimiento / Tranquilidad", "Expectativa ",
			"Miedo", "Asombro", "Euforia", "Tristeza, Soledad",
			"Abismo", "Felicidad", "Reconocimiento", "Proximidad"
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
		bool titulo = false;
		
		float velOpa = 1.0f; // Velocidad de opacidad
		

		int escena = 0; // escena actual
		
		int numEscenas = 11;
		
		void updateEmular();
		void escena00(), escena01(), escena02(),
			escena03(),	escena04(), escena05(),
			escena06(), escena07(), escena08(), 
			escena09(), escena10();
		void setupEsc01(), updateEsc01();
		void setupEsc02(), updateEsc02();
		void updateEsc03(), updateEscena04(),
			updateEscena07(), updateEscena08();

		void camAnim();

		bool alphaActivo = true;
		
		bool switchAlpha = false;
		bool alphaEncendido = false;

		ofColor c; // Ellipses // nodos
		ofColor cE; // Ejes
		ofColor cSrf; 
		float cSrfR, cSrfG, cSrfB, cSrfA;
		int ejesGral = 100;
		/////////////////////////////////////////////////
		// escena 00
		/////////////////////////////////////////////////
		bool iniciaTodo = true;
		int contador, limiteContador = 50;
		bool entraLogo = false; 
		bool saleLogo = false;
		ofImage logoAbismo, logoAbismoInv;
		float opaLogo;
		/////////////////////////////////////////////////
		// escena 01
		/////////////////////////////////////////////////
		int colLine = 100; // Color de lineas esc01
		int pasada = 0; // Barridos de posicion en X
		int cuentaPulsos = 0;
		bool aumentaCuentaPulso = true;

		int valOnda1, valOnda2;

		void museConectado(int, int, int);
		void dibujaLineas(int, int);
		void dibujaOnda(int, int, int, float, ofColor);
		void dibujaOnda(int, int, int, int, float, ofColor);
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
		/////////////////////////////////////////////////
		// escena 02
		/////////////////////////////////////////////////
		int sep2X, sep2Y;
		int numPart2X = 60, numPart2Y = 36;
		ofVec3f nodos[60 * 36];
		ofVec3f nodosTemp[60 * 36];

		float tamNodos[60 * 36];
		int colNodo02[60 * 36];
		ofVec2f sensorPosiciones[7];
		ofVec2f velSensores[7];
		bool direcciones2X[7], direcciones2Y[7];

		int cuentaFueraPantalla[7]; 
		bool entra02 = true;
		bool dibujaPosiciones = true;
		bool cambiaRadios02 = false;
		float dist02 = 300;

		bool autom02 = true;
		bool switchEllipse = false; // Cambia numero de elipses
		float opa02 = 0.0;
		float alphaSrf02 = 255;
		int cuenta02; // Contador para comportamientos
		int velMult = 3; // Multiplicador de velocidad
		float colEjes02 = 0, colPuntos02 = 0;
		float ampNodo02 = 0;
		/////////////////////////////////////////////////
		// escena 03
		/////////////////////////////////////////////////
		bool ajusta03 = true;
		int cuenta03;
		bool fondo03;
		bool cambiaColorNodo03 = false;
		bool cambiaTamNodo03 = false;
		float colRed = 0;
		/////////////////////////////////////////////////
		// escena 04 y 05
		/////////////////////////////////////////////////
		int cuenta04 = 0;
		int cuenta05 = 0;
		bool noiseSrf = false;
		bool reset04 = false;

		float tamNoise = 0.0;
		float maxNoise = 1450.0;
		float velNoise = 0.00015;
		float valSin05 = 1;
		//float sepX05 = 1, sepY05 = 1;
		/////////////////////////////////////////////////
		// escena 06
		/////////////////////////////////////////////////

		bool mallaSrf = false;
		bool apagaMalla = true;
		bool camara02 = false;
		bool puntos02 = false;
		
		bool ejes02, invertir02, circular02;
		ofxFloatSlider radio02;

		ofVec3f posCam;
		ofEasyCam myCam;
		float rotaParts = 0;
		bool gira2 = false;	
		float rota360 = 0;

		ofMesh superficie02;
		float numPart02;
		double incCol02;


		/////////////////////////////////////////////////
		// escena 08
		/////////////////////////////////////////////////
		void textoCentro(string, bool, bool, int, int, int, int);
		// texto, centroH, centroV, pX, pY, numFont, tamFont
		ofTrueTypeFont	verdana;
		ofTrueTypeFont	helvNormal;
		ofTrueTypeFont	helvBlack;
		ofTrueTypeFont	frabk;
		bool entraOpa, saleOpa;
		int valOpa = 0;
		int cuenta08 = 0;
		int preguntas;
		/////////////////////////////////////////////////
		// escena 09
		/////////////////////////////////////////////////
		float valBack09 = 0.0f;


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
		ofxToggle emularSensores;

		bool alpha, beta, gamma, delta, theta;
		bool artifacts, museOn1, museOn2, blink1, blink2, jawClench1, jawClench2;
		bool acc, gyro, isGood;
		float accX1, accX2, accX3, accY1, accY2, accY3, accZ1, accZ2, accZ3;
		float gyroX1, gyroX2, gyroX3, gyroY1, gyroY2, gyroY3, gyroZ1, gyroZ2, gyroZ3;
		float EEG11, EEG12, EEG13, EEG21, EEG22, EEG23, EEG31, EEG32, EEG33, EEG41, EEG42, EEG43;
		float auxLeft1, auxLeft2, auxRight1, auxRight2;

		bool pulse = false;
		bool gsr = false;

		// GUI
		ofxPanel gui;
		/////////////// GUI //////////////////		
};
