# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\cainiao_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\cainiao_autogen.dir\\ParseCache.txt"
  "cainiao_autogen"
  )
endif()
