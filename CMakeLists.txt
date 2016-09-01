# Copyright 2015 University of Auckland
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.cmake_minimum_required (VERSION 3.1)

cmake_minimum_required(VERSION 3.2)

# Handle superbuild first
option (USE_SUPERBUILD "Whether or not a superbuild should be invoked" ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if (USE_SUPERBUILD)
  project (SUPERBUILD NONE)
  # execute the superbuild to build dependencies
  include (cmake/SuperBuild.cmake)
  return()                      # stop processing this file further
else()
  project(c2bb VERSION 1.0 LANGUAGES CXX)
endif()

option(BUILD_TESTING "Build c2bb tests" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(common)

# Use the following variables when configuring the build from the command line to
# set the corresponding cache variables.

# COVERAGE ==> C2BB_COVERAGE
set(_PARAM_ANNOTATION "Enable coverage testing.")
if(CMAKE_COMPILER_IS_GNUCXX)
  set( C2BB_COVERAGE OFF CACHE BOOL ${_PARAM_ANNOTATION} )
endif()
if( COVERAGE AND CMAKE_COMPILER_IS_GNUCXX )
  set( C2BB_COVERAGE "${COVERAGE}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE )
endif()

# MEMCHECK ==> CSIM_MEMCHECK
set(_PARAM_ANNOTATION "Enable memcheck testing.")
if(CMAKE_COMPILER_IS_GNUCXX)
  set( C2BB_MEMCHECK OFF CACHE BOOL ${_PARAM_ANNOTATION} )
endif()
if( MEMCHECK AND CMAKE_COMPILER_IS_GNUCXX )
  set( C2BB_MEMCHECK "${MEMCHECK}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE )
endif()

if(C2BB_COVERAGE OR CSIM_MEMCHECK)
  set(C2BB_UNIT_TESTS ON)
endif()

# TWAE ==> C2BB_WARNINGS_AS_ERRORS -- Note: This excludes third party code, where warnings are never treated as errors.
set(_PARAM_ANNOTATION "Treat warnings as errors (note: warnings in 3rd party code are never treated as errors)")
set( C2BB_TREAT_WARNINGS_AS_ERRORS OFF CACHE BOOL ${_PARAM_ANNOTATION} )
if( TWAE )
  set( C2BB_TREAT_WARNINGS_AS_ERRORS "${TWAE}" CACHE BOOL ${_PARAM_ANNOTATION} FORCE )
endif()

# BUILD_TYPE ==> C2BB_BUILD_TYPE
set(_PARAM_ANNOTATION "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
set( C2BB_BUILD_TYPE "Release" CACHE STRING ${_PARAM_ANNOTATION} )
if( BUILD_TYPE )
  set( C2BB_BUILD_TYPE ${BUILD_TYPE} CACHE STRING ${_PARAM_ANNOTATION} FORCE )
endif()
if( C2BB_MEMCHECK OR C2BB_COVERAGE)
  set( C2BB_BUILD_TYPE "Debug" CACHE STRING ${_PARAM_ANNOTATION} FORCE )
endif()

# INSTALL_PREFIX ==> C2BB_INSTALL_PREFIX
set(_PARAM_ANNOTATION "Install path prefix, prepended onto install directories.")
set( C2BB_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} CACHE PATH ${_PARAM_ANNOTATION} )
if( INSTALL_PREFIX )
  set( C2BB_INSTALL_PREFIX ${INSTALL_PREFIX} CACHE PATH ${_PARAM_ANNOTATION} FORCE )
endif()

# CSIM_DEPENDENCY_DIR
set(_PARAM_ANNOTATION "Dependency prefix (where to find non-system dependencies)")
set( C2BB_DEPENDENCY_DIR "/usr/local" CACHE STRING ${_PARAM_ANNOTATION} )
if( DEPENDENCY_DIR )
  set( C2BB_DEPENDENCY_DIR ${DEPENDENCY_DIR} CACHE STRING ${_PARAM_ANNOTATION} FORCE )
endif()

# Keep the GUI tidy.
internalise_cmake_variables()
hide_distracting_variables()

# c2bb target
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

if (BUILD_TESTING)
  # enable testing here so that we can make use of the 'test' target
  enable_testing()
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()

#add_subdirectory(examples/cvode-integrator)



