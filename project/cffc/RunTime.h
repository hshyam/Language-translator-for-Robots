#ifndef RUNTIME
#define RUNTIME

#include <cstdio>
#include <string>

/*
 * Generic RunTime
 * ---------------
 */
class MachineState {
public:
    virtual MachineState *enter() = 0 ; 
} ;

class RunTime {
public:
    MachineState *currentState ;
    MachineState *nextState ;

    RunTime ( ) ;

    virtual void readSensors() ;
    virtual void writeActuators() ;

    virtual int run ( MachineState *initialState) ;
} ;

/*
 * Platform Specific RunTime Classes
 * --------------------------------------------------
*/

class RegexRecognizer : public RunTime {
public:
    char nextChar ;
    std::string outputBuffer ;

    RegexRecognizer (int argc, char **argv) ;
    void readSensors() ;
    void writeActuators() ;

private:
    const char* inputBuffer ;
    int inputBufferIndex ;
} ;


class IntegerComputer : public RunTime {
public:
    int input ;
    int output ;

    IntegerComputer (int argc, char **argv) ;
    void readSensors() ;
    void writeActuators() ;
} ;

class IntegerStreamComputer : public RunTime {
public:
    int input ;
    int output ;

    IntegerStreamComputer (int argc, char **argv) ;
    void readSensors() ;
    void writeActuators() ;

private:
    int index ;
    int numInputs ;
    char **inputStrings ;
} ;

class PositionalRobot : public RunTime {
public:
    float xPos ;
    float yPos ;

    PositionalRobot (int argc, char **argv) ;
    void readSensors() ;
    void writeActuators() ;
} ;

#endif
