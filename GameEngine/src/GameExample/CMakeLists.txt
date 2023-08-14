set(LIB_NAME GameExample)

# I could not get an object library to hold only object files
# From the docs of CMake it is not mentioned that object libraries can
# hold object files.
add_library(${LIB_NAME} OBJECT
    AI/AttackWhenInRange.cpp
    AI/Patrolling.cpp
    Behaviours/Components/FieldOfView.cpp
    Behaviours/Systems/FOVspotter.cpp
    GameObjects/Door.cpp
    GameObjects/Luigi.cpp
)