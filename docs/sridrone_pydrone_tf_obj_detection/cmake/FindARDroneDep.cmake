# A package finder for ARDroneDep
# 
set( name ARDroneDep )
set( ${name}_FOUND False )

if ( ${CMAKE_SYSTEM_NAME} STREQUAL Linux )
  set ( ${name}_LIBRARIES "" ) 
  set ( ${name}_INCLUDE_DIR "/usr/local/include/ARDroneLib" ) 
  foreach( incdir Common ardrone_tool ATcodec VP_Api VP_Os VP_SDK VP_SDK/VP_Os/linux VLIB ) 
    list( APPEND ${name}_INCLUDE_DIR /usr/local/include/ARDroneLib/${incdir} )
  endforeach()
  foreach( lib pc_ardrone vlib sdk pc_ardrone_notool avcodec avdevice avfilter avformat avutil swscale )
    find_library( ${lib}_LIBRARY
      NAMES ${lib} 
      PATHS /usr/lib /usr/local/lib )

    if ( ${lib}_LIBRARY )
      mark_as_advanced( ${lib}_LIBRARY )
      set( ${name}_FOUND True )
    endif()
    list( APPEND ${name}_LIBRARIES  ${${lib}_LIBRARY} )
  endforeach()
endif()

if ( ${name}_FOUND )
  message( STATUS "Found ${name}: (${${name}_INCLUDE_DIR}, ${${name}_LIBRARIES})" )
else()
  message( STATUS "Unable to find ${name}: (${${name}_INCLUDE_DIR}, ${${name}_LIBRARIES})" )
endif()
