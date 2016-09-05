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

cmake_minimum_required(VERSION 3.5)

project(c2bb VERSION 1.0 LANGUAGES CXX)

# The version number.
set(C2BB_VERSION_MAJOR 1)
set(C2BB_VERSION_MINOR 0)
set(C2BB_VERSION_PATCH 0)

foreach(VERSION_PART C2BB_VERSION_MAJOR C2BB_VERSION_MINOR C2BB_VERSION_PATCH)
  string(LENGTH ${${VERSION_PART}} VERSION_PART_LENGTH)
  if(VERSION_PART_LENGTH EQUAL 1)
    set(${VERSION_PART}_PAD 0)
  endif()
endforeach()
set(C2BB_VERSION 0x${C2BB_VERSION_MAJOR_PAD}${C2BB_VERSION_MAJOR}${C2BB_VERSION_MINOR_PAD}${C2BB_VERSION_MINOR}${C2BB_VERSION_PATCH_PAD}${C2BB_VERSION_PATCH})
set(C2BB_VERSION_STRING "${C2BB_VERSION_MAJOR}.${C2BB_VERSION_MINOR}.${C2BB_VERSION_PATCH}")

set(C2BB_CONFIG_H "${CMAKE_CURRENT_BINARY_DIR}/c2bb_config.h")
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/src/configure/C2BB_config.h.in"
  ${C2BB_CONFIG_H}
)

find_package(csim CONFIG REQUIRED)

set(SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/version.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c2bb.cpp
)

set(HEADER_FILES
  ${C2BB_CONFIG_H}
)

add_executable(c2bb
  ${SOURCE_FILES}
  ${HEADER_FILES}
)

target_include_directories(c2bb
  PUBLIC
  PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(c2bb PUBLIC
  csim
)

set_target_properties(c2bb PROPERTIES
    OUTPUT_NAME c2bb
    VERSION ${C2BB_VERSION_STRING}
)

set_target_properties(c2bb PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)

install(TARGETS c2bb
  RUNTIME DESTINATION bin
)

set(CPACK_PACKAGE_VERSION_MAJOR "${C2BB_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${C2BB_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${C2BB_VERSION_PATCH}")

if(WIN32)
  set(CPACK_GENERATOR ZIP)
else()
  set(CPACK_GENERATOR TGZ)
endif()

include(CPack)
