//
// Created by Wenjie Dong on 2023-10-23.
//

#include <iostream>

#ifndef INC_3__DATASTRUCTURES_TRIPLE_H
#define INC_3__DATASTRUCTURES_TRIPLE_H

template<class T>
struct Triple {
	int r, c;
	T elem;
	Triple(int _r, int _c, T _elem) : r(_r), c(_c), elem(_elem) {}
};

#endif //INC_3__DATASTRUCTURES_TRIPLE_H
