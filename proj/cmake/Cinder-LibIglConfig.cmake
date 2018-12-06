if(NOT TARGET Cinder-LibIgl)
  option(LIBIGL_WITH_TETGEN           "Use Tetgen"         OFF)
  get_filename_component( CINDER-LIBIGL_PATH "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
	# get_filename_component( CINDER_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../../Cinder" ABSOLUTE )
  message("CINDER PATH= ${CINDER_PATH}")
  set(LIBIGL_ROOT "${CINDER-LIBIGL_PATH}/lib/libigl")
  set(LIBIGL_SOURCE_DIR "${LIBIGL_ROOT}/include")
  set(LIBIGL_EXTERNAL "${LIBIGL_ROOT}/external")
  set(LIBIGL_INCLUDE_DIRS "")
  set(LIBIGL_LIBRARIES "")
  set(LIBIGL_EXTRA_LIBRARIES "")
  set(LIBIGL_DEFINITIONS "")

  list(APPEND LIBIGL_INCLUDE_DIRS "${LIBIGL_SOURCE_DIR}")

  list( APPEND CINDER-LIBIGL_SOURCES
    ${CINDER-LIBIGL_PATH}/src/CinderLibIgl.cpp
    ${CINDER-LIBIGL_PATH}/include/CinderLibIgl.h
    )
if(LIBIGL_WITH_TETGEN)
  set(TETGEN_DIR "${LIBIGL_EXTERNAL}/tetgen")
  # add_subdirectory("${TETGEN_DIR}" "tetgen")
  add_library(tetgen ${TETGEN_DIR}/tetgen.cxx ${TETGEN_DIR}/predicates.cxx)
  target_compile_definitions(tetgen PRIVATE -DTETLIBRARY)
  list(APPEND LIBIGL_INCLUDE_DIRS ${TETGEN_DIR})
  list(APPEND LIBIGL_TETGEN_EXTRA_LIBRARIES "tetgen")
  list(APPEND LIBIGL_EXTRA_LIBRARIES ${LIBIGL_TETGEN_EXTRA_LIBRARIES})
endif()
  add_library(Cinder-LibIgl ${CINDER-LIBIGL_SOURCES})
  target_include_directories( Cinder-LibIgl PUBLIC
    "${CINDER-LIBIGL_PATH}/include"
    "${CINDER-LIBIGL_PATH}/lib/libigl/external/embree/include"
    "${LIBIGL_INCLUDE_DIRS}")
	# target_include_directories( Cinder-LibIgl SYSTEM BEFORE PUBLIC "${CINDER_PATH}/include" )
	if( NOT TARGET cinder )
		include( "${CINDER_PATH}/proj/cmake/configure.cmake" )
		find_package( cinder REQUIRED PATHS
		  "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
		  "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
	endif()
  target_link_libraries(Cinder-LibIgl PRIVATE cinder)
  target_link_libraries(Cinder-LibIgl PUBLIC ${LIBIGL_EXTRA_LIBRARIES})
  # include_directories(${CINDER-LIBIGL_PATH}/lib/libigl/include)
endif()
