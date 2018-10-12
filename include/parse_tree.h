#ifndef PARSE_TREE_H_INCLUDED
#define PARSE_TREE_H_INCLUDED

#include "node.h"

class ParseTree {
private:
    Node root;

public:
    ParseTree() : root(GrammarCharacter(GrammarVariable::ROOT), nullptr) {}

    Node& get_root() {
        return this->root;
    }
};


#endif // PARSE_TREE_H_INCLUDED
