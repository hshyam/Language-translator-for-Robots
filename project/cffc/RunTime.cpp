#include "RunTime.h"
#include <iostream>

using namespace std ;

RunTime::RunTime() { }

int RunTime::run( MachineState *initialState) {
    currentState = initialState ;

    while ( currentState != NULL ) {
        this->readSensors() ;

        nextState = currentState->enter() ;

        this->writeActuators() ;

        currentState = nextState ;
    }
    return  0 ;
}

void RunTime::readSensors() { }
void RunTime::writeActuators() { }

/*
 * Platform Specific RunTimes Classes
 * --------------------------------------------------
 */


// IntegerStreamComputer
// ---------------
IntegerStreamComputer::IntegerStreamComputer (int argc, char **argv) { 
    index = 1 ;
    numInputs = argc - 1 ;
    inputStrings = argv ;
}

void IntegerStreamComputer::readSensors() { 
    sscanf ( inputStrings[index], "%d", & input ) ;
}

void IntegerStreamComputer::writeActuators() {
    cout << output << endl ;
    if (index == numInputs) nextState = NULL ;
    ++ index ;
}


// RegexRecognizer
// ---------------
RegexRecognizer::RegexRecognizer (int argc, char **argv) { 
    inputBuffer = argv[1] ; 
    inputBufferIndex = 0 ; 
    outputBuffer = "" ;
}

void RegexRecognizer::readSensors() { 
    nextChar = inputBuffer [ inputBufferIndex ++ ] ;
}

void RegexRecognizer::writeActuators() {
    if ( ! outputBuffer.empty() )
        cout << outputBuffer << endl ;
    outputBuffer = "" ;    
}


// IntegerComputer
// ---------------
IntegerComputer::IntegerComputer (int argc, char **argv) { 
    sscanf( argv[1], "%d", &input) ;
    output = 0 ;
}

void IntegerComputer::readSensors() { 
}

void IntegerComputer::writeActuators() {
    cout << output << endl ;
}


// PositionalRobot
// ---------------
PositionalRobot::PositionalRobot (int argc, char **argv) { 
}

void PositionalRobot::readSensors() { 
}

void PositionalRobot::writeActuators() {
    cout << "  XPos: " << xPos << "  YPos: " << yPos << endl ;
}


