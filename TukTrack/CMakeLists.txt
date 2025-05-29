cmake_minimum_required(VERSION 3.16)

project(TukTrack VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appTukTrack
    main.cpp
    uicontroller.h uicontroller.cpp
    MANUAL_FINALIZATION
)

set_property(TARGET appTukTrack APPEND PROPERTY
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
)

set_source_files_properties(Style.qml
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(appTukTrack
    URI TukTrack
    VERSION 1.0
    QML_FILES
        Main.qml
        Style.qml

        Screens/Home.qml
        Screens/TukTuk.qml
        Screens/Drivers.qml
        Screens/DriverDetail.qml
        Screens/Deposits.qml
        Screens/More.qml
        Screens/TukTukDetail.qml
        Screens/DailyDeposits.qml
        Screens/MaintenanceRecord.qml
        Screens/About.qml

        Components/DateChooser.qml
        Components/TextIconBtn.qml
        Components/DatePickerPopup.qml
        #RESOURCES android/AndroidManifest.xml android/build.gradle android/res/values/libs.xml android/res/xml/qtprovider_paths.xml android/gradle/wrapper/gradle-wrapper.jar android/gradle/wrapper/gradle-wrapper.properties android/gradle.properties android/gradlew android/gradlew.bat
)

qt_add_resources(appTukTrack "images"
    PREFIX "/images"
    FILES
        images/tuk.png
        images/driver.png
        images/tuc-tuc.png
        images/expenses.png
        images/money.png
        images/deposit.png
        images/info-button.png
        images/data-visualization.png
)

qt_add_resources(appTukTrack "fonts"
    PREFIX "/"
    FILES
        fonts/Roboto-Regular.ttf
        fonts/webfont.ttf
)
qt_finalize_executable(appTukTrack)
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
target_link_libraries(appTukTrack PRIVATE Qt6::Widgets)
target_link_libraries(appTukTrack PRIVATE tuktrack_core)
target_link_libraries(appTukTrack PRIVATE Qt6::Sql)

include(GNUInstallDirs)
install(TARGETS appTukTrack
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
