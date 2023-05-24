# Install script for directory: /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027

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
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/def.tab.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/lex.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiAlias.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiAssertion.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiBlockage.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiComponent.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiDebug.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiDefs.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiFill.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiFPC.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiGroup.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiIOTiming.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiKRDefs.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiMisc.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiNet.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiNonDefault.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiPartition.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiPath.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiPinCap.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiPinProp.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiProp.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiPropType.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiRegion.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiRowTrack.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiScanchain.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiSite.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiSlot.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiTimingDisable.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiUser.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiUtil.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defiVia.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defrCallBacks.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defrData.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defrReader.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defrSettings.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defwWriterCalls.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/def/defwWriter.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/defzlib/defzlib.hpp"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiAlias.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiAssertion.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiBlockage.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiComponent.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiDebug.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiDefs.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiFill.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiFPC.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiGroup.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiIOTiming.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiKRDefs.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiMisc.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiNet.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiNonDefault.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiPartition.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiPath.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiPinCap.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiPinProp.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiProp.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiPropType.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiRegion.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiRowTrack.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiScanchain.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiSite.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiSlot.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiTimingDisable.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiTypedefs.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiUser.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defiVia.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defMsgTable.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defrReader.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defwWriterCalls.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdef/defwWriter.h"
    "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/cdefzlib/defzlib.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/lib/libdef.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/lib/libdefzlib.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/lib/libcdef.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/def/5.8-p027/lib/libcdefzlib.a")
endif()

