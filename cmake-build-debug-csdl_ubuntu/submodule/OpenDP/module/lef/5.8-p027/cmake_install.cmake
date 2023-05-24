# Install script for directory: /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027

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
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lef.tab.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lex.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/crypt.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiArray.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiCrossTalk.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiDebug.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiDefs.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiEncryptInt.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiKRDefs.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiLayer.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiMacro.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiMisc.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiNonDefault.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiProp.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiPropType.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiUnits.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiUser.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiUtil.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiVia.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefiViaRule.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefrCallBacks.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefrData.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefrReader.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefrSettings.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefwWriterCalls.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lef/lefwWriter.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lefzlib/lefzlib.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiArray.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiCrossTalk.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiDebug.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiEncryptInt.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiLayer.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiMacro.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiMisc.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiNonDefault.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiProp.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiPropType.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiTypedefs.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiUnits.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiUser.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiUtil.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiVia.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefiViaRule.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefMsgTable.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefrReader.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefwWriterCalls.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clef/lefwWriter.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/clefzlib/lefzlib.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lib/liblef.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lib/liblefzlib.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lib/libclef.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lib/libclefzlib.a")
endif()
