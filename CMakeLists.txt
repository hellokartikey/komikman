cmake_minimum_required(VERSION 3.30)

project(komikman VERSION 0.1.0)

set(QT_MIN_VERSION "6.8")
set(KF_MIN_VERSION "6.0")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

find_package(Qt6 ${QT_MIN_VERSION}
REQUIRED
COMPONENTS
  Core
  Gui
  Widgets
  Qml
  Quick
  QuickControls2
)

find_package(KF6 ${KF_MIN_VERSION}
REQUIRED
COMPONENTS
  Kirigami
  CoreAddons
  I18n
  Archive
  ColorScheme
)

find_package(libassert REQUIRED)
find_package(nlohmann_json REQUIRED)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(KDEClangFormat)
include(KDEGitCommitHooks)
include(ECMQmlModule)
include(ECMSetupVersion)

file(GLOB_RECURSE ALL_CXX_SOURCE_FILES src/*.cpp src/*.hpp)
kde_clang_format(${ALL_CXX_SOURCE_FILES})
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)

qt_policy(SET QTP0001 NEW)
qt_standard_project_setup()

add_subdirectory(data)
add_subdirectory(src)
