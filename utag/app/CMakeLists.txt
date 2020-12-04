set(SOURCE_EXE main.cpp)

add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wpedantic
    -DTAGLIB_STATIC
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

message("## Looking for Qt...")
find_package(Qt5 REQUIRED Core Qml Widgets Gui)
if (${Qt5_FOUND})
    message("## Found Qt " ${Qt5_VERSION})
else()
    message("## Couldn't find Qt")
endif()

# MACRO to add all directories in result
MACRO(SUBDIRLIST result firstdir curdir)
    file(GLOB ENDF6_SRC_TOP RELATIVE
        ${curdir} ${curdir}/*)
    file(GLOB_RECURSE ENDF6_SRC_NESTED ${curdir}/*)
    set(children ${ENDF6_SRC_TOP} ${ENDF6_SRC_NESTED})

    SET(dirlist "${firstdir}")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${curdir}/${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()


function(include_all_files)
    SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR}/../3dparty/taglib/taglib/ ${CMAKE_CURRENT_SOURCE_DIR}/../3dparty/taglib/taglib)

    FOREACH(subdir ${SUBDIRS})
        include_directories(${subdir})
    ENDFOREACH()
    include_directories(src)
endfunction()

include_all_files()
add_subdirectory(src)

qt5_add_resources(RESOURCES resources/myres.qrc)

#Set app icon
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX_BUNDLE_ICON_FILE utag_icon.icns)
    set(APP_ICON_MACOSX ${CMAKE_CURRENT_SOURCE_DIR}/../resources/utag_icon.icns)
    set_source_files_properties(${APP_ICON_MACOSX} PROPERTIES
               MACOSX_PACKAGE_LOCATION "Resources")
    add_executable(${CMAKE_PROJECT_NAME} MACOSX_BUNDLE ${APP_ICON_MACOSX} main.cpp ${RESOURCES})
else()
    set(APP_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/../resources/app_win32.rc")

    add_executable(${CMAKE_PROJECT_NAME} main.cpp ${APP_ICON_RESOURCE})
endif()
target_link_libraries(${PROJECT_NAME} tag src_lib Qt5::Core Qt5::Qml Qt5::Widgets Qt5::Gui)

