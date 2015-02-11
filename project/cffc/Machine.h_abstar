// Generated Machine.h for ABStar

#include "RunTime.h"

// Declarations of the State classes
class State_Final ; 
class State_NeedB ; 
class State_Error ; 


class ABStar_Machine { 
   public: 
   ABStar_Machine( int argc, char **argv ) ; 

   void go() ;

   RegexRecognizer *runTime ;

   // Machine states
   State_Final *state_Final ; 
   State_NeedB *state_NeedB ; 
   State_Error *state_Error ; 

} ;

class ABStarState : public MachineState {
   public: 
   ABStar_Machine *stateMachine ; 
} ; 

// Concrete machine states
class State_Final : public ABStarState { 
   public:
   MachineState *enter () ;
   State_Final ( ABStar_Machine *m ) ;
} ;

class State_NeedB : public ABStarState { 
   public:
   MachineState *enter () ;
   State_NeedB ( ABStar_Machine *m ) ;
} ;

class State_Error : public ABStarState { 
   public:
   MachineState *enter () ;
   State_Error ( ABStar_Machine *m ) ;
} ;



