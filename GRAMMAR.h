//
// Created by newvl on 12/19/2020.
//

#ifndef COMPLIERC_GRAMMAR_H
#define COMPLIERC_GRAMMAR_H
#include "lex.yy.c"

int parse();

int func();
int statement();
int block();

int loop();
int forLoop();
int whileLoop();
int loopStatement();
int forDec();


int A();

int term(enum TOKENS tok);

int logicalExpr();
int logicalExpr1();
int logicalExpr2();
int logicalExpr3();

int E();
int E1();
int E2();

int iterator();

int T();
int T1();
int T2();
int T3();
int T4();
int T5();

int I();
int I1();
int I2();
int I3();
int I4();
int I5();
int I6();

int funcCall();
int printfCall();

int jumpExpr();
int jumpExpr1();
int jumpExpr2();
int jumpExpr3();


int param();

int OP();
int OP1();
int OP2();
int OP3();
#endif //COMPLIERC_GRAMMAR_H
