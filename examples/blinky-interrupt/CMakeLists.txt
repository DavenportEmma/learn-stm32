cmake_minimum_required(VERSION 3.27.3)

include(${SDK_BASE}/cmake/common.cmake)

project(blinky C)

target_sources(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f7xx_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f7xx_hal_msp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32f7xx_nucleo_144.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)