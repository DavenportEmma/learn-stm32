cmake_minimum_required(VERSION 3.27.1)

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
	set(CMAKE_MAKE_PROGRAM ${SDK_BASE}/modules/ninja/ninja CACHE INTERNAL "" FORCE)
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
	set(CMAKE_MAKE_PROGRAM ${SDK_BASE}/modules/ninja/ninja.exe CACHE INTERNAL "" FORCE)
endif()

set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "" FORCE)