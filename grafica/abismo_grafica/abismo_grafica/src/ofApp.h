#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include <winsock2.h>

#define PORT 7000
#define NUM_MSG_STRINGS 20


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
		/////////////////////////////

		bool fullScreenDisplay = false;
		bool debug = true;
		void debugF();
		bool showGui = false;
		string sensaciones[11];
		ofTrueTypeFont titulos, texto1;
		bool emularSensorMuse = false;
		float valSensores[6] = {0,0,0,0,0,0};
		string sensor[6] = {
			"Alpha", "Beta ", "Gamma", "Delta", "Theta",
			"Pulso" 
		};
		
		/////// ESCENAS //////////////////////////
		void muestraValSensores();
		bool titulo = true;
		float velOpa = 1.0f; // Velocidad de opacidad
		int escena = 2; // escena actual
		int numEscenas = 11;
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
		void museConectado(int, int);
		void dibujaOnda(int, int, int, float, int);
		void dibujaOrientaciones(int, int, float, float, float, ofColor, string);
		float opa01 = 0.0;

		string ondas[5];
		int anchoOndaVentana;
		float valOnda[5];
		int posIniX = 100;
		int sep = 50;
		float posOndaX = 0;
		float velOndaX = 0.5;
		ofFbo ondasFbo[5];
		int multSensores = 100;
		int multRotaciones = 45;

		int esc01 = 0;
		bool cambia01 = false;
		float opa01b = 0.0;

		int numPart = 6;
		ofVec3f particulas[6];
		float radio01Fin = 500;
		float radio01 = 0.25;
		float tamPart[6];
		int anillos = 10;
		int sepAnillos = 30;
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
		// Brain
		ofxToggle alpha;
		ofxToggle beta;
		ofxToggle gamma;
		ofxToggle delta;
		ofxToggle theta;
		// Artifacts
		ofxToggle artifacts;
		ofxToggle museOn;
		ofxToggle blink;
		ofxToggle jawClench;
		// Accelerometer
		ofxToggle acc;
		ofxFloatSlider accX;
		ofxFloatSlider accY;
		ofxFloatSlider accZ;
		// Gyro
		ofxToggle gyro;
		ofxFloatSlider gyroX;
		ofxFloatSlider gyroY;
		ofxFloatSlider gyroZ;
		//Connections
		ofxToggle isGood;
		ofxFloatSlider EEG1;
		ofxFloatSlider EEG2;
		ofxFloatSlider EEG3;
		ofxFloatSlider EEG4;
		ofxFloatSlider auxLeft;
		ofxFloatSlider auxRight;

		ofxToggle pulseSensor;

		// GUI
		ofxPanel gui;
		/////////////// GUI //////////////////		
};
