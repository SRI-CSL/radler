include(FindPackageHandleStandardArgs)

find_library(RIJNDAEL_LIBRARIES
  NAMES Rijndael 
  DOC "RIJNDAEL libraries"
)

# Try to find headers
find_path(RIJNDAEL_INCLUDES
  NAMES Rijndael_c.h 
  DOC "RIJNDAEL header"
)

find_package_handle_standard_args(RIJNDAEL
	REQUIRED_VARS RIJNDAEL_LIBRARIES RIJNDAEL_INCLUDES)

if (RIJNDAEL_FOUND)
  set(RIJNDAEL_INCLUDE_DIRS "${RIJNDAEL_INCLUDES}")
  list(REMOVE_DUPLICATES RIJNDAEL_INCLUDE_DIRS)

  if (NOT TARGET RIJNDAEL::RIJNDAEL)
    add_library(RIJNDAEL::RIJNDAEL UNKNOWN IMPORTED)
    set_target_properties(RIJNDAEL::RIJNDAEL PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${RIJNDAEL_INCLUDES}"
      IMPORTED_LOCATION "${RIJNDAEL_LIBRARIES}")
  endif()
endif()
