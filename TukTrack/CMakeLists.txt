cmake_minimum_required(VERSION 3.16)

project(TukTrack VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appTukTrack
    main.cpp
)

qt_add_qml_module(appTukTrack
    URI TukTrack
    VERSION 1.0
    QML_FILES
        Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appTukTrack PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTukTrack
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTukTrack
    PRIVATE Qt6::Quick
)

target_link_libraries(appTukTrack PRIVATE tuktrack_core)

include(GNUInstallDirs)
install(TARGETS appTukTrack
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
