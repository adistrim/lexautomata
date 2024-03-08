%{
#include <stdio.h>
%}

%{
int IDENTIFIER;
%}

%%
"iostream"|"cmath"|"vector"|"algorithm" { printf("%s is Library\n", yytext); }
"#include"|"using"|"namespace"|"std"|"string"|"return"|"endl"|"cout"|"program"|"block"|"decls"|"decl"|"type"|"stmts"|"stmt"|"if"|"else"|"while"|"do"|"break"|"true"|"false"|"int"|"float"|"main" { printf("%s is a Keyword\n", yytext); BEGIN(IDENTIFIER); }
<IDENTIFIER>[a-zA-Z][a-zA-Z0-9_]* { 
    if (yytext[strlen(yytext) - 1] == ':') {
        printf("%s is a Label\n", yytext);
    } else {
        printf("%s is a Variable\n", yytext);
    }
}
[0-9]+       { printf("%s is an Integer\n", yytext); }
"=="|"!="|"<="|">="|"<"|">"|"+"|"-"|"*"|"/"|"=" { printf("%s is an Operator\n", yytext); }
"("|")"|"{"|"}" { printf("%s is a Special Character\n", yytext); }
";" { printf("%s is a Delimiter\n", yytext); }
\"[^\"\n]*\" { printf("%s is a String\n", yytext); }
[ \t\n]      ; /* skip whitespace */
.            { printf("Invalid token: %s\n", yytext); }
%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    yyin = input_file;
    yylex();

    fclose(input_file);
    return 0;
}
