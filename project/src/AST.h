#ifndef AST_H
#define AST_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "strfmt.h"

class Node {
 public:
  Node() {};
  virtual ~Node() {};
  virtual int getNumVarUses() = 0;
} ;

class Decl : public Node {
 public:
  Decl() {
    numDecls = 0;
    d = NULL;
    name = "";
  };
  Decl(std::string input, Decl *dp) {
    numDecls = 1;
    name = input;
    d = dp;
  };
  std::string getName() {
    return name;
  };
  int getNumVarUses() {
    return 0;
  };
  int getNumVarDecls() {
    if (d != NULL)
      numDecls = numDecls + d->getNumVarDecls();
    return numDecls;
  };

  Decl *getNextDecl() {
    return d;
  };

 private:
  std::string name;
  int numDecls;
  Decl *d;
} ;

/*class Decls : public Node {
 public:
  Decls() {
    numDecls = 0;
  };
  Decls(Decl *dp, Decls *ddp) {
    d = dp;
    dd = ddp;
    numDecls = 0;
  };
  ~Decls() {};
  int getNumVarDecls() {
    if (d != NULL) 
      numDecls = numDecls + d->getNumVarDecls();
    if (dd != NULL)
      numDecls = numDecls + dd->getNumVarDecls();
    return numDecls;
  };
  int getNumVarUses() {
    return 0;
  };
  
 private:
  Decl *d;
  Decls *dd;
  int numDecls;
} ;

Decls was removed for writing assignment 3. */

class Expr : public Node {
 public:
  Expr() {
  };
  ~Expr() {};
  virtual std::string getValue() = 0;
  virtual int setStateMachineTrue(Decl*) = 0;

  int getNumVarUses() {
    return numVarUses;
  }

 private:
  int numVarUses;
} ;

class Num : public Expr {
 public:
  Num(std::string input) {
    val = input;
  };
  ~Num() {};

  int getNumVarUses() {
    return 0;
  };

  std::string getValue() {
    return val;
  };

  int setStateMachineTrue(Decl *dp) {
    return 0;
  }

 private:
  std::string val;
  bool isInt;
  } ;

class VariableUse : public Expr {
 public:
  VariableUse() {};
  VariableUse(std::string input) {
    name = input;
    onStateMachine = false;
  };
  ~VariableUse() {};

  int getNumVarUses() {
    return 1;
  };

  int setStateMachineTrue(Decl *dp) {
    int numDecls = dp->getNumVarDecls();
    Decl *currDecl = dp;
    for (int i = 0; i < numDecls; i++) {
      if (!name.compare(currDecl->getName()))
	onStateMachine = true;
      currDecl = dp->getNextDecl();
    }
    return 0;
  };
  
  std::string getValue() {
    if (onStateMachine)
      return string_format("stateMachine->Var_%s", name.c_str());
    else
      return string_format("stateMachine->runTime->%s", name.c_str());
  };

 private:
  std::string name;
  bool onStateMachine;
};

class Bool : public Expr {
 public:
  Bool() {};
  Bool(std::string input) {
    val = input;
  };
  ~Bool() {};

  std::string getValue() {
    return val;
  };

  int setStateMachineTrue(Decl *dp) {
    return 0;
  }

 private:
  std::string val;
};

class CharConst : public Expr {
 public:
  CharConst() {};
  CharConst(std::string input) {
    val = input;
  };
  ~CharConst() {};

  std::string getValue() {
    return val;
  };

  int setStateMachineTrue(Decl *dp) {
    return 0;
  }
  
  private:
    std::string val;
};

class StringConst : public Expr {
 public:
  StringConst() {};
  StringConst(std::string input) {
    val = input;
  };
  ~StringConst() {};

  std::string getValue() {
    return val;
  };

  int setStateMachineTrue(Decl *dp) {
    return 0;
  }
  
  private:
    std::string val;
};

class Add : public Expr {
 public:
  Add() {};
  Add(Expr *e1, Expr *e2) {
    left = e1;
    right = e2;
  };
  ~Add() {};

  int getNumVarUses()
  {
    numVarUses = left->getNumVarUses() + right->getNumVarUses();
    return numVarUses;
  };
 
