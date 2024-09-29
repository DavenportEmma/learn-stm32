if(DEFINED CONFIG_FREERTOS)
    target_sources(${PROJECT_NAME} PUBLIC
        ${SDK_BASE}/modules/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/port.c
        ${SDK_BASE}/modules/FreeRTOS/FreeRTOS/Source/portable/MemMang/heap_4.c
        ${SDK_BASE}/modules/FreeRTOS/FreeRTOS/Source/tasks.c
        ${SDK_BASE}/modules/FreeRTOS/FreeRTOS/Source/list.c
        ${SDK_BASE}/modules/FreeRTOS/FreeRTOS/Source/queue.c
        ${SDK_BASE}/modules/FreeRTOS/FreeRTOS/Source/stream_buffer.c
        ${SDK_BASE}/modules/FreeRTOS/FreeRTOS/Source/timers.c
    )

    target_include_directories(${PROJECT_NAME} PUBLIC
        ${SDK_BASE}/modules/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1
        ${SDK_BASE}/modules/FreeRTOS/FreeRTOS/Source/include
    )
endif()

if(DEFINED CONFIG_MIDI)
    target_sources(${PROJECT_NAME} PUBLIC
        ${SDK_BASE}/src/midi.c
    )
endif()

if(DEFINED CONFIG_UART)
    target_sources(${PROJECT_NAME} PUBLIC
        ${SDK_BASE}/src/uart.c
    )
endif()