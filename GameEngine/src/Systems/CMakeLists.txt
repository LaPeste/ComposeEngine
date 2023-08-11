set(LIB_NAME Systems)

add_library(${LIB_NAME} OBJECT
    Animator.cpp
    BTEngine.cpp
    CollisionDetector.cpp
    InputSystem.cpp
    Movement.cpp
    Renderer.cpp
    System.tpp
    SystemBase.cpp
    SystemManager.cpp    
)