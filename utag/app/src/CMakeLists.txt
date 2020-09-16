function(custom_add_library_from_dir TARGET)
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCE_LIB)
    add_library(lib STATIC ${SOURCE_LIB})
endfunction()

custom_add_library_from_dir("lib")
