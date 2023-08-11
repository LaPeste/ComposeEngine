set(LIB_NAME Components)

add_library(${LIB_NAME} OBJECT
    Acceleration.cpp
    Appearance.cpp
    Collider.cpp
    Component.tpp
    ComponentBase.cpp
    Controller.cpp
    EntityFlag.cpp
    Transform.cpp
    Velocity.cpp    
)