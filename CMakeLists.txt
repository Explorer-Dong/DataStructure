cmake_minimum_required(VERSION 3.26)
project(DataStructure)

set(CMAKE_CXX_STANDARD 17)

add_executable(DataStructure
        Code/chapter2/SeqList.h
        Code/chapter2/Node.h
        Code/chapter2/LinkList.h
        Code/chapter2/CircleList.h
        Code/chapter2/Homework_2.cpp
        Code/chapter2/Experiment_2.cpp

        Code/chapter3/SeqStack.h
        Code/chapter3/LinkStack.h
        Code/chapter3/SeqDoubleStack.h
        Code/chapter3/CircleSeqQueueWithFlag.h
        Code/chapter3/Homework_3.cpp
        Code/chapter3/Experiment_3.cpp
        Code/chapter3/CircleSeqQueueWithNum.h
        Code/chapter3/DoubleStack4Queue.h

        Code/chapter4/Homework_4.cpp
        Code/chapter4/Experiment_4.cpp

        Code/chapter5/Triple.h
        Code/chapter5/SparseMatrix.h
        Code/chapter5/Homework_5.cpp
        Code/chapter5/Experiment_5.cpp

        Code/chapter6/GList.h
        Code/chapter6/Homework_6.cpp
        Code/chapter6/Experiment_6.cpp

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