  std::string getValue() {
    return string_format("%s + %s", left->getValue().c_str(), right->getValue().c_str());
  };

  int setStateMachineTrue(Decl *dp) {
    left->setStateMachineTrue(dp);
    right->setStateMachineTrue(dp);
    return 0;
  };

 private:
  Expr * left;
  Expr * right;
  int numVarUses;
} ;

class Mul : public Expr {
 public:
  Mul() {};
  Mul(Expr *e1, Expr *e2) {
    left = e1;
    right = e2;
  };
  ~Mul() {};

  int getNumVarUses() {
    numVarUses = left->getNumVarUses() + right->getNumVarUses();
    return numVarUses;
  };

  std::string getValue() {
    return string_format("%s * %s", left->getValue().c_str(), right->getValue().c_str());
  };

  int setStateMachineTrue(Decl *dp) {
    left->setStateMachineTrue(dp);
    right->setStateMachineTrue(dp);
    return 0;
  };

 private:
  Expr * left;
  Expr * right;
  int numVarUses;
} ;

class Sub : public Expr {
 public:
  Sub() {};
  Sub(Expr *e1, Expr *e2) {
    left = e1;
    right = e2;
  };
  ~Sub() {};

  int getNumVarUses() {
    numVarUses = left->getNumVarUses() + right->getNumVarUses();
    return numVarUses;
  };

  std::string getValue() {
    return string_format("%s - %s", left->getValue().c_str(), right->getValue().c_str());
  };

  int setStateMachineTrue(Decl *dp) {
    left->setStateMachineTrue(dp);
    right->setStateMachineTrue(dp);
    return 0;
  };

 private:
  Expr * left;
  Expr * right;
  int numVarUses;
} ;

class Div : public Expr {
 public:
  Div() {};
  Div(Expr *e1, Expr *e2) {
    left = e1;
    right = e2;
  };
  ~Div() {};

  int getNumVarUses() {
    numVarUses = left->getNumVarUses() + right->getNumVarUses();
    return numVarUses;
  };

  std::string getValue() {
    return string_format("%s / %s", left->getValue().c_str(), right->getValue().c_str());
  };

  int setStateMachineTrue(Decl *dp) {
    left->setStateMachineTrue(dp);
    right->setStateMachineTrue(dp);
    return 0;
  };

 private:
  Expr * left;
  Expr * right;
  int numVarUses;
} ;

class RelOp : public Expr {
 public:
  RelOp() {};
  RelOp(Expr *e1, std::string oper, Expr *e2) {
    left = e1;
    op = oper;
    right = e2;
  };
  ~RelOp() {};

  int getNumVarUses() {
    if (left != NULL)
      numVarUses = numVarUses + left->getNumVarUses();
    if (right != NULL)
      numVarUses = numVarUses + right->getNumVarUses();
    return numVarUses;
  };

  std::string getValue() {
    return string_format("%s %s %s", left->getValue().c_str(), op.c_str(), right->getValue().c_str());
  };

  int setStateMachineTrue(Decl *dp) {
    left->setStateMachineTrue(dp);
    right->setStateMachineTrue(dp);
    return 0;
  };
  
 private:
  Expr *left;
  std::string op;
  Expr *right;
  int numVarUses;
};

class Platform : public Node {
 public:
  Platform() {};
  Platform(std::string input) {
    name = input;
  };
  ~Platform() {};
  std::string getPlatformName() {
    return name;
  };
  int getNumVarUses() {
    return 0;
  };

 private:
  std::string name;
} ;

class Stmt : public Node {
 public:
  Stmt() {};
  Stmt(Expr *ep, std::string input) {
    e = ep;
    name = input;
    numVarUses = 1;
  };
  ~Stmt() {};
  int getNumVarUses() {
    if (e != NULL)
      numVarUses = numVarUses + e->getNumVarUses();
    return numVarUses;
  };

  std::string getVarName() {
    if (onStateMachine)
      return string_format("stateMachine->Var_%s", name.c_str());
    else
      return string_format("stateMachine->runTime->%s", name.c_str());
  }

  int getNumStmts() {
    return 1;
  };

  std::string getExpr() {
    return e->getValue();
  }

