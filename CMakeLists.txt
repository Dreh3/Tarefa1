# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_sdk_import.cmake)
project(tarefa1 C CXX ASM)
pico_sdk_init()
add_executable(tarefa1 tarefa1.c )
pico_set_program_name(tarefa1 "tarefa1")
pico_set_program_version(tarefa1 "0.1")
pico_enable_stdio_uart(tarefa1 1)
pico_enable_stdio_usb(tarefa1 1)
target_link_libraries(tarefa1
        pico_stdlib
        hardware_pio
        )
target_include_directories(tarefa1 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

#Gerar arquivo cabeçalho pio
pico_generate_pio_header(${CMAKE_PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/pio_matrix.pio)

pico_add_extra_outputs(tarefa1)

