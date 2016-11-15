if(NOT TARGET Cinder-LibIgl)
  get_filename_component( CINDER-LIBIGL_PATH "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
	get_filename_component( CINDER_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../.." ABSOLUTE )
  list( APPEND CINDER-LIBIGL_SOURCES
    ${CINDER-LIBIGL_PATH}/src/CinderLibIgl.cpp
    # ${CINDER-LIBIGL_PATH}/lib/libigl/include/igl/viewer/ViewerData.h
    )
  add_library(Cinder-LibIgl ${CINDER-LIBIGL_SOURCES})
  target_include_directories( Cinder-LibIgl PUBLIC
    "${CINDER-LIBIGL_PATH}/include"
    "${CINDER-LIBIGL_PATH}/lib/libigl/include")
	target_include_directories( Cinder-LibIgl SYSTEM BEFORE PUBLIC "${CINDER_PATH}/include" )
	if( NOT TARGET cinder )
		include( "${CINDER_PATH}/proj/cmake/configure.cmake" )
		find_package( cinder REQUIRED PATHS
		  "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
		  "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
	endif()
  target_link_libraries(Cinder-LibIgl PRIVATE cinder)
endif()
