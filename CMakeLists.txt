cmake_minimum_required(VERSION 3.26)
project(DataStructure)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        Code/chapter2/h
)

add_executable(3__DataStructures
        Code/chapter2/SeqList.h
        Code/chapter2/Node.h
        Code/chapter2/LinkList.h
        Code/chapter2/CircleList.h
        Code/chapter2/Homework_2.cpp
        Code/chapter2/Experiment_2.cpp

        Code/chapter3/SeqStack.h
        Code/chapter3/LinkStack.h
        Code/chapter3/SeqDoubleStack.h
        Code/chapter3/SeqQueueFlag.h
        Code/chapter3/LinkQueue.h
        Code/chapter3/Homework_3.cpp
        Code/chapter3/Trail_3.cpp

        Code/chapter3/SeqQueueNum.h
        Code/chapter3/Dstack2Queue.h

        Code/chapter4/Homework_4.cpp
        Code/chapter4/Trail_4.cpp

        Code/chapter5/Triple.h
        Code/chapter5/SparseMatrix.h
        Code/chapter5/Homework_5.cpp
        Code/chapter5/Trail_5.cpp

        Code/chapter6/GListNode.h
        Code/chapter6/GList.h
        Code/chapter6/Homework_6.cpp
        Code/chapter6/Trail_6.cpp

        Code/chapter7/BTree.h
        Code/chapter7/CSTree.h
        Code/chapter7/HuffmanNode.h
        Code/chapter7/HuffmanTree.h
        Code/chapter7/HuffmanTree.cpp
        Code/chapter7/Homework_7.cpp
        Code/chapter7/Trail_7.cpp

        Code/chapter8/MGraph.h
        Code/chapter8/ALGraph.h
        Code/chapter8/Homework_8.cpp
        Code/chapter8/Trail_8.cpp

        Code/chapter9/Trail_9.cpp

        Code/chapter10/Trail_10.cpp
        Code/chapter10/Homework_10.cpp

        Code/main.cpp
)