#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "scanner.h"
#include "token.h"
#include "vector.h"

enum class GrammarVariable : unsigned char {
	ROOT,

	PROG,
	DECLS,
	DECL,
	ARRAY,

	STATEMENT,
	STATEMENTS,
	EXP,
	EXP_2,
	INDEX,
	OP_EXP,
	OP
};

class First {
private:
	Vector<Vector<TokenType>> firsts;

public:
    First();
};

class Follow {
private:
	Vector<Vector<TokenType>> follows;

public:
    Follow();

	Vector<TokenType> get_follows_for_type(GrammarVariable variable) {
		return follows[static_cast<std::size_t>(variable)];
	}
};

class GrammarCharacter {
private:
    enum class characterType {
        VARIABLE,
        TOKEN
    };

    struct GrammarCharacterType { // constructor missing which sets variable
		characterType type;
		union Variable_or_token
		{
			GrammarVariable variable;
			TokenType token;
		} variable_or_token;
	} grammar_character_type;

public:

    GrammarCharacter() {}

    GrammarCharacter(GrammarVariable variable) {
        grammar_character_type.type = characterType::VARIABLE;
        grammar_character_type.variable_or_token.variable = variable;
    }

    GrammarCharacter(TokenType token) {
        grammar_character_type.type = characterType::TOKEN;
        grammar_character_type.variable_or_token.token = token;
    }

    void set_grammar_variable(GrammarVariable variable) {
        grammar_character_type.type = characterType::VARIABLE;
        grammar_character_type.variable_or_token.variable = variable;
    }

    void set_token_type(TokenType token) {
        grammar_character_type.type = characterType::TOKEN;
        grammar_character_type.variable_or_token.token = token;
    }

   bool is_grammar_variable () const {
       return grammar_character_type.type == characterType::VARIABLE;
   }

   bool is_token_type ()  const {
       return grammar_character_type.type == characterType::TOKEN;
   }

   GrammarVariable get_grammar_variable()  const {
        return grammar_character_type.variable_or_token.variable;
   }

   TokenType get_token_type()  const {
        return grammar_character_type.variable_or_token.token;
    }
};

class GrammarWord {
private:
   Vector<GrammarCharacter> characters; //better: sorted list - vector is a sorted list
};

class GrammarProduction {
	GrammarVariable start;
	Vector<GrammarWord> words;
};


class Grammar {
private:
    GrammarVariable start = GrammarVariable::PROG;
    Vector<GrammarProduction> productions;

public:
    void prog() {
    }
};



#endif // GRAMMAR_H
