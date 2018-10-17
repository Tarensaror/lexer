#ifndef NODE_H
#define NODE_H

#include "vector.h"

class Node {
private:
    friend class ParseTree;
    friend class Vector<Node>;
    Node* parent;
    int level;
    GrammarCharacter character;
    Vector<Node> children;

    Node(const GrammarCharacter& character, Node* parent) : parent(parent), character(character) {
        this->level = (this->parent != nullptr) ? (*(this->parent)).get_level() + 1 : 0;
    }

public:
    /**
    * para parent: if parent ist nullptr, it will be handled as root
    */
    Node& add_child(const GrammarCharacter& character) {
        this->children.emplace_back(character, this);
        return *(this->children.end() - 1);
    }

    bool is_leaf() {
        return this->character.is_token_type();
    }

    GrammarCharacter get_character() const {
        return this->character;
    }

    Node get_parent() const {
        return *(this->parent);
    }

    Vector<Node> get_children() const {
        return (this->children);
    }

    int get_level() {
        return this->level;
    }
};
#endif /* NODE_H */

