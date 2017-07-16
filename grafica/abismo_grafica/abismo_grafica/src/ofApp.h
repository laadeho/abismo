#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include <winsock2.h> // importando este archivo se elimina el error de netdb.h sys/socket.h y netinet/in.h
#include "ofxSimpleSerial.h"

#define PORT 7000
#define NUM_MSG_STRINGS 20
#define puertoCOM1 "COM4"
#define puertoCOM2 "COM6"

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
		void gotMessage(ofMessage msg);
		///////// SERIAL ////////////////////
		ofxSimpleSerial	serial1, serial2;
		string message;
		bool reconectarSerial = false;
		// Pulso

		bool esDos = false;
		bool esCero = false;

		bool esUno = false;
		bool esCinco = false;
		
		bool pulso = false;
		bool pulsoSensor1 = false;
		bool pulso1Dato1 = false;
		bool pulso1Dato2 = false;
		bool pulso1Dato3 = false;
		//
		int valSerial1, valSerial2;
		int valPulso1, valPulso2;
		// Dos/Cero // 50/48
		int thressGSR = 30;
		int valGSR = 0;
		bool p1Sensor1, p1Sensor2;
		bool p2Sensor1, p2Sensor2;

		void exit();
		void updateSerial();
		void setupSerial();
		bool trySerialAgain = false;
		bool serial1Conectado, serial2Conectado = false;

		bool debugSerial = true;

		/////////////////////////////

		bool fullScreenDisplay = false;
		bool debug = true;
		void debugF();
		bool showGui = false;
		string sensaciones[11];
		ofTrueTypeFont titulos, texto1;
		int numSens = 7;
		float valSensor1[7] = { 0,0,0,0,0,0,0 };
		float valSensor2[7] = { 0,0,0,0,0,0,0 };
		string sensor[7] = {
			"Alpha", "Beta ", "Gamma", "Delta", "Theta",
			"Pulso" , "GSR"
		};
		ofFbo ondasFbo[14]; // Fbo para render en grafico independiente

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
		void dibujaOnda(int, int, int, int, int, float, bool, int);
		void dibujaOrientaciones(int, int, float, float, float, ofColor, string);
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

		int numPart = 6;
		ofVec3f particulas1[6], particulas2[6];
		float radio01Fin = 500;
		float tamPart[6];
		int anillos = 10;
		int sepAnillos = 30;
		float radio01 = 0.25;
		float escala01 = 1.0f;
		bool partInPos = false;
		bool iniciaOpa01b = false;

		// escena 02
		/*
		Una red de puntos es modificada por
		una serie de particulas rebotando en pantalla
		afectan la distancia entre los nodos. 
		La velocidad de las partículas es dada por 
		los sensores.
		El entorno cimienza a migrar a mallas y posteriormente
		se vuelve un espacio 3d en el que podrán 
		navegar, dando paso a la escena 3 (miedo) con
		vértices afilados y ambientes tenebrosos
		*/
		int numPart2X = 30, numPart2Y = 18;
		int sep2X, sep2Y;
		ofVec3f nodos[30 * 18];
		float tamNodos[30 * 18];
		int colNodo02[30 * 18];

		int numSensores = 6;
		ofVec2f sensorPosiciones[6];
		ofVec2f velSensores[6];
		bool direcciones2X[6], direcciones2Y[6];
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
		// suple a variables de GUI

		bool alpha, beta, gamma, delta, theta;
		bool artifacts, museOn1, museOn2, blink1, blink2, jawClench1, jawClench2;
		bool acc, gyro, isGood;
		float accX1, accX2, accX3, accY1, accY2, accY3, accZ1, accZ2, accZ3;
		float gyroX1, gyroX2, gyroX3, gyroY1, gyroY2, gyroY3, gyroZ1, gyroZ2, gyroZ3;
		float EEG11, EEG12, EEG13, EEG21, EEG22, EEG23, EEG31, EEG32, EEG33, EEG41, EEG42, EEG43;
		float auxLeft1, auxLeft2, auxRight1, auxRight2;
		ofxToggle emularSensores = false;

		/*
		// Brain
		ofxToggle alpha;
		ofxToggle beta;
		ofxToggle gamma;
		ofxToggle delta;
		ofxToggle theta;
		// Artifacts
		ofxToggle artifacts;
		ofxToggle museOn1, museOn2;
		ofxToggle blink1, blink2;
		ofxToggle jawClench1, jawClench2;
		// Accelerometer
		ofxToggle acc;
		ofxFloatSlider accX1, accX2;
		ofxFloatSlider accY1, accY2;
		ofxFloatSlider accZ1, accZ2;
		// Gyro
		ofxToggle gyro;
		ofxFloatSlider gyroX1, gyroX2;
		ofxFloatSlider gyroY1, gyroY2;
		ofxFloatSlider gyroZ1, gyroZ2;
		//Connections
		ofxToggle isGood;
		ofxFloatSlider EEG11, EEG12;
		ofxFloatSlider EEG21, EEG22;
		ofxFloatSlider EEG31, EEG32;
		ofxFloatSlider EEG41, EEG42;
		ofxFloatSlider auxLeft1, auxLeft2;
		ofxFloatSlider auxRight1, auxRight2;
		*/

		ofxToggle pulseSensor;
		ofxToggle gsr;

		// GUI
		ofxPanel gui;
		/////////////// GUI //////////////////		
};
