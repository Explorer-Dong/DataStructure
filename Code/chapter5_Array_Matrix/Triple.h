#ifndef TRIPLE_H
#define TRIPLE_H

template<class T>
struct Triple {
    int r, c;
    T value;
    
    Triple(int r, int c, T value) : r(r), c(c), value(value) {}
};

#endif //TRIPLE_H