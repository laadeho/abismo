#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);
	serial.listDevices();
	serial.setup("COM4", 9600);
	serial.startContinuousRead();
	ofAddListener(serial.NEW_MESSAGE, this, &ofApp::onNewMessage);

	message = "";

	ofLogNotice("SETUP LISTO");
}

void ofApp::onNewMessage(string & message)
{
	cout << "onNewMessage, message: " << message << "\n";

	red = (message == "r");
	green = (message == "g");
	blue = (message == "b");
	ofLogNotice(ofToString(message));

}

void ofApp::update()
{
	if (requestRead)
	{
		serial.sendRequest();
		requestRead = false;
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	int redColor = (red) ? 255 : 0;
	int greenColor = (green) ? 255 : 0;
	int blueColor = (blue) ? 255 : 0;

	ofBackground(redColor, greenColor, blueColor);

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	requestRead = true;
}

void ofApp::exit() {
	serial.flush();
	serial.close();
}