# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Praktikum2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Praktikum2_autogen.dir\\ParseCache.txt"
  "Praktikum2_autogen"
  )
endif()
