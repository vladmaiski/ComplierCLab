
#include "GRAMMAR.h"

int term(enum TOKENS tok) {
    return (*tokens++).type == tok;
}

int parse() {
    return func();
}

int func() {
    return term(TYPE) && term(ID) && term(OPEN) && term(CLOSE) && statement();
}

int statement() {
    return (term(OPEN_F) && block() && term(CLOSE_F));
}

int block() {
    TOKEN *save = tokens;
    if (A() && block())
        return 1;

    tokens = save;
    if (A())
        return 1;

    tokens = save;
    if (loop() && block())
        return 1;

    tokens = save;
    if (loop())
        return 1;

    tokens = save;
    if (funcCall() && block())
        return 1;

    tokens = save;
    if (funcCall())
        return 1;

    tokens = save;
    if (jumpExpr() && block())
        return 1;

    tokens = save;
    if (jumpExpr())
        return 1;

    tokens = save;
    return 0;
}

int jumpExpr() {
    TOKEN *save = tokens;
    return ((tokens = save, jumpExpr1()) || (tokens = save, jumpExpr2())
            || (tokens = save, jumpExpr3()));
}

int jumpExpr1() {
    return term(RET) && term(VAL) && term(SEM);
}

int jumpExpr2() {
    return term(CONTINUE) && term(SEM);
}

int jumpExpr3() {
    return term(BREAK) && term(SEM);
}

int funcCall() {
    TOKEN *save = tokens;
    if (term(PRINTF) && term(OPEN) && printfCall() && term(CLOSE) && term(SEM))
        return 1;

    tokens = save;
    return 0;
}

int printfCall() {
    TOKEN *save = tokens;

    if (OP2() && term(COMMA) && printfCall())
        return 1;

    tokens = save;
    if (OP2())
        return 1;

    tokens = save;
    if(term(STRING_LITERAL) && term(COMMA) && printfCall())
        return 1;

    tokens = save;
    if(term(STRING_LITERAL))
        return 1;

    tokens = save;
    return 0;
}

int loop() {
    TOKEN *save = tokens;
    return ((tokens = save, forLoop()) || (tokens = save, whileLoop()));
}

int whileLoop() {
    return (term(WHILE) && term(OPEN) && logicalExpr() && term(CLOSE) && statement());
}

int forLoop() {
    return (term(FOR) && term(OPEN) && forDec() && term(CLOSE) && statement());
}

int forDec() {
    return I2() && term(SEM) && logicalExpr() && term(SEM) && iterator();
}

int iterator() {
    TOKEN *save = tokens;
    return ((tokens = save, I3()) || (tokens = save, I4())
            || (tokens = save, I5()));
}

int logicalExpr(){
    TOKEN *save = tokens;
    return ((tokens = save, logicalExpr1()) || (tokens = save, logicalExpr2())
            || (tokens = save, logicalExpr3()));
}

int logicalExpr1(){
    return OP2() && term(LOGICAL) && OP();
}

int logicalExpr2(){
    return OP2();
}

int logicalExpr3(){
    return term(NEQ) && OP2();
}

int A() {
    return ((I() || E()) && term(SEM));
}

int E1() { return T() && term(PLMIN) && E(); }

int E2() { return T(); }

int E() {
    TOKEN *save = tokens;
    return ((tokens = save, E1()) || (tokens = save, E2()));
}


int T1() { return OP() && term(TIMDIV) && T(); }

int T3() { return (term(OPEN) && E() && term(CLOSE) && term(TIMDIV) && T()); }

int T4() { return (term(OPEN) && E() && term(CLOSE)); }

int T5() { return (OP()); }

int T() {
    TOKEN *save = tokens;
    return ((tokens = save, T1()) || (tokens = save, T3())
            || (tokens = save, T4()) || (tokens = save, T5()));
}

int I() {
    TOKEN *save = tokens;
    return ((tokens = save, I2()) || (tokens = save, I1()) ||
    (tokens = save, I3()) || (tokens = save, I4()) ||
    (tokens = save, I5()) || (tokens = save, I6()));
}

int I1() {
    return (term(TYPE) && term(ID));
}

int I2() {
    int res = (term(TYPE) && term(ID) && term(EQ) && E());
    return res;
}

int I3() {
    return (term(ID) && term(EQ) && E());
}

int I4() {
    return (term(INCDEC) && term(ID));
}

int I5() {
    return (term(ID) && term(INCDEC));
}

int I6() {
    return (term(ID) && term(SPEC_EQ) && E());
}

int OP() {
    TOKEN *save = tokens;
    return ((tokens = save, OP3()) || (tokens = save, OP1()) || (tokens = save, OP2()));
}

int param() {
    TOKEN *save = tokens;
    if (OP() && term(COMMA) && param())
        return 1;

    tokens = save;
    if (OP())
        return 1;

    tokens = save;
    return 0;
}

int OP3() {
    return (term(ID) && term(OPEN) && param() && term(CLOSE));
}

int OP1() {
    return (term(VAL));
}

int OP2() {
    return (term(ID));
}