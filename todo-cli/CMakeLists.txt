cmake_minimum_required(VERSION 3.19)
project(todo-cli LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(todo-cli
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    task.h
    task.cpp
)

qt_add_translations(
    TARGETS todo-cli
    TS_FILES todo-cli_zh_CN.ts
)

target_link_libraries(todo-cli
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS todo-cli
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET todo-cli
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
