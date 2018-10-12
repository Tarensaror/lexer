#ifndef NODE_H
#define NODE_H

#include "leaf.h"

class Node  public Leaf {
private:
    Vector<Node> children;
    // Leaf leaf1, leaf2, leaf3;

public:
    Node(const GrammarCharacter& character, Node parent) : Leaf(character, parent);

    void add_child(Node child) {
        this->children.push_back(child);
    }
}
