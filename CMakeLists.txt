cmake_minimum_required(VERSION 3.16)

project(QtAndroidApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_add_executable(appQtAndroidApp
    main.cpp
)

qt_add_qml_module(appQtAndroidApp
    URI QtAndroidApp
    VERSION 1.0
    QML_FILES Main.qml
)

target_link_libraries(appQtAndroidApp
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appQtAndroidApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
