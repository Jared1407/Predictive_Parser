#ifndef __TASKS__
#define __TASKS__

#include "execute.h"
#include "lexer.h"
#include <stack>

using namespace std;

//Task 1
void parse_and_generate_AST();


// Structs
struct exprNode {
    TokenType operatorType; //enum type, ID, PLUS, MINUS, DIV, ARRAY, WHOLE ARRAY

    //int exprType; // expr type, SCALAR, ARRAY, ARRAYDDELC, ERROR, Not used until task 2

    struct { // ID or NUM
        string varName;
        int line_no;
    } id;

    struct { // OPERATOR = PLUS, MINUS, DIV, MULT, ARRAY ELEM
        struct exprNode *left;
        struct exprNode *right;
    } child;

    struct { // OPERATOR == WHOLE ARRAY
        string arrayname;
        int line_no;
    } array;

};




//stackNode
struct stackNode{
    //Store the enum type as EXPR or TERM
    //EXPR = 0, TERM = 1
    int enumType;
    //A stack node can contain an expression or a terminal
    //We will use a union to store either

    struct exprNode expr;
    Token terminal;
};


// Parser
class Parser {
private:
    LexicalAnalyzer lexer;
    //Parsing functions
    void parse_decl_section();
    void parse_scalar_decl_section();
    void parse_array_decl_section();
    void parse_id_list();
    void parse_block();
    void parse_stmt_list();
    void parse_stmt();
    void parse_assign_stmt();
    void parse_output_stmt();
    void parse_variable_access();
    void parse_expr();
    void parse_primary();

    Token expect(TokenType expected_type);



public:
    //expr Rules
    //expr rules
    vector<string> exprRules =
            {
                    "EPLUSE", "EMINUSE", "EMULTE", "EDIVE", "LPARENERPAREN", "ELBRACERBRAC", "ELBRACDOTRBRAC", "ID", "NUM"
            };

    //Helper Functions
    string token_type_to_string(TokenType t);
    Token get_symbol();
    Token peek_symbol();
    void syntax_error();
    int precedence(TokenType t);
    string RHS_to_string(stackNode E);
    stackNode reduce(stack<stackNode> RHS);
    void print_E(exprNode* e);
    //Must be public
    void readAndPrintAllInput();
    void parse_program();
    bool is_terminal(TokenType t);
    TokenType terminalpeek(stack<stackNode> s);



    //AST

    int ast_table[12][12] = {
        //        +        -        *        /       (        )        [        .        ]       NUM       ID        $
        {'>', '>', '<', '<', '<', '>', '<', 'E', '>', '<', '<', '>'},// +
        {'>', '>', '<', '<', '<', '>', '<', 'E', '>', '<', '<', '>'},// -
        {'>', '>', '>', '>', '<', '>', '<', 'E', '>', '<', '<', '>'},// *
        {'>', '>', '>', '>', '<', '>', '<', 'E', '>', '<', '<', '>'},// /
        {'<', '<', '<', '<', '<', '=', '<', 'E', '<', '<', '<', 'E'},// (
        {'>', '>', '>', '>', 'E', '>', '>', 'E', '>', 'E', 'E', '>'},// )
        {'<', '<', '<', '<', '<', '<', '<', '=', '=', '<', '<', 'E'},// [
        {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', '=', 'E', 'E', 'E'},// .
        {'>', '>', '>', '>', 'E', '>', '>', 'E', '>', 'E', 'E', '>'},// ]
        {'>', '>', '>', '>', 'E', '>', '>', 'E', '>', 'E', 'E', '>'},// NUM
        {'>', '>', '>', '>', 'E', '>', '>', 'E', '>', 'E', 'E', '>'},// ID
        {'<', '<', '<', '<', '<', 'E', '<', 'E', 'E', '<', '<', 'A'},// $
    };


};



//Task 2
void parse_and_type_check();


//Task 3
instNode* parse_and_generate_statement_list();


#endif  // __TASKS__

