cmake_minimum_required(VERSION 3.26)
project(DataStructure)

set(CMAKE_CXX_STANDARD 17)

add_executable(DataStructure
        Code/chapter2_List/SeqList.h
        Code/chapter2_List/Node.h
        Code/chapter2_List/LinkList.h
        Code/chapter2_List/CircleList.h
        Code/chapter2_List/Homework_2.cpp
        Code/chapter2_List/Experiment_2.cpp

        Code/chapter3_Stack_Queue/SeqStack.h
        Code/chapter3_Stack_Queue/LinkStack.h
        Code/chapter3_Stack_Queue/SeqDoubleStack.h
        Code/chapter3_Stack_Queue/DoubleStack4Queue.h
        Code/chapter3_Stack_Queue/CircleSeqQueueWithFlag.h
        Code/chapter3_Stack_Queue/CircleSeqQueueWithNum.h
        Code/chapter3_Stack_Queue/Homework_3.cpp
        Code/chapter3_Stack_Queue/Experiment_3.cpp

        Code/chapter4_String/Homework_4.cpp
        Code/chapter4_String/Experiment_4.cpp

        Code/chapter5_Array_Matrix/Triple.h
        Code/chapter5_Array_Matrix/SparseMatrix.h
        Code/chapter5_Array_Matrix/Homework_5.cpp
        Code/chapter5_Array_Matrix/Experiment_5.cpp

        Code/chapter6_GeneralizedList/GList.h
        Code/chapter6_GeneralizedList/Homework_6.cpp
        Code/chapter6_GeneralizedList/Experiment_6.cpp

        Code/chapter7_Tree/BinaryTree.h
        Code/chapter7_Tree/ChildSiblingTree.h
        Code/chapter7_Tree/HuffmanNode.h
        Code/chapter7_Tree/HuffmanTree.h
        Code/chapter7_Tree/HuffmanTree.cpp
        Code/chapter7_Tree/Homework_7.cpp
        Code/chapter7_Tree/Experiment_7.cpp

        Code/chapter8_Graph/MGraph.h
        Code/chapter8_Graph/ALGraph.h
        Code/chapter8_Graph/Homework_8.cpp
        Code/chapter8_Graph/Experiment_8.cpp

        Code/chapter9_Search/Experiment_9.cpp

        Code/chapter10_Sort/Homework_10.cpp
        Code/chapter10_Sort/Experiment_10.cpp

        Code/main.cpp
)