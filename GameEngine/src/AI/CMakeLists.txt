add_subdirectory(BasicNodes/)

set(LIB_NAME BehaviourTree)
add_library(${LIB_NAME} OBJECT BehaviourTree.cpp $<TARGET_OBJECTS:TreeNodes>)