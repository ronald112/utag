set(SOURCE_EXE main.cpp)

add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

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
target_link_libraries(${PROJECT_NAME} lib tag)
