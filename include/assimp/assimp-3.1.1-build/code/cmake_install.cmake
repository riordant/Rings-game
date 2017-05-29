# Install script for directory: /Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1-build/code/libassimp.3.1.1.dylib"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1-build/code/libassimp.3.dylib"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1-build/code/libassimp.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.3.1.1.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.3.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "/usr/local//libassimp.3.dylib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/anim.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/ai_assert.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/camera.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/color4.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/color4.inl"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/config.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/defs.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/cfileio.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/light.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/material.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/material.inl"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/matrix3x3.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/matrix3x3.inl"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/matrix4x4.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/matrix4x4.inl"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/mesh.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/postprocess.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/quaternion.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/quaternion.inl"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/scene.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/metadata.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/texture.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/types.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/vector2.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/vector2.inl"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/vector3.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/vector3.inl"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/version.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/cimport.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/importerdesc.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/Importer.hpp"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/DefaultLogger.hpp"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/ProgressHandler.hpp"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/IOStream.hpp"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/IOSystem.hpp"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/Logger.hpp"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/LogStream.hpp"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/NullLogger.hpp"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/cexport.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/Exporter.hpp"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/Compiler/pushpack1.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/Compiler/poppack1.h"
    "/Users/tadhgriordan/Desktop/Assimp/assimp-3.1.1/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