  int setStateMachineTrue(Decl *dp) {
    int numDecls = dp->getNumVarDecls();
    Decl *currDecl = dp;
    for (int i = 0; i < numDecls; i++) {
      if (!name.compare(currDecl->getName()))
	onStateMachine = true;
      currDecl = dp->getNextDecl();
    }
    if (e != NULL)
      e->setStateMachineTrue(dp);
    return 0;
  };

 private:
  int numVarUses;
  Expr *e;
  std::string name;
  bool onStateMachine;
} ;

class Stmts : public Node {
 public:
  Stmts() {};
  Stmts(Stmt *sp, Stmts *ssp) {
    s = sp;
    ss = ssp;
    numVarUses = 0;
    numStmts = 0;
  }
  ~Stmts() {};
  int getNumVarUses() {
    if (s != NULL)
      numVarUses = numVarUses + s->getNumVarUses();
    if (ss != NULL)
      numVarUses = numVarUses +  ss->getNumVarUses();
    return numVarUses;
  };

  int getNumStmts() {
    if (s != NULL)
      numStmts = numStmts + s->getNumStmts();
    if (ss != NULL)
      numStmts = numStmts +  ss->getNumStmts();
    return numStmts;
  };

  Stmt *getCurrentStmt() {
    if (s != NULL)
      return s;
  };

  Stmts *getNextStmts() {
    if (ss != NULL)
      return ss;
  };

  int setStateMachineTrue(Decl *dp) {
    if (s != NULL)
      s->setStateMachineTrue(dp);
    if (ss != NULL)
      ss->setStateMachineTrue(dp);
    return 0;
  };

 private:
  Stmt *s;
  Stmts *ss;
  int numVarUses;
  int numStmts;
} ;

class Transition : public Node {
 public:
  Transition() {};
  Transition(Expr *ep, Stmts *ssp, std::string input) {
    e = ep;
    ss = ssp;
    name = input;
    numVarUses = 0;
  };
  ~Transition() {};
  int getNumVarUses() {
    if (e != NULL) 
      numVarUses = numVarUses +  e->getNumVarUses();
    if (ss != NULL)
      numVarUses = numVarUses + ss->getNumVarUses();
    return numVarUses;
  };

  int getNumTransitions() {
    return 1;
  };

  int getNumStmts() {
    if (ss != NULL)
      return ss->getNumStmts();
  };

  std::string getName() {
    if (name.compare("NULL"))
      return string_format("stateMachine->state_%s", name.c_str());
    else
      return name;
  };

  std::string getExpr() {
    if (e != NULL)
      return e->getValue();
  };

  Stmts *getStmts() {
    if (ss != NULL)
      return ss;
  };

  int setStateMachineTrue(Decl *dp) {
    if (e != NULL)
      e->setStateMachineTrue(dp);
    if (ss != NULL)
      ss->setStateMachineTrue(dp);
    return 0;
  };

 private:
  Expr *e;
  Stmts *ss;
  int numVarUses;
  std::string name;
} ;

class Transitions : public Node {
 public:
  Transitions() {};
  Transitions(Transition *tp, Transitions *ttp) {
    t = tp;
    tt = ttp;
    numVarUses = 0;
  };
  ~Transitions() {};
  int getNumVarUses() {
    if (t != NULL)
      numVarUses = numVarUses + t->getNumVarUses() ;
    if ( tt != NULL)
      numVarUses = numVarUses + tt->getNumVarUses();
    return numVarUses;
  };
  int getNumTransitions() {
    if (t != NULL) 
      numTransitions = numTransitions + t->getNumTransitions();
    if (tt != NULL)
      numTransitions = numTransitions + tt->getNumTransitions();
    return numTransitions;
  };

  Transition *getCurrentTransition() {
    if (t != NULL)
      return t;
  };

  Transitions *getNextTransitions() {
    if (tt != NULL)
      return tt;
  };

  int setStateMachineTrue(Decl *dp) {
    if (t != NULL)
      t->setStateMachineTrue(dp);
    if (tt != NULL)
      tt->setStateMachineTrue(dp);
    return 0;
  };

 private:
  Transition *t;
  Transitions *tt;
  int numVarUses;
  int numTransitions;
} ;

