#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <string>
#include "tasks.h"
#include "lexer.h"
#include "execute.h"



using namespace std;


//Helper functions
Token Parser::expect(TokenType expected_type)
{
    Token t;

    t = lexer.GetToken();
    if (t.token_type != expected_type)
    {
        cout << "Error: expected token of type " << expected_type << " but got " << t.token_type << endl;
        exit(1);
    }
    return t;
}

void Parser::syntax_error(){
    cout << "SNYATX EORRR" << endl;
    exit(1);
}

TokenType Parser::terminalpeek(stack<stackNode> s){
    //terminal at the top of stack or just below
    //if top is nonterminal
    stack<stackNode> temp = s;
    if(s.top().terminal.token_type == PLUS || s.top().terminal.token_type == MINUS || s.top().terminal.token_type == MULT || s.top().terminal.token_type == DIV || s.top().terminal.token_type == LBRACE || s.top().terminal.token_type == RBRACE || s.top().terminal.token_type == LBRAC || s.top().terminal.token_type == DOT || s.top().terminal.token_type == RBRAC || s.top().terminal.token_type == NUM || s.top().terminal.token_type == ID || s.top().terminal.token_type == END_OF_FILE){
        return s.top().terminal.token_type;
    }
    else{
        temp.pop();
        return temp.top().terminal.token_type;
    }

}

bool Parser::is_terminal(TokenType t){
    if(t == PLUS || t == MINUS || t == MULT || t == DIV || t == LBRACE || t == RBRACE || t == LBRAC || t == RBRAC || t == DOT || t == NUM || t == ID || t == END_OF_FILE){
        return true;
    }else{
        return false;
    }
}

int Parser::precedence(TokenType t) {
    if(t == PLUS) {
        return 0;
    }else if(t == MINUS){
        return 1;
    }else if(t == MULT){
        return 2;
    }else if(t == DIV){
        return 3;
    }else if(t == LPAREN){
        return 4;
    }else if(t == RPAREN){
        return 5;
    }else if(t == LBRAC){
        return 6;
    }else if(t == DOT){
        return 7;
    }else if(t == RBRAC){
        return 8;
    }else if(t == NUM){
        return 9;
    }else if(t == ID){
        return 10;
    }else if(t == END_OF_FILE) {
        return 11;
    }else{
        return -1;
    }
}


// Task 1
void Parser::parse_primary() {
    //-> ID
    //-> NUM
    Token t;
    t = lexer.peek(1);
    if(t.token_type == ID || t.token_type == NUM){
        expect(t.token_type);
    }else{
        syntax_error();
    }

}

void Parser::parse_expr(){
    //W.I.P
    //-> expr MINUS expr
    //-> expr PLUS expr
    //-> expr MULT expr
    //-> expr DIV expr
    //-> LPAREN expr RPAREN
    //-> expr LBRAC expr RBRAC
    //-> expr LBRAC DOT RBRAC
    //-> primary
    // Use operative precedence parsing

    //Input is a string W
    //Output is an abstract syntax tree E
    //Initially stack contains $, scanner reads start of W

    //Initialize stack
    //Stack will use dataype stackNode created in tasks.h
    stack<stackNode> s;

    //Initialize input
    Token t, a1, b1;
    int a, b;
    // a and b
    Token test = lexer.peek(1);
    cout << "expr" << endl;
    test.Print();


    /*// get a token
    t = lexer.GetToken();

    // while end of input is not reached
    while (t.token_type != SEMICOLON)
    {
        t.Print();         	// pringt token
        t = lexer.GetToken();	// and get another one
    }*/

    //Push $ onto stack
    // Create a stackNode for eof
    stackNode* eof = new stackNode();
    eof->terminal.token_type = END_OF_FILE;
    eof->terminal.lexeme = "$";
    eof->enumType = 1;
    s.push(*eof);


    while(!s.empty()) {

        if (s.top().terminal.token_type == END_OF_FILE && lexer.peek(1).token_type == END_OF_FILE) {
            //If stack is empty, then input is accepted
            return;
        } else {
            t = lexer.peek(1);
            b1 = t;
            a1.token_type = terminalpeek(s);
            a = precedence(a1.token_type); // a = terminal at top of stack or just below if top != terminal
            b = precedence(b1.token_type); // b = next token in input
            cout << char(ast_table[a][b]) << endl;
            if (ast_table[a][b] == '<' || ast_table[a][b] == '=') {
                stackNode *temp = new stackNode();
                t = lexer.GetToken();
                temp->terminal = t;
                temp->enumType = 1;
                s.push(*temp);
                cout << "pushed " << t.lexeme << endl;
            } else if (ast_table[a][b] == '>') {
                //Reduce
                stack<stackNode> RHS;
                Token lastpoped;
                string ruleToCheck = "";
                while (true) {
                    stackNode temp2 = s.top();
                    s.pop(); // pop both terminals and nonterminals

                    if (temp2.enumType == 1){
                        lastpoped = temp2.terminal;
                    }
                    RHS.push(temp2);
                    if((s.top().enumType == 1)  && ast_table[precedence(terminalpeek(s))][precedence(lastpoped.token_type)] == '<'){
                        false;
                    }

                }
               /* if () {
                    //reduce
                }*/


                // if E-> RHS is a production, then reduce E -> RHS
                // and stack.push(E)
                // else syntax_error();

            } else {
                syntax_error();
            }
        }
    }
}

