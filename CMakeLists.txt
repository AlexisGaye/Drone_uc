cmake_minimum_required(VERSION 3.10)

project(Drone NONE)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# output compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#language
enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# add startup file
set(STARTUP_FILE ${CMAKE_CURRENT_SOURCE_DIR}/CORE/startup_stm32f401xe.s)
set(OS_CPU_A_FILE ${CMAKE_CURRENT_SOURCE_DIR}/os/os_cpu_a.s)

# add .h
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32F401RETx_FLASH.ld)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/CORE)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/FWLIB/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/HARDWARE/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SYSTEM/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/USER/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/os/inc)

# add .c
file(GLOB SOURCE 
"${CMAKE_CURRENT_SOURCE_DIR}/USER/src/*.c" 
"${CMAKE_CURRENT_SOURCE_DIR}/FWLIB/src/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/HARDWARE/src/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/SYSTEM/src/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/os/src/*.c" 
)
set(SOURCE_FILES ${SOURCE})

# set compiler and linker
set(CMAKE_C_COMPILER /opt/gcc-arm-none-eabi/bin/arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER /opt/gcc-arm-none-eabi/bin/arm-none-eabi-gcc)                                                        
set(CMAKE_LINKER /opt/gcc-arm-none-eabi/bin/arm-none-eabi-ld)

# 增加宏定义
add_definitions(-DSTM32F401xx -DUSE_STDPERIPH_DRIVER)

# 设置编译选项
set(CMAKE_C_FLAGS "-mthumb -mcpu=cortex-m4 -std=c99 -g -Os \
    -ffunction-sections -fdata-sections -Wall -Wextra \
    -Wno-self-assign -Wno-unused-parameter -Wno-empty-body")
# set(CMAKE_CXX_FLAGS "-mthumb -mcpu=cortex-m4 -std=gnu++17 -g -Os -ffunction-sections -fdata-sections -Wall -Wextra")
set(CMAKE_ASM_FLAGS "-mthumb -mcpu=cortex-m4 -g -x assembler-with-cpp")

# 设置链接选项
add_link_options(-mcpu=cortex-m4 -mthumb -DSTM32F401xx -T${CMAKE_SOURCE_DIR}/STM32F401RETx_FLASH.ld --specs=nano.specs -u _printf_float -lc -lm -Wl,-Map=${CMAKE_SOURCE_DIR}/build/${CMAKE_PROJECT_NAME}.map,--cref -Wl,--gc-sections)

# ${OS_CPU_A_FILE}
# 添加可执行文件
add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES} ${STARTUP_FILE} ${OS_CPU_A_FILE})
target_link_libraries(${PROJECT_NAME}.elf -Wl,--start-group -lgcc -lc -lm -lrdimon -Wl,--end-group)


# 添加目标文件
add_custom_target(${PROJECT_NAME}.bin ALL DEPENDS ${PROJECT_NAME}.elf COMMAND arm-none-eabi-objcopy -Obinary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)