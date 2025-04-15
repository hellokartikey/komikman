add_library(komikman_static)

target_link_libraries(komikman_static
PUBLIC
  Qt6::Core
  Qt6::Gui
  Qt6::Quick
  Qt6::Widgets
  Qt6::QuickControls2
  libassert::assert
)

target_sources(komikman_static
PRIVATE
  backend.cpp
  backend.hpp
)

ecm_add_qml_module(komikman_static URI Komikman)

ecm_target_qml_sources(komikman_static
SOURCES
  qml/Main.qml
)

add_executable(komikman main.cpp)
target_link_libraries(komikman PRIVATE komikman_static)
