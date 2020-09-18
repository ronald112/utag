function(custom_add_library_from_dir TARGET)
    SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

    FOREACH(subdir ${SUBDIRS})
        aux_source_directory(${subdir} SOURCE_LIB)
    ENDFOREACH()

    add_library(${TARGET} STATIC ${SOURCE_LIB})
endfunction()

custom_add_library_from_dir("src_lib")
target_link_libraries(src_lib Qt5::Core Qt5::Qml Qt5::Widgets)
