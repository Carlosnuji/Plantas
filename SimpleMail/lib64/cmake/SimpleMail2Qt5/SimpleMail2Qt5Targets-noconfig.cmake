#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SimpleMail::Core" for configuration ""
set_property(TARGET SimpleMail::Core APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(SimpleMail::Core PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib64/libSimpleMail2Qt5.so.2.0.0"
  IMPORTED_SONAME_NOCONFIG "libSimpleMail2Qt5.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS SimpleMail::Core )
list(APPEND _IMPORT_CHECK_FILES_FOR_SimpleMail::Core "${_IMPORT_PREFIX}/lib64/libSimpleMail2Qt5.so.2.0.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
