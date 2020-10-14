
function(custom_add_library_from_dir TARGET)
    SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

    #set(HEADERS AudioFile/AudioFile.h TagEditor/TagEditor.h MiscHeaders.h MyHeaders.h)
    #file(GLOB_RECURSE src_header ${SUBDIRS}/*.h)
    #set(HEADERS)
    set(HEADERS "")
    FOREACH(subdir ${SUBDIRS})
        aux_source_directory(${subdir} SOURCE_LIB)
        file(GLOB kek2 ${subdir}/*.h)
        LIST(APPEND HEADERS ${kek2})
    ENDFOREACH()

    add_library(${TARGET} ${SOURCE_LIB} ${HEADERS})
endfunction()


message("::${HEADERS}::\n")


custom_add_library_from_dir("src_lib")
target_link_libraries(src_lib tag Qt5::Core Qt5::Qml Qt5::Widgets)