// Parse_variable access may not be a necessary function as it has already been
// implemented in parse_assign_stmt
void Parser::parse_variable_access(){
    //-> ID
    //-> ID LBRAC expr RBRAC
    //-> ID LBRAC DOT RBRAC
    Token t, t2;
    t = lexer.peek(1);
    t2 = lexer.peek(2);
    if(t.token_type == ID){
        expect(ID);
        if(t2.token_type == LBRAC){
            expect(LBRAC);
            t = lexer.peek(1);
            if(t.token_type == DOT){
                expect(DOT);
                expect(RBRAC);
            }else if(t.token_type == ID || t.token_type == NUM){
                parse_expr();
                expect(RBRAC);
            }else{
                syntax_error();
            }
        }
    }else{
        syntax_error();
    }
}

void Parser::parse_output_stmt(){
    //-> OUTPUT variable-access SEMICOLON
    //W.I.P
    Token t;
    t = lexer.peek(1);
    if(t.token_type == OUTPUT){
        expect(OUTPUT);
        parse_variable_access();
        cout << "output_stmt" << endl;
        expect(SEMICOLON);
    }else{
        syntax_error();
    }
}

void Parser::parse_assign_stmt(){
    //-> variable-access EQUAL expr SEMICOLON
    // Variable access can be completely implemented through assign stmt so no need for variable access. Right?
    //Done I believe
    Token preExpect = lexer.peek(1);
    Token preExpect2 = lexer.peek(2);
    cout << "assign stmt" << endl;
    preExpect.Print();
    preExpect2.Print();

    expect(ID);
    Token t1, t2;
    t1 = lexer.peek(1);
    t2 = lexer.peek(2);
    if(t1.token_type == LBRAC && t2.token_type == DOT){
        expect(LBRAC);
        expect(DOT);
        expect(RBRAC);

    }else if(t1.token_type == LBRAC && (t2.token_type == ID || t2.token_type == NUM || t2.token_type == LPAREN)){
        expect(LBRAC);
        parse_expr();
        expect(RBRAC);
    }

    expect(EQUAL);
    parse_expr();
    cout << "end of assign stmt" << endl;
    expect(SEMICOLON);

}


void Parser::parse_stmt(){
    //-> assign-stmt
    //-> output-stmt
    Token test = lexer.peek(1);
    cout << "stmt" << endl;
    test.Print();
    Token t;
    t = lexer.peek(1);
    if(t.token_type == ID){
        parse_assign_stmt();
    }else if(t.token_type == OUTPUT){
        parse_output_stmt();
    } else{
        cout << "stmt syntax error" << endl;
        syntax_error();
    }
}

void Parser::parse_stmt_list() {
    //-> stmt
    //-> stmt stmt-list
    Token test = lexer.peek(1);
    cout << "stmt list" << endl;
    test.Print();
    Token t, t2;
    t = lexer.peek(1);
    t2 = lexer.peek(2);
    if(t.token_type == ID){
        if(t2.token_type == LBRAC || t2.token_type == LBRACE || t2.token_type == EQUAL){
            parse_stmt();
            parse_stmt_list();
        }
    }else if(t.token_type == OUTPUT){
        parse_stmt();
        parse_stmt_list();
    }else if(t.token_type == RBRACE){
        return;
    }else{
        cout << "stmt_list syntax error" << endl;
        syntax_error();
    }
}

