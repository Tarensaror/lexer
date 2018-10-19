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
	
	void typeCheck() {
/*
		new vector visited nodes.
		
		get root
		
		
		loop start
		iterate down.
		look for children to go as far down as possible.
		if bottom reached
		go 1 layer up 
		
		
		
		compare actual type to children types and operator
		return syntax error if type mismatch, with reference to node and expected an actual types and layer.
		store node to visited
		
		else go up 1 layer and iterate next unvisited node 
		loop end
		
		whole tree is checked. return true
		
*/		
	}
	
	void makeCode() {
		//to be implemented
	}
	
};


#endif // PARSE_TREE_H_INCLUDED
