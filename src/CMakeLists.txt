add_library(komikman_static)

target_link_libraries(komikman_static
PUBLIC
  Qt6::Core
  Qt6::Gui
  Qt6::Quick
  Qt6::Widgets
  Qt6::QuickControls2
  libassert::assert
  nlohmann_json::nlohmann_json
)

target_sources(komikman_static
PRIVATE
  backend.hpp
  backend.cpp
  library.hpp
  library.cpp
  entry.hpp
  entry.cpp
)

ecm_add_qml_module(komikman_static URI Komikman)

ecm_target_qml_sources(komikman_static
SOURCES
  qml/Main.qml
  qml/EntryData.qml
  qml/EntryDelegate.qml
  qml/EntryPage.qml
  qml/CoverImage.qml
)

add_executable(komikman main.cpp)
target_link_libraries(komikman PRIVATE komikman_static)