void Parser::parse_block() {
    //-> LBRACE stmt-list RBRACE
    Token test = lexer.peek(1);
    cout << "block" << endl;
    test.Print();
    expect(LBRACE);
    Token t;
    t = lexer.peek(1);
    if(t.token_type == ID || t.token_type == OUTPUT){
        parse_stmt_list();
        expect(RBRACE);
    }else if(t.token_type == END_OF_FILE){
        return;
    }else{
        cout << "block syntax error" << endl;
        syntax_error();
    }
}

void Parser::parse_id_list(){
    //-> ID
    //-> ID id-list
    Token test = lexer.peek(1);
    cout << "id list" << endl;
    test.Print();
    expect(ID);
    Token t;
    t = lexer.peek(1);
    if(t.token_type == ID){
        parse_id_list();
    }else if(t.token_type == LBRACE || t.token_type == ARRAY) {
        return;
    }else{
        cout <<"id list syntax error" << endl;
        syntax_error();
    }
}

void Parser::parse_array_decl_section(){
    //-> ARRAY id-list
    Token t;
    t = lexer.peek(1);
    if(t.token_type == ARRAY){
        expect(ARRAY);
        parse_id_list();
    }else if(t.token_type == LBRACE){
        return;
    }else{
        cout << "array decl section syntax error" << endl;
        syntax_error();
    }
}

void Parser::parse_scalar_decl_section(){
    //-> SCALAR id-list
    Token t;
    t = lexer.peek(1);
    cout << "scalar decl section" << endl;
    t.Print();
    if(t.token_type == SCALAR){
        expect(SCALAR);
        parse_id_list();
    }else if(t.token_type == ARRAY){
        return;
    }else{
        cout << "scalar decl section syntax error" << endl;
        syntax_error();
    }
}

void Parser::parse_decl_section(){
    //-> scalar-decl-section array-decl-section
    Token t;
    t = lexer.peek(1);
    if(t.token_type == SCALAR) {
        parse_scalar_decl_section();
        parse_array_decl_section();
    }else if(t.token_type == LBRACE) {
        return;
    }else{
        cout << "decl section syntax error" << endl;
        syntax_error();
    }

}

void Parser::parse_program(){
    //-> decl-section block
    Token t;
    t = lexer.peek(1);
    cout << "Parsing program" << endl;
    t.Print();
    if(t.token_type == SCALAR) {
        parse_decl_section();
        parse_block();
    }else if(t.token_type == END_OF_FILE){
        return;
    }
}


void Parser::readAndPrintAllInput()
{
    Token t;

    // get a token
    t = lexer.GetToken();

    // while end of input is not reached
    while (t.token_type != END_OF_FILE)
    {
        t.Print();         	// pringt token
        t = lexer.GetToken();	// and get another one
    }

    // note that you should use END_OF_FILE and not EOF
}

void parse_and_generate_AST() {
    //Parse the program
    cout << "1" << endl;
    Parser parser;

    //parser.readAndPrintAllInput();

    parser.parse_program();

}
// Task 2
void parse_and_type_check()
{
	//cout << "2" << endl;
}

