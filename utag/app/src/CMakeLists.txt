function(custom_add_library_from_dir TARGET)
    SUBDIRLIST(${CMAKE_CURRENT_SOURCE_DIR} SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

    FOREACH(subdir ${SUBDIRS})
        aux_source_directory(${subdir} SOURCE_LIB)
    ENDFOREACH()

    MESSAGE("${SOURCE_LIB};")
    add_library(lib STATIC ${SOURCE_LIB})
endfunction()

custom_add_library_from_dir("lib")
