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
