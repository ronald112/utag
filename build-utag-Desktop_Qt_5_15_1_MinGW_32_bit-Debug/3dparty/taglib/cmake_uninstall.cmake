if (NOT EXISTS "D:/StudyWork/Progamming/uCode/C++/utag/build-utag-Desktop_Qt_5_15_1_MinGW_32_bit-Debug/3dparty/taglib/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"D:/StudyWork/Progamming/uCode/C++/utag/build-utag-Desktop_Qt_5_15_1_MinGW_32_bit-Debug/3dparty/taglib/install_manifest.txt\"")
endif()

file(READ "D:/StudyWork/Progamming/uCode/C++/utag/build-utag-Desktop_Qt_5_15_1_MinGW_32_bit-Debug/3dparty/taglib/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    execute_process(
      COMMAND C:/Program Files/CMake/bin/cmake.exe -E remove "$ENV{DESTDIR}${file}"
      OUTPUT_VARIABLE rm_out
      RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
      message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif ()
  else ()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif ()
endforeach()
