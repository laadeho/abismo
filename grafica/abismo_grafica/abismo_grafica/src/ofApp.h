#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"

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
		bool debug = false;
		bool showGui = false;
		string sensaciones[10];
		ofTrueTypeFont titulos, texto1;

		int escena;
		int numEscenas = 10;
		bool emularSensorMuse = false;
		float valSensores[5] = {0,0,0,0,0};
		/////// ESCENAS //////////////////////////
		void escena01();
		void dibujaOnda(int, int, int, float);
		void dibujaOrientacion(int, int);

		float opaGral = 0.0;
		float opa01 = 0.0;
		string ondas[5];
		float valOnda[5];
		int posIniX = 100;
		float posOndaX = posIniX;
		float velOndaX = 0.05;






		///// TEST OSC ////////////////////////////
		ofTrueTypeFont font;
		ofxOscReceiver receiver;

		int current_msg_string;
		string msg_strings[NUM_MSG_STRINGS];
		float timers[NUM_MSG_STRINGS];

		int mouseX, mouseY;
		string mouseButtonState;

		ofImage receivedImage;
		///// TEST OSC ////////////////////////////
		void updateOSC();

		/////////// GUI //////////////////
		ofxIntSlider escenas;
		// Brain
		ofxToggle alpha;
		ofxToggle beta;
		ofxToggle gamma;
		ofxToggle delta;
		ofxToggle theta;
		// Artifacts
		ofxToggle artifacts;
		ofxToggle museOn;
		ofxButton blink;
		ofxButton jawClench;
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
		// GUI
		ofxPanel gui;
		/////////////// GUI //////////////////		
};
