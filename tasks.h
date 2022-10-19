#ifndef __TASKS__
#define __TASKS__

#include "execute.h"
#include "lexer.h"



using namespace std;




//Task 1
void parse_program();
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


//Helper functions
Token expect(TokenType expected_type);
void syntax_error();
void parse_and_generate_AST();

//Task 2
void parse_and_type_check();


//Task 3
instNode* parse_and_generate_statement_list();


#endif  // __TASKS__

