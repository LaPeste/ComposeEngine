set(LIB_NAME BehaviourTree)
add_library(${LIB_NAME} OBJECT
    BehaviourTree.cpp
    BasicNodes/Repeater.cpp
    BasicNodes/Selector.cpp
    BasicNodes/Sequence.cpp
)