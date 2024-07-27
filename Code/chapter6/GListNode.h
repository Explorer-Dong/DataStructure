//
// Created by Wenjie Dong on 2023-10-23.
//

#include <iostream>

#ifndef INC_3__DATASTRUCTURES_GLISTNODE_H
#define INC_3__DATASTRUCTURES_GLISTNODE_H

enum GListNodeType {ATOM, LIST};

template<class T>
struct GListNode {
	GListNodeType type;
	union {
		T data;
		GListNode* sublist;
	};
	GListNode<T>* next;
};

#endif //INC_3__DATASTRUCTURES_GLISTNODE_H
