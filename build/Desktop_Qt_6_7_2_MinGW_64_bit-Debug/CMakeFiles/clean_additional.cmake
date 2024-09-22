# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DebugConsoleZero_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DebugConsoleZero_autogen.dir\\ParseCache.txt"
  "DebugConsoleZero_autogen"
  )
endif()
