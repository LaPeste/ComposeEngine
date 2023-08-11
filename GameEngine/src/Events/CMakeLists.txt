set(LIB_NAME Events)
add_library(${LIB_NAME} OBJECT
  AddedComponentEvent.cpp
  Event.tpp
  EventBase.cpp
  EventListener.cpp
  EventManager.cpp
  InputEvent.cpp
)