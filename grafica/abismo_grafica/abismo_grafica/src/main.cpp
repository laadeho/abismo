#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	//ofSetupOpenGL(1920, 1080, OF_WINDOW);			// <-------- setup the GL context
	ofAppGlutWindow window;
	// DOS PROYES Y MONITOR
	
	/*ofSetupOpenGL(&window, 5120, 1080, OF_WINDOW);
	ofSetWindowPosition(-1280, 0);
	*/
	ofSetupOpenGL(&window, 1920, 1080, OF_WINDOW);
	//ofSetWindowPosition(1920, 0);
	//ofSetupOpenGL(1920, 1080, OF_FULLSCREEN);
	
	//ofSetupOpenGL(1280, 720, OF_WINDOW);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}