cmake_minimum_required(VERSION 3.16)

project(uchat-qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appuchat-qt
    main.cpp
)

qt_add_qml_module(appuchat-qt
    URI uchat-qt
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES LoginPage.qml
        QML_FILES ContactPage.qml
        QML_FILES ChatPage.qml
        QML_FILES ChatMessageDelegate.qml
        SOURCES
        SOURCES
        QML_FILES
        SOURCES coreapi.h coreapi.cpp
        QML_FILES ConnectPage.qml
        SOURCES
        SOURCES clientmodel.h clientmodel.cpp
        QML_FILES NotificationPopup.qml
        SOURCES contactItem.h
        SOURCES friendListModel.h
        SOURCES groupListModel.h
        SOURCES chatmodel.h chatmodel.cpp

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appuchat-qt PROPERTIES
   MACOSX_BUNDLE_GUI_IDENTIFIER com.dingvero.appuchatqt
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appuchat-qt
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appuchat-qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

