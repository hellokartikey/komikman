ecm_setup_version(
  ${PROJECT_VERSION}
  VARIABLE_PREFIX KOMIKMAN
  VERSION_HEADER version.hpp
)

add_executable(komikman main.cpp)

target_link_libraries(komikman
PRIVATE
  Qt6::Core
  Qt6::Gui
  Qt6::Quick
  Qt6::Widgets
  Qt6::QuickControls2
  KF6::Kirigami
  KF6::CoreAddons
  KF6::I18n
  libassert::assert
  nlohmann_json::nlohmann_json
)

target_sources(komikman
PRIVATE
  backend.hpp
  backend.cpp
  chapter.hpp
  chapter.cpp
  config.hpp
  config.cpp
  entry.hpp
  entry.cpp
  library.hpp
  library.cpp
)

ecm_add_qml_module(komikman URI Komikman)

ecm_target_qml_sources(komikman
SOURCES
  qml/Main.qml
  qml/EntryData.qml
  qml/EntryDelegate.qml
  qml/EntryPage.qml
  qml/CoverImage.qml
  qml/ChaptersPage.qml
  qml/ChapterView.qml
)

install(TARGETS komikman ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
