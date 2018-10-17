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
	bool is_valid = true;
	Node& last_parent = tree.get_root();
    Node& current = this->last_parent;

    void initializeParseTable();
    void initializeParser();

public:
    Parser() {
        production_stack.emplace_back(this->last_parent.get_character());
        initializeParseTable();
    }
	bool parse(const Token& token);
    Vector<Vector<Vector<GrammarCharacter>>> get_parse_table(){return this->parse_table;}
    bool finalize();
    ParseTree get_parse_tree() {
        return this->tree;
    }
};
#endif // PARSER_H
