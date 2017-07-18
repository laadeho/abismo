#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main() {

	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 300, 300, OF_WINDOW);			// <-------- setup the GL context
														// this kicks off the running of my app
														// can be OF_WINDOW or OF_FULLSCREEN
														// pass in width and height too:
	ofSetWindowPosition(100, 600);
	ofRunApp(new ofApp());
}
