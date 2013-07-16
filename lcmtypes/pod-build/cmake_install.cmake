# Install script for directory: /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/build")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/pod-build/lib/liblcmtypes_lcmtypes.a")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblcmtypes_lcmtypes.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblcmtypes_lcmtypes.a")
    EXECUTE_PROCESS(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblcmtypes_lcmtypes.a")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lcmtypes" TYPE FILE FILES
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/c/lcmtypes/lcmtypes_edge_t.h"
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/c/lcmtypes/lcmtypes_environment_t.h"
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/c/lcmtypes/lcmtypes_graph_t.h"
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/c/lcmtypes/lcmtypes_region_3d_t.h"
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/c/lcmtypes/lcmtypes_state_t.h"
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/c/lcmtypes/lcmtypes_trajectory_t.h"
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/c/lcmtypes/lcmtypes_vertex_t.h"
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/c/lcmtypes/lcmtypes.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/pod-build/lib/pkgconfig/lcmtypes_lcmtypes.pc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/java" TYPE FILE FILES "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/pod-build/lcmtypes_lcmtypes.jar")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/site-packages" TYPE DIRECTORY FILES "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/python/")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/lcmtypes" TYPE FILE FILES
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/lcmtypes_edge_t.lcm"
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/lcmtypes_environment_t.lcm"
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/lcmtypes_graph_t.lcm"
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/lcmtypes_region_3d_t.lcm"
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/lcmtypes_state_t.lcm"
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/lcmtypes_trajectory_t.lcm"
    "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/lcmtypes/lcmtypes_vertex_t.lcm"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/pod-build/lib/pkgconfig/lcmtypes.pc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/pod-build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/Users/thejenix/Dropbox/School/Agency/dev/rrtstar/lcmtypes/pod-build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
