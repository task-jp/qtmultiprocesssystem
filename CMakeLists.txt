cmake_minimum_required(VERSION 3.16)

include(.cmake.conf)
project(QtMultiProcessSystem
    VERSION "${QT_REPO_MODULE_VERSION}"
    DESCRIPTION "Qt Multi Process System"
    HOMEPAGE_URL "https://github.com/task-jp/qtmultiprocesssystem"
    LANGUAGES CXX
)

find_package(Qt6 ${PROJECT_VERSION} CONFIG REQUIRED COMPONENTS BuildInternals Core Quick)
find_package(Qt6 ${PROJECT_VERSION} CONFIG OPTIONAL_COMPONENTS DBus WaylandCompositor Location Multimedia)

qt_build_repo()

