cmake_minimum_required(VERSION 3.0.0)
project(ultraschall VERSION 4.0.0)

# taglib includes
include_directories(
  external/taglib/include
  external/taglib/include/toolkit
  external/taglib/include/mpeg
  external/taglib/include/mpeg/id3v2
  external/taglib/include/mpeg/id3v2/frames
  external/taglib/include/bindings/c
)

# mp4v2 includes
include_directories(
  external/mp4v2/include
)

# public includes
include_directories(
  include/ultraschall
)

include(CTest)
enable_testing()

add_library(ultraschall SHARED
  src/Framework.cpp
  src/ServiceFactory.cpp
  src/Tag.cpp
  src/Cover.cpp
)

find_library(MP4V2_LIB mp4v2 "external/mp4v2/lib/macos/debug")
find_library(TAG_LIB tag "external/taglib/lib/macos/debug")
target_link_libraries(ultraschall ${MP4V2_LIB} ${TAG_LIB})

set_target_properties(ultraschall PROPERTIES VERSION ${PROJECT_VERSION})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
