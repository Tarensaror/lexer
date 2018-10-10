#ifndef PARSER_H
#define PARSER_H

#include "grammar.h"
#include "vector.h"
#include "token.h"
#include "exception.h"

class Parser {
private:
	Vector<Vector<Vector<GrammarCharacter>>> parse_table;

public:
    void parse(Vector<Token> tokens);
    void initializeParseTable();
    Vector<Vector<Vector<GrammarCharacter>>> getParseTable();

};
#endif // PARSER_H
