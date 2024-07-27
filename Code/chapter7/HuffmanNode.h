//
// Created by Wenjie Dong on 2023-11-28.
//

#ifndef INC_3__DATASTRUCTURES_HUFFMANNODE_H
#define INC_3__DATASTRUCTURES_HUFFMANNODE_H

struct HuffmanNode {
	char data;
	double weight;
	int parent, lchild, rchild;
	bool operator<(const HuffmanNode& t) const {
		return weight > t.weight;
	}
};

#endif //INC_3__DATASTRUCTURES_HUFFMANNODE_H
