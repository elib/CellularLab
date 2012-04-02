#include "cellularApp.h"

#include "CellGrid.h"
#include "CellFactory.h"
#include "DecayingCellRule.h"
#include "AcceptIfConnectedRule.h"
#include "AssignResourcesRule.h"

//--------------------------------------------------------------
void cellularApp::setup()
{
	_cellGrid = new CellGrid();
	_cellGrid->Setup(MEGASTRUCTURE_CELL, 20, 20);

	DecayingCellRule rule1;
	AssignResourcesRule rule2;
	AcceptIfConnectedRule rule3;

	_cellGrid->AddCellRule(&rule1);
	_cellGrid->AddGlobalRule(&rule2);
	_cellGrid->AddAcceptRule(&rule3);

	simulationSpeed = 1;
}

//--------------------------------------------------------------
void cellularApp::update()
{
	_cellGrid->Update(simulationSpeed);
}

//--------------------------------------------------------------
void cellularApp::draw()
{
	ofBackground(100, 255);
	_cellGrid->Draw(ofGetViewportWidth(), ofGetViewportHeight());

}

//--------------------------------------------------------------
void cellularApp::keyPressed  (int key)
{
    switch (key){
        case 'a':
            simulationSpeed += 1;
            break;
		case 'z':
			simulationSpeed  = max(simulationSpeed - 1, 1);
			break;
    }
}

//--------------------------------------------------------------
void cellularApp::keyReleased  (int key)
{
}

//--------------------------------------------------------------
void cellularApp::mouseMoved(int x, int y )
{
}

//--------------------------------------------------------------
void cellularApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void cellularApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void cellularApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void cellularApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void cellularApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void cellularApp::dragEvent(ofDragInfo dragInfo){ 

}