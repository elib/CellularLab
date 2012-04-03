#include "ofMain.h"
#include "cellularApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( )
{
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 600, 600, OF_WINDOW);
	ofEnableAlphaBlending();
	ofSetFrameRate(60);

	//window.setGlutDisplayString("rgba double samples>=4");

	ofRunApp( new cellularApp());
}