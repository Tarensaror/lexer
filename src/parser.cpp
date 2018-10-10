#include "parser.h"
void Parser::parse(Vector<Token> tokens) {
    //ParseTree tree;
    Vector<GrammarCharacter> production_stack;
    production_stack.emplace_back(GrammarVariable::PROG);

    for(const Token& token : tokens) {
        const GrammarCharacter& top_element = production_stack.pop_back();
        if (top_element.is_grammar_variable()) {
            Vector<GrammarCharacter> production = parse_table[static_cast<std::size_t>(token.type)][static_cast<std::size_t>(top_element.get_grammar_variable())];
        } else {
            throw ParserException("Non-variable element on stack.");
        }
    }
}

void Parser::initializeParseTable() {
    parse_table[static_cast<std::size_t>(TokenType::PLUS)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::PLUS)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::PLUS)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::PLUS))};
	parse_table[static_cast<std::size_t>(TokenType::MINUS)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::MINUS)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::MINUS)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::MINUS))};
	parse_table[static_cast<std::size_t>(TokenType::COLON)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::COLON)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::COLON)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::COLON))};
	parse_table[static_cast<std::size_t>(TokenType::ASTERISK)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::ASTERISK)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::ASTERISK)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::ASTERISK))};
	parse_table[static_cast<std::size_t>(TokenType::LESS_THAN)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::LESS_THAN)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::LESS_THAN)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::LESS_THAN))};
	parse_table[static_cast<std::size_t>(TokenType::GREATER_THAN)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::GREATER_THAN)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::GREATER_THAN)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::GREATER_THAN))};
	parse_table[static_cast<std::size_t>(TokenType::EQUALITY)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::EQUALITY)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::EQUALITY)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::EQUALITY))};
	parse_table[static_cast<std::size_t>(TokenType::ASSIGNMENT)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::WHATEVER)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::WHATEVER)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::WHATEVER)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::WHATEVER))};
	parse_table[static_cast<std::size_t>(TokenType::NOT)]
        [static_cast<std::size_t>(GrammarVariable::EXP)] = {(GrammarCharacter(GrammarVariable::EXP_2), GrammarCharacter(GrammarVariable::OP_EXP))};
	parse_table[static_cast<std::size_t>(TokenType::NOT)]
        [static_cast<std::size_t>(GrammarVariable::EXP_2)] = {(GrammarCharacter(TokenType::NOT), GrammarCharacter(GrammarVariable::EXP_2))};
	parse_table[static_cast<std::size_t>(TokenType::LOGICAL_AND)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::LOGICAL_AND)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::LOGICAL_AND)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::LOGICAL_AND))};
	parse_table[static_cast<std::size_t>(TokenType::SEMICOLON)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::PARENTHESIS_OPEN)]
        [static_cast<std::size_t>(GrammarVariable::EXP)] = {(GrammarCharacter(GrammarVariable::EXP_2), GrammarCharacter(GrammarVariable::OP_EXP))};
	parse_table[static_cast<std::size_t>(TokenType::PARENTHESIS_OPEN)]
        [static_cast<std::size_t>(GrammarVariable::EXP_2)] = {(GrammarCharacter(TokenType::PARENTHESIS_OPEN), GrammarCharacter(GrammarVariable::EXP), GrammarCharacter(TokenType::PARENTHESIS_CLOSE))};
	parse_table[static_cast<std::size_t>(TokenType::PARENTHESIS_CLOSE)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::CURLY_BRACKET_OPEN)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::CURLY_BRACKET_OPEN)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(GrammarVariable::STATEMENT), GrammarCharacter(TokenType::SEMICOLON), GrammarCharacter(GrammarVariable::STATEMENTS))};
	parse_table[static_cast<std::size_t>(TokenType::CURLY_BRACKET_OPEN)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENT)] = {(GrammarCharacter(TokenType::CURLY_BRACKET_OPEN), GrammarCharacter(GrammarVariable::STATEMENTS), GrammarCharacter(TokenType::CURLY_BRACKET_CLOSE))};
	parse_table[static_cast<std::size_t>(TokenType::CURLY_BRACKET_CLOSE)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
    parse_table[static_cast<std::size_t>(TokenType::SQUARE_BRACKET_OPEN)]
        [static_cast<std::size_t>(GrammarVariable::PROG)] = {(GrammarCharacter(TokenType::SQUARE_BRACKET_OPEN), GrammarCharacter(TokenType::INTEGER), GrammarCharacter(TokenType::SQUARE_BRACKET_CLOSE))};
	parse_table[static_cast<std::size_t>(TokenType::SQUARE_BRACKET_OPEN)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(TokenType::SQUARE_BRACKET_OPEN), GrammarCharacter(GrammarVariable::EXP), GrammarCharacter(TokenType::SQUARE_BRACKET_CLOSE))};
	parse_table[static_cast<std::size_t>(TokenType::SQUARE_BRACKET_CLOSE)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::INTEGER)]
        [static_cast<std::size_t>(GrammarVariable::EXP)] = {(GrammarCharacter(GrammarVariable::EXP_2), GrammarCharacter(GrammarVariable::OP_EXP))};
	parse_table[static_cast<std::size_t>(TokenType::INTEGER)]
        [static_cast<std::size_t>(GrammarVariable::EXP_2)] = {(GrammarCharacter(TokenType::INTEGER))};
	parse_table[static_cast<std::size_t>(TokenType::IDENTIFIER)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::IDENTIFIER)]
        [static_cast<std::size_t>(GrammarVariable::ARRAY)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::IDENTIFIER)]
        [static_cast<std::size_t>(GrammarVariable::EXP)] = {(GrammarCharacter(GrammarVariable::EXP_2), GrammarCharacter(GrammarVariable::OP_EXP))};
	parse_table[static_cast<std::size_t>(TokenType::IDENTIFIER)]
        [static_cast<std::size_t>(GrammarVariable::EXP_2)] = {(GrammarCharacter(TokenType::IDENTIFIER), GrammarCharacter(GrammarVariable::INDEX))};
	parse_table[static_cast<std::size_t>(TokenType::IF)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::IF)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(GrammarVariable::STATEMENT), GrammarCharacter(TokenType::SEMICOLON), GrammarCharacter(GrammarVariable::STATEMENTS))};
	parse_table[static_cast<std::size_t>(TokenType::IF)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENT)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::ELSE)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(GrammarVariable::STATEMENT), GrammarCharacter(TokenType::SEMICOLON), GrammarCharacter(GrammarVariable::STATEMENTS))};
	parse_table[static_cast<std::size_t>(TokenType::ELSE)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::WHILE)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::WHILE)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(GrammarVariable::STATEMENT), GrammarCharacter(TokenType::SEMICOLON), GrammarCharacter(GrammarVariable::STATEMENTS))};
	parse_table[static_cast<std::size_t>(TokenType::WHILE)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENT)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::READ)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::READ)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(GrammarVariable::STATEMENT), GrammarCharacter(TokenType::SEMICOLON), GrammarCharacter(GrammarVariable::STATEMENTS))};
	parse_table[static_cast<std::size_t>(TokenType::READ)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENT)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::WRITE)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::WRITE)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(GrammarVariable::STATEMENT), GrammarCharacter(TokenType::SEMICOLON), GrammarCharacter(GrammarVariable::STATEMENTS))};
	parse_table[static_cast<std::size_t>(TokenType::WRITE)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(GrammarVariable::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::INT)]
        [static_cast<std::size_t>(GrammarVariable::PROG)] = {(GrammarCharacter(GrammarVariable::DECLS), GrammarCharacter(GrammarVariable::STATEMENTS))};
	parse_table[static_cast<std::size_t>(TokenType::INT)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(GrammarVariable::DECL), GrammarCharacter(TokenType::SEMICOLON), GrammarCharacter(GrammarVariable::DECLS))};
	parse_table[static_cast<std::size_t>(TokenType::INT)]
        [static_cast<std::size_t>(GrammarVariable::DECL)] = {(GrammarCharacter(TokenType::INT), GrammarCharacter(GrammarVariable::ARRAY), GrammarCharacter(TokenType::IDENTIFIER))};
}
