#ifndef __TASKS__
#define __TASKS__

#include "execute.h"
#include "lexer.h"



using namespace std;



//Task 1
void parse_and_generate_AST();
// Parser
class Parser {
public:
    //Helper Functions
    static Token expect(TokenType expected_type);
    static void syntax_error();
    static int precedence(TokenType t);
    //Must be public
    void parse_program();
    int ast_table[12][12] = {
        //        +        -        *        /        (        )        [        .       ]       NUM       ID       $
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

};



//Task 2
void parse_and_type_check();


//Task 3
instNode* parse_and_generate_statement_list();


#endif  // __TASKS__

