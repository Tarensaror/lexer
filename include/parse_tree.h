#ifndef PARSE_TREE_H_INCLUDED
#define PARSE_TREE_H_INCLUDED

#include "node.h"
#include "leaf.h"

public class ParseTree {
private:
    Leaf root;

    void add_leaf(const Leaf& child, const Node& parent) {
        Leaf child = Leaf(child, parent);
        if (root == nullptr) {
            this->root = child;
        }
    }

public:
    ParseTree(Leaf root) {
        this->root = root;
    }

    void add_character(const GrammarCharacter& character, const Node& parent) {
        Leaf node;
        if (character.is_grammar_variable()) {
            node = Node(character, parent);
        } else if (character.is_token_type()) {
            node = Leaf(character, parent);
        } else {
            //throw ParserException(); TODO
        }
        add_leaf(node);
    }
}


#endif // PARSE_TREE_H_INCLUDED
