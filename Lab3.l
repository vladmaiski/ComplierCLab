%option noyywrap

ID[_A-Za-z][A-Za-z_0-9]*


%{
	#include <malloc.h>
	#include <stdio.h>
	#include <string.h>

	int next = 0;
	int linesCounter = 0;

	enum TOKENS{
    		IF = 1, ELSE, OPEN_F, CLOSE_F, OPEN, CLOSE, FOR, WHILE, DO, TYPE,
    		ID, SPACE, VAL, SEM, PLMIN, TIMDIV, EQ, END, INCDEC, OPEN_CUR, CLOSE_CUR,
			LOGICAL, NEQ, SPEC_EQ, COMMA, STRING_LITERAL, PRINTF, RET, CONTINUE, BREAK
	};

	typedef struct TOKEN_ {
   	 	enum TOKENS type;
	} TOKEN;


	TOKEN createToken(enum TOKENS type) {
  	  	TOKEN tok;
   	 	tok.type = type;
    		return tok;
	}


	TOKEN *tokens;
%}

%%	

"int"|"float"|"char"|"double"		{tokens[next++] = createToken(TYPE);} 
"<"|">"|">="|"<="				{tokens[next++] = createToken(LOGICAL);} 
"return"				{tokens[next++] = createToken(RET);} 
"!"				{tokens[next++] = createToken(NEQ);} 
\"([^\\\"]|\\.)*\"  {tokens[next++] = createToken(STRING_LITERAL);}
"+="|"-="|"*="|"/="				{tokens[next++] = createToken(SPEC_EQ);} 
"("				{tokens[next++] = createToken(OPEN);} 
")"				{tokens[next++] = createToken(CLOSE);} 
"{"				{tokens[next++] = createToken(OPEN_F);} 
"}"				{tokens[next++] = createToken(CLOSE_F);} 
"continue"				{tokens[next++] = createToken(CONTINUE);} 
"break"				{tokens[next++] = createToken(BREAK);} 
"if"				{tokens[next++] = createToken(IF);} 
"else"				{tokens[next++] = createToken(ELSE);} 
"for"				{tokens[next++] = createToken(FOR);} 
"do"				{tokens[next++] = createToken(DO);} 
"while"				{tokens[next++] = createToken(WHILE);} 
"printf"				{tokens[next++] = createToken(PRINTF);} 
";"				{tokens[next++] = createToken(SEM);}
"++"|"--"		{tokens[next++] = createToken(INCDEC);}
"+"|"-"				{tokens[next++] = createToken(PLMIN);}
"*"|"/"				{tokens[next++] = createToken(TIMDIV);}
"="				{tokens[next++] = createToken(EQ);}
[\t\r ]+			;
","		{tokens[next++] = createToken(COMMA);}

[0-9]*[.,]?[0-9]+		{tokens[next++] = createToken(VAL);}
{ID}				{tokens[next++] = createToken(ID);}	
.				{return 1;}
<<EOF>>  			{tokens[next++] = createToken(END);; yyterminate();}
%%
