add_subdirectory(AI/)
add_subdirectory(Behaviours/)
add_subdirectory(GameObjects/)

set(LIB_NAME GameExample)
add_library(${LIB_NAME} OBJECT
    $<TARGET_OBJECTS:GameExample_AI>
    $<TARGET_OBJECTS:GameExample_Behaviours>
    $<TARGET_OBJECTS:GameExample_GameObjects>
)