class State : public Node {
 public:
  State() {};
  State(Transitions *ttp, std::string input, bool isInit) {
    name = input;
    isInitial = isInit;
    tt = ttp;
    numVarUses = 0;
  };
  ~State() {};

  int getNumVarUses() {
    if (tt != NULL)
      numVarUses = numVarUses + tt->getNumVarUses();
    return numVarUses;
  };
  int getNumStates() {
    return 1;
  };
  std::string getStateName() {
    return name;
  };
  bool isInitialState() {
    return isInitial;
  };
  Transitions *getTransitions() {
    if (tt != NULL)
      return tt;
  };

  int setStateMachineTrue(Decl *dp) {
    if (tt != NULL)
      tt->setStateMachineTrue(dp);
    return 0;
  };

 private:
  std::string name;
  bool isInitial;
  Transitions *tt;
  int numVarUses;
  
} ;

class States : public Node {
 public:
  States() {
    numStates = 0;
  };
  States(State *sp, States *ssp) {
    s = sp;
    ss = ssp;
    numStates = 0;
    numVarUses = 0;
  };
  ~States() {};
  int getNumStates() {
    if (s != NULL) 
      numStates = numStates + s->getNumStates();
    if (ss != NULL)
      numStates = numStates + ss->getNumStates();
    return numStates;
  };
  int getNumVarUses() {
    if (s != NULL)
      numVarUses = numVarUses + s->getNumVarUses();
    if (ss != NULL)
      numVarUses = numVarUses + ss->getNumVarUses();
    return numVarUses;
  };
  State *getCurrentState() {
    if (s != NULL)
      return s;
  };
  States *getNextStates() {
    if (ss != NULL)
      return ss;
  };

  int setStateMachineTrue(Decl *dp) {
    if (s != NULL)
      s->setStateMachineTrue(dp);
    if (ss != NULL)
      ss->setStateMachineTrue(dp);
    return 0;
  };

 private:
  std::string name;
  State *s;
  States *ss;
  int numVarUses;
  int numStates;
} ;

class Program : public Node {
 public:
  Program() {};
  Program(std::string input, Platform *pp, Decl *dp, States *ssp) {
    name = input;
    p = pp;
    d = dp;
    if (d != NULL)
      numVarDecls = d->getNumVarDecls();
    else numVarDecls = 0;
    ss = ssp;
    if (ss != NULL)
      numStates = ss->getNumStates();
    else numStates = 0;
    decorateWithEnv();
  };
  ~Program() {};
  std::string getName() {
    return name;
  };
  int getNumStates() {
    return numStates;
  };
  int getNumVarDecls() {
    return numVarDecls;
  };
  int getNumVarUses() {
    if (ss != NULL) {
      numVarUses = ss->getNumVarUses();
      return numVarUses;
    }
    else return 0;
  };

  int decorateWithEnv() {
    if (ss != NULL && d != NULL) {
      Decl* tempDec = d;
      ss->setStateMachineTrue(tempDec);
    }
    return 0;
  };
      

  std::string cppCode_h(){
    std::string ret = string_format("// Generated Machine.h for %s\n\n#include \"RunTime.h\"\n\n// Declarations of the State classes\n", name.c_str()) ;
    
   States *currState = ss;
   State *initialState;

   for (int i = 0; i < numStates; i++) {
     ret.append(string_format("class State_%s ;\n", currState->getCurrentState()->getStateName().c_str()));
      if (currState->getCurrentState()->isInitialState())
	initialState = currState->getCurrentState();
      currState = currState->getNextStates();
    }
   ret.append ("\n\n\n");


   ret.append(string_format("class %s_Machine {\n\tpublic:\n\t%s_Machine( int argc, char **argv ) ;\n\n", name.c_str(), name.c_str()));
   ret.append(string_format("\tvoid go() ;\n\n\t%s *runTime ;\n\n", p->getPlatformName().c_str()));

   ret.append("\t// Machine states\n");
   currState = ss;
   for (int i = 0; i < numStates; i++) {
     ret.append(string_format("\tState_%s *state_%s ;\n", currState->getCurrentState()->getStateName().c_str(), currState->getCurrentState()->getStateName().c_str()));
     currState = currState->getNextStates();
   }
   ret.append(string_format("\n"));

   Decl *currDec = d;
   for (int c = 0; c < numVarDecls; c++) {
     ret.append(string_format("\tint Var_%s ;\n", currDec->getName().c_str()));
     currDec = currDec->getNextDecl();
   }
   
   ret.append("} ;\n\n");

   ret.append(string_format("class %sState : public MachineState {\n\tpublic:\n\t%s_Machine *stateMachine ;\n} ;\n\n", name.c_str(), name.c_str()));
  
   ret.append("// Concrete machine states\n");
   currState = ss;
   for (int i = 0; i < numStates; i++) {
     ret.append(string_format("class State_%s : public %sState {\n\tpublic:\n\tMachineState *enter() ;\n\tState_%s ( %s_Machine *m ) ;\n} ;\n\n", currState->getCurrentState()->getStateName().c_str(), name.c_str(), currState->getCurrentState()->getStateName().c_str(), name.c_str()));
     currState = currState->getNextStates();
   }

   return ret;
  };
     

