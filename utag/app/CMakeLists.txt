set(SOURCE_EXE main.cpp)

add_compile_options(
   -Wall
   -Wextra
   -Werror
   -Wpedantic
)

# MACRO to add all directories in result
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "${curdir}/")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${curdir}/${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR}/../taglib/taglib)

FOREACH(subdir ${SUBDIRS})
  include_directories(${subdir})
ENDFOREACH()

include_directories(src)
add_subdirectory(src)

add_executable(${PROJECT_NAME} ${SOURCE_EXE})
target_link_libraries(${PROJECT_NAME} lib tag)