// Task 3
instNode* parse_and_generate_statement_list()
{
    //cout << "3" << endl;

    // The following is the hardcoded statement list 
    // generated for a specific program
    // you should replace this code with code that parses the
    // input and generayes a statement list
    // 
    // program
    // SCALAR a b c d
    // ARRAY x y z
    // a = 1;
    // b = 2;
    // c = 3;
    // d = (a+b)*(b+c);
    // OUTPUT d;
    // x[a+b] = d;
    // OUTPUT x[3];
    //
    //  a will be at location 0
    //  b will be at location 1
    //  c will be at location 2
    //  d will be at location 3
    //  x will be at location 4 - 13
    //  y will be at location 14 - 23
    //  z will be at location 24 - 33
    //  t1 will be at location 34 : intermediate value for (a+b)
    //  t2 will be at location 35 : intermediate value for (b+c)
    //  t3 will be at location 36 : intermediate value (a+b)*(b+c)
    //  t4 will be at location 37 : intermediate value for a+b index of array
    //  t5 will be at location 38 : intermediate value for addr of x[a+b] =
    //                              address_of_x + value of a+b =
    //                              4 + value of a+b
    //  t6 will be at location 39 : intermediate value for addr of x[3] =
    //                              address_of_x + value of 3 =
    //                              4 + value of 3 (computation is not done at
    //                              compile time)
    //
    instNode * i01 = new instNode();
    i01->lhsat=DIRECT; i01->lhs = 0;    // a
    i01->iType=ASSIGN_INST;             // =
    i01->op1at=IMMEDIATE; i01->op1 = 1; // 1
    i01->oper = OP_NOOP;                // no operator

    instNode * i02 = new instNode();
    i02->lhsat=DIRECT; i02->lhs = 1;    // b
    i02->iType=ASSIGN_INST;             // =
    i02->op1at=IMMEDIATE; i02->op1 = 2; // 2
    i02->oper = OP_NOOP;                // no operator

    i01->next = i02;

    instNode * i03 = new instNode();
    i03->lhsat=DIRECT; i03->lhs = 2;    // c
    i03->iType=ASSIGN_INST;             // =
    i03->op1at=IMMEDIATE; i03->op1 = 3; // 3
    i03->oper = OP_NOOP;                // no operator

    i02->next = i03;


    instNode * i1 = new instNode();
    i1->lhsat=DIRECT; i1->lhs = 34; // t1
    i1->iType=ASSIGN_INST;          // =
    i1->op1at=DIRECT; i1->op1 = 0;  // a
    i1->oper = OP_PLUS;             // +
    i1->op2at=DIRECT; i1->op2 = 1;  // b

    i03->next = i1;

    instNode * i2 = new instNode();
    i2->lhsat=DIRECT; i2->lhs = 35; // t2
    i2->iType=ASSIGN_INST;          // =
    i2->op1at=DIRECT; i2->op1 = 1;  // b
    i2->oper = OP_PLUS;             // +
    i2->op2at=DIRECT; i2->op2 = 2;  // c

    i1->next = i2;

    instNode * i3 = new instNode();
    i3->lhsat=DIRECT; i3->lhs = 36; // t3
    i3->iType=ASSIGN_INST;          // =
    i3->op1at=DIRECT; i3->op1 = 34;  // t1
    i3->oper = OP_MULT;             // *
    i3->op2at=DIRECT; i3->op2 = 35;  // t2


    i2->next = i3;                  // i3 should be after i1 and i2

    instNode * i4 = new instNode();
    i4->lhsat=DIRECT; i4->lhs = 3;  // d
    i4->iType=ASSIGN_INST;          // =
    i4->op1at=DIRECT; i4->op1 = 36; // t3
    i4->oper = OP_NOOP;             // no operator


    i3->next = i4;

    instNode * i5 = new instNode();
    i5->iType=OUTPUT_INST;          // OUTPUT
    i5->op1at=DIRECT; i5->op1 = 3;  // d

    i4->next = i5;

    instNode * i6 = new instNode();
    i6->lhsat=DIRECT; i6->lhs = 37; // t4
    i6->iType=ASSIGN_INST;          // =
    i6->op1at=DIRECT; i6->op1 = 0;  // a
    i6->oper = OP_PLUS;             // +
    i6->op2at=DIRECT; i6->op2 = 1;  // b
    i5->next = i6;

    instNode * i7 = new instNode();
    i7->lhsat=DIRECT; i7->lhs = 38;    // t5
    i7->iType=ASSIGN_INST;             // =
    i7->op1at=IMMEDIATE; i7->op1 = 4;  // address of x = 4 available
                                       // at compile time
    i7->oper = OP_PLUS;                // +
    i7->op2at=DIRECT; i7->op2 = 37;    // t5 (contains value of a+b

    i6->next = i7;

    instNode * i8 = new instNode();
    i8->lhsat=INDIRECT; i8->lhs = 38;  // x[a+b]
    i8->iType=ASSIGN_INST;             // =
    i8->op1at=DIRECT; i8->op1 = 3;     // d
    i8->oper = OP_NOOP;

    i7->next = i8;

    instNode * i9 = new instNode();
    i9->lhsat=DIRECT; i9->lhs = 39;    // t6 will contain address of x[3]
    i9->iType=ASSIGN_INST;             // =
    i9->op1at=IMMEDIATE; i9->op1 = 4;  // address of x = 4 available
                                       // at compile time
    i9->oper = OP_PLUS;                // +
    i9->op2at=IMMEDIATE; i9->op2 = 3;  // 3

    i8->next = i9;

    instNode * i10 = new instNode();
    i10->iType=OUTPUT_INST;              // OUTPUT
    i10->op1at=INDIRECT; i10->op1 = 39;  // x[3] by providing its
                                         // address indirectly through
                                         // t6

    i9->next = i10;


    instNode* code = i01;

    return code;
}