  std::string cppCode_cpp(){
    std::string ret = string_format("// Generated Machine.cpp for %s\n\n#include \"Machine.h\"\nusing namespace std ;", name.c_str());
    ret.append(string_format("\n%s_Machine::%s_Machine (int argc, char **argv) {\n", name.c_str(), name.c_str()));
    ret.append(string_format("\trunTime = new %s(argc, argv) ;\n\t// Creating state objects\n", p->getPlatformName().c_str()));

    States *currState = ss;
    State *initialState;
    for (int i = 0; i < numStates; i++) {
      ret.append(string_format("\tstate_%s = new State_%s(this) ;\n", currState->getCurrentState()->getStateName().c_str(), currState->getCurrentState()->getStateName().c_str()));
      if (currState->getCurrentState()->isInitialState())
	initialState = currState->getCurrentState();
      currState = currState->getNextStates();
    }
    ret.append("}\n\n");

    ret.append(string_format("void %s_Machine::go() {\n\trunTime->run( state_%s );\n}\n\n", name.c_str(), initialState->getStateName().c_str()));

    ret.append("// Concrete machine states\n");
    currState = ss;
    for (int i = 0; i < numStates; i++) {
      ret.append(string_format("MachineState *State_%s::enter() {\n", currState->getCurrentState()->getStateName().c_str()));
      
      Transitions *currTrans = currState->getCurrentState()->getTransitions();
      int numTransitions = currTrans->getNumTransitions();
      for (int t = 0; t < numTransitions; t++) {
	ret.append(string_format("\tif ( %s ) {\n", currTrans->getCurrentTransition()->getExpr().c_str()));

	Stmts *currStmt = currTrans->getCurrentTransition()->getStmts();
	int numStmts;
	if (currStmt != NULL)
	  numStmts = currStmt->getNumStmts();
	else numStmts = 0;
	for (int s = 0; s < numStmts; s++) {
	  ret.append(string_format("\t\t%s = %s ;\n", currStmt->getCurrentStmt()->getVarName().c_str(), currStmt->getCurrentStmt()->getExpr().c_str()));
	  currStmt = currStmt->getNextStmts();
	}

	ret.append(string_format("\n\t\treturn %s ;\n\t}\n\n", currTrans->getCurrentTransition()->getName().c_str()));
	currTrans = currTrans->getNextTransitions();

      }

      ret.append(string_format("}\n\n"));
      ret.append(string_format("State_%s::State_%s ( %s_Machine *m) {\n\tstateMachine = m ;\n}\n\n\n", currState->getCurrentState()->getStateName().c_str(), currState->getCurrentState()->getStateName().c_str(), name.c_str()));

      currState = currState->getNextStates();

    }

    ret.append(string_format("// A 'main' program to run the state machine.\nint main (int argc, char **argv) {\n\t%s_Machine *%s = new %s_Machine (argc, argv) ;\n\t%s->go() ;\n}", name.c_str(), name.c_str(), name.c_str(), name.c_str()));
    
    return ret;
  };
  
 private:
  std::string name;
  int numStates;
  int numVarDecls;
  int numVarUses;
  Platform *p;
  Decl *d;
  States *ss;

} ;

#endif /* AST_H */
