#ifndef PARSER_H
#define PARSER_H

#include "grammar.h"
#include "vector.h"
#include "token.h"
#include "exception.h"
#include "parse_tree.h"
#include "node.h"

class Parser {
private:
	Vector<Vector<Vector<GrammarCharacter>>> parse_table;
	Vector<GrammarCharacter> production_stack;
	ParseTree tree;
	Node& last_parent = tree.get_root();
    Node& current = last_parent;

    void initializeParseTable();
    void initializeParser();

public:
    Parser() {
        production_stack.emplace_back(last_parent.get_character());
        initializeParseTable();
    }
	void parse(const Token& token);
    Vector<Vector<Vector<GrammarCharacter>>> getParseTable(){return parse_table;}
};
#endif // PARSER_H
