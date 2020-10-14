set(SOURCE_EXE main.cpp)

add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wpedantic
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

add_executable(${PROJECT_NAME} ${SOURCE_EXE})
target_link_libraries(${PROJECT_NAME} tag src_lib Qt5::Core Qt5::Qml Qt5::Widgets Qt5::Gui)

