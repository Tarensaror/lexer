#ifndef LEAF_H
#define LEAF_H

#include "node.h"
#include "symboltable.h"

class Leaf {
private:

    Node parent;
    GrammarCharacter character;

public:
    Leaf(const GrammarCharacter& character, Node parent) : Node(parent) {
        this->parent = parent;
        this->character = character;
    }

    GrammarCharacter get_character() const {
        return this->character;
    }

    Node get_parent() const {
        return this->parent;
    }

}
