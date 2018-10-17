#include "parser.h"
bool Parser::parse(const Token& token) {
    while (this->is_valid) {
        if (this->production_stack.size() == 0) {
            Vector<GrammarCharacter> production = this->parse_table[static_cast<std::size_t>(TokenType::EPSILON)][static_cast<std::size_t>(this->last_parent.get_character().get_grammar_variable())];
            if (production.size() == 0 || (production.size() == 1 && !production.pop_back().is_token_type() && production.pop_back().get_token_type() != TokenType::EPSILON)) {
                this->is_valid = false;
                throw SyntaxErrorException(token);
            }
        } else {
            const GrammarCharacter& top_element = this->production_stack.pop_back();
            if (top_element.get_token_type() == TokenType::EPSILON) {
                current = this->last_parent.add_child(top_element);
                this->last_parent = this->last_parent.get_parent();
            } else if (top_element.is_grammar_variable()) {
                Vector<GrammarCharacter> production = this->parse_table[static_cast<std::size_t>(token.type)][static_cast<std::size_t>(top_element.get_grammar_variable())];
                if (production.size() == 0) {
                    this->is_valid = false;
                    throw SyntaxErrorException(token);
                }
                for(Vector<GrammarCharacter>::const_reverse_iterator iter = production.rbegin(), end = production.rend(); iter != end; ++iter) {
                    this->production_stack.push_back(*iter);
                }
                // production_stack.insert(production_stack.end(), production.rbegin(), production.rend()); ALTERNATIVE to for-loop
                this->production_stack.push_back(GrammarCharacter(TokenType::EPSILON));

                current = this->last_parent.add_child(top_element);
                this->last_parent = current;
            } else if (top_element.is_token_type()) {
                if (top_element.get_token_type() == token.type) {
                    current = this->last_parent.add_child(top_element);
                } else {
                    this->is_valid = false;
                    throw SyntaxErrorException(token);
                }
                this->last_parent = this->last_parent.get_parent();
            } else {
                this->is_valid = false;
                //throw ParserException(); TODO
            }
        }
    }
    return true;
}

bool Parser::finalize() {
//    const static Token EOF(0, 0, TokenType::EPSILON);
    try {
        if (this->is_valid) {
            while (this->parse(Token(0, 0, TokenType::EPSILON)));

            if (this->production_stack.size() == 0)
                return this->is_valid = true;
            else
                return false;
        }
        return false;
    } catch(const SyntaxErrorException& invalid_stack) {
        throw;
    }
}

