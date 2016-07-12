#---------------------------------------------------------------------------//
# Copyright 2016 Lukasz Wojcicki
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#---------------------------------------------------------------------------//

cmake_minimum_required(VERSION 2.8)

project (sjepmine)
set(CMAKE_BUILD_TYPE Release)

set(SRCS
    src/ClassData.cpp
    src/SJEPExtractor.cpp
    src/CpItem.cpp
    src/CpItemset.cpp
    src/CPTree/CPNode.cpp
    src/CPTree/CPNodeItem.cpp
    src/CPTree/CPTree.cpp
    src/SJEP.cpp
    )

set(HDRS
    src/ClassData.h
    src/SJEPExtractor.h
    src/CpItem.h
    src/CpItemset.h
    src/SJEP.h
    )

set(HDRS_CPTREE
    src/CPTree/CPNode.h
    src/CPTree/CPNodeItem.h
    src/CPTree/CPTree.h
    )

add_library(sjepmine SHARED ${SRCS})

set(SJEPMINE_VERSION_MAJOR 1)
set(SJEPMINE_VERSION_MINOR 0)
set(SJEPMINE_VERSION_PATCH 0)
set(SJEPMINE_VERSION ${SJEPMINE_VERSION_MAJOR}.${SJEPMINE_VERSION_MINOR}.${SJEPMINE_VERSION_PATCH} )

set_target_properties(sjepmine PROPERTIES VERSION ${SJEPMINE_VERSION}
    SOVERSION ${SJEPMINE_VERSION_MAJOR} )

install(TARGETS sjepmine DESTINATION lib)
install(FILES ${HDRS} DESTINATION include)
install(FILES ${HDRS_CPTREE} DESTINATION include/CPTree)
