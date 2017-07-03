#pragma once

#include "ofMain.h"
#include <winsock2.h> 

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
		
		/*
		void setupEscena03();
		void updateEscena03();
		*/

		void drawEscena03();
		void nuevoEnte03();
		ofEasyCam cam03;
		int tamBox = 10;

		int numBox = 0;

		vector <ofVec3f> coords;

};