void Parser::initializeParseTable() {
    parse_table[static_cast<std::size_t>(TokenType::EPSILON)]
        [static_cast<std::size_t>(GrammarVariable::PROG)] = {(GrammarCharacter(GrammarVariable::DECLS), GrammarCharacter(GrammarVariable::STATEMENTS))};
    parse_table[static_cast<std::size_t>(TokenType::EPSILON)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(TokenType::EPSILON))};
    parse_table[static_cast<std::size_t>(TokenType::EPSILON)]
        [static_cast<std::size_t>(GrammarVariable::ARRAY)] = {(GrammarCharacter(TokenType::EPSILON))};
    parse_table[static_cast<std::size_t>(TokenType::EPSILON)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(TokenType::EPSILON))};
    parse_table[static_cast<std::size_t>(TokenType::EPSILON)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(TokenType::EPSILON))};
    parse_table[static_cast<std::size_t>(TokenType::EPSILON)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(TokenType::EPSILON))};

    parse_table[static_cast<std::size_t>(TokenType::PLUS)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::PLUS)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::PLUS)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::PLUS))};

	parse_table[static_cast<std::size_t>(TokenType::MINUS)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::MINUS)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::MINUS)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::MINUS))};

	parse_table[static_cast<std::size_t>(TokenType::COLON)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::COLON)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::COLON)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::COLON))};

	parse_table[static_cast<std::size_t>(TokenType::ASTERISK)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::ASTERISK)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::ASTERISK)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::ASTERISK))};

	parse_table[static_cast<std::size_t>(TokenType::LESS_THAN)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::LESS_THAN)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::LESS_THAN)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::LESS_THAN))};

	parse_table[static_cast<std::size_t>(TokenType::GREATER_THAN)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::GREATER_THAN)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::GREATER_THAN)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::GREATER_THAN))};

	parse_table[static_cast<std::size_t>(TokenType::EQUALITY)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::EQUALITY)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::EQUALITY)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::EQUALITY))};

	parse_table[static_cast<std::size_t>(TokenType::ASSIGNMENT)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(TokenType::EPSILON))};

	parse_table[static_cast<std::size_t>(TokenType::WHATEVER)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::WHATEVER)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::WHATEVER)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::WHATEVER))};

	parse_table[static_cast<std::size_t>(TokenType::NOT)]
        [static_cast<std::size_t>(GrammarVariable::EXP)] = {(GrammarCharacter(GrammarVariable::EXP_2), GrammarCharacter(GrammarVariable::OP_EXP))};
	parse_table[static_cast<std::size_t>(TokenType::NOT)]
        [static_cast<std::size_t>(GrammarVariable::EXP_2)] = {(GrammarCharacter(TokenType::NOT), GrammarCharacter(GrammarVariable::EXP_2))};

	parse_table[static_cast<std::size_t>(TokenType::LOGICAL_AND)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::LOGICAL_AND)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(GrammarVariable::OP), GrammarCharacter(GrammarVariable::EXP))};
	parse_table[static_cast<std::size_t>(TokenType::LOGICAL_AND)]
        [static_cast<std::size_t>(GrammarVariable::OP)] = {(GrammarCharacter(TokenType::LOGICAL_AND))};

	parse_table[static_cast<std::size_t>(TokenType::SEMICOLON)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(TokenType::EPSILON))};

	parse_table[static_cast<std::size_t>(TokenType::PARENTHESIS_OPEN)]
        [static_cast<std::size_t>(GrammarVariable::EXP)] = {(GrammarCharacter(GrammarVariable::EXP_2), GrammarCharacter(GrammarVariable::OP_EXP))};
	parse_table[static_cast<std::size_t>(TokenType::PARENTHESIS_OPEN)]
        [static_cast<std::size_t>(GrammarVariable::EXP_2)] = {(GrammarCharacter(TokenType::PARENTHESIS_OPEN), GrammarCharacter(GrammarVariable::EXP), GrammarCharacter(TokenType::PARENTHESIS_CLOSE))};

	parse_table[static_cast<std::size_t>(TokenType::PARENTHESIS_CLOSE)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(TokenType::EPSILON))};

	parse_table[static_cast<std::size_t>(TokenType::CURLY_BRACKET_OPEN)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::CURLY_BRACKET_OPEN)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(GrammarVariable::STATEMENT), GrammarCharacter(TokenType::SEMICOLON), GrammarCharacter(GrammarVariable::STATEMENTS))};
	parse_table[static_cast<std::size_t>(TokenType::CURLY_BRACKET_OPEN)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENT)] = {(GrammarCharacter(TokenType::CURLY_BRACKET_OPEN), GrammarCharacter(GrammarVariable::STATEMENTS), GrammarCharacter(TokenType::CURLY_BRACKET_CLOSE))};

	parse_table[static_cast<std::size_t>(TokenType::CURLY_BRACKET_CLOSE)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(TokenType::EPSILON))};

    parse_table[static_cast<std::size_t>(TokenType::SQUARE_BRACKET_OPEN)]
        [static_cast<std::size_t>(GrammarVariable::PROG)] = {(GrammarCharacter(TokenType::SQUARE_BRACKET_OPEN), GrammarCharacter(TokenType::INTEGER), GrammarCharacter(TokenType::SQUARE_BRACKET_CLOSE))};
	parse_table[static_cast<std::size_t>(TokenType::SQUARE_BRACKET_OPEN)]
        [static_cast<std::size_t>(GrammarVariable::INDEX)] = {(GrammarCharacter(TokenType::SQUARE_BRACKET_OPEN), GrammarCharacter(GrammarVariable::EXP), GrammarCharacter(TokenType::SQUARE_BRACKET_CLOSE))};

	parse_table[static_cast<std::size_t>(TokenType::SQUARE_BRACKET_CLOSE)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(TokenType::EPSILON))};

	parse_table[static_cast<std::size_t>(TokenType::INTEGER)]
        [static_cast<std::size_t>(GrammarVariable::EXP)] = {(GrammarCharacter(GrammarVariable::EXP_2), GrammarCharacter(GrammarVariable::OP_EXP))};
	parse_table[static_cast<std::size_t>(TokenType::INTEGER)]
        [static_cast<std::size_t>(GrammarVariable::EXP_2)] = {(GrammarCharacter(TokenType::INTEGER))};

	parse_table[static_cast<std::size_t>(TokenType::IDENTIFIER)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::IDENTIFIER)]
        [static_cast<std::size_t>(GrammarVariable::ARRAY)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::IDENTIFIER)]
        [static_cast<std::size_t>(GrammarVariable::EXP)] = {(GrammarCharacter(GrammarVariable::EXP_2), GrammarCharacter(GrammarVariable::OP_EXP))};
	parse_table[static_cast<std::size_t>(TokenType::IDENTIFIER)]
        [static_cast<std::size_t>(GrammarVariable::EXP_2)] = {(GrammarCharacter(TokenType::IDENTIFIER), GrammarCharacter(GrammarVariable::INDEX))};

	parse_table[static_cast<std::size_t>(TokenType::IF)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::IF)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(GrammarVariable::STATEMENT), GrammarCharacter(TokenType::SEMICOLON), GrammarCharacter(GrammarVariable::STATEMENTS))};
	parse_table[static_cast<std::size_t>(TokenType::IF)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENT)] = {(GrammarCharacter(TokenType::EPSILON))};

	parse_table[static_cast<std::size_t>(TokenType::ELSE)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(GrammarVariable::STATEMENT), GrammarCharacter(TokenType::SEMICOLON), GrammarCharacter(GrammarVariable::STATEMENTS))};
	parse_table[static_cast<std::size_t>(TokenType::ELSE)]
        [static_cast<std::size_t>(GrammarVariable::OP_EXP)] = {(GrammarCharacter(TokenType::EPSILON))};

	parse_table[static_cast<std::size_t>(TokenType::WHILE)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::WHILE)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(GrammarVariable::STATEMENT), GrammarCharacter(TokenType::SEMICOLON), GrammarCharacter(GrammarVariable::STATEMENTS))};
	parse_table[static_cast<std::size_t>(TokenType::WHILE)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENT)] = {(GrammarCharacter(TokenType::EPSILON))};

	parse_table[static_cast<std::size_t>(TokenType::READ)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::READ)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(GrammarVariable::STATEMENT), GrammarCharacter(TokenType::SEMICOLON), GrammarCharacter(GrammarVariable::STATEMENTS))};
	parse_table[static_cast<std::size_t>(TokenType::READ)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENT)] = {(GrammarCharacter(TokenType::EPSILON))};

	parse_table[static_cast<std::size_t>(TokenType::WRITE)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(TokenType::EPSILON))};
	parse_table[static_cast<std::size_t>(TokenType::WRITE)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(GrammarVariable::STATEMENT), GrammarCharacter(TokenType::SEMICOLON), GrammarCharacter(GrammarVariable::STATEMENTS))};
	parse_table[static_cast<std::size_t>(TokenType::WRITE)]
        [static_cast<std::size_t>(GrammarVariable::STATEMENTS)] = {(GrammarCharacter(TokenType::EPSILON))};

	parse_table[static_cast<std::size_t>(TokenType::INT)]
        [static_cast<std::size_t>(GrammarVariable::PROG)] = {(GrammarCharacter(GrammarVariable::DECLS), GrammarCharacter(GrammarVariable::STATEMENTS))};
	parse_table[static_cast<std::size_t>(TokenType::INT)]
        [static_cast<std::size_t>(GrammarVariable::DECLS)] = {(GrammarCharacter(GrammarVariable::DECL), GrammarCharacter(TokenType::SEMICOLON), GrammarCharacter(GrammarVariable::DECLS))};
	parse_table[static_cast<std::size_t>(TokenType::INT)]
        [static_cast<std::size_t>(GrammarVariable::DECL)] = {(GrammarCharacter(TokenType::INT), GrammarCharacter(GrammarVariable::ARRAY), GrammarCharacter(TokenType::IDENTIFIER))};
}
