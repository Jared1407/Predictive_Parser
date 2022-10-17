#include "execute.h"
#include "lexer.h"
#include "execute.h"

using namespace std;

//Helper Functions
Token expect(TokenType expected_type);

void parse_and_generate_AST();
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



void parse_and_type_check();
instNode* parse_and_generate_statement_list();
