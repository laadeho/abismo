#ifndef _OF_APP
#define _OF_APP

#include "ofMain.h"
#include "ofxSimpleSerial.h"
#include <vector>
#include "ofUtils.h"

#define puertoCOM1 "COM4"

using namespace std;

class ofApp : public ofBaseApp {

public:

	ofxSimpleSerial	serial;
	string		message;
	bool		red;
	bool		green;
	bool		blue;
	int azul;
	bool		requestRead;

	void		setup();
	void		update();
	void		draw();
	void		mousePressed(int x, int y, int button);
	void		onNewMessage(string & message);

	bool pulse;
	
	void exit();

protected:

};

#endif	

