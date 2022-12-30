cmake_minimum_required(VERSION 3.22)
project(DemoLaunch C)

set(CMAKE_C_STANDARD 11)

set(PATH_TO_SOURCES ../../../sources)
set(PATH_TO_DRIVERS ../../../drivers/LinuxDriver)

add_executable(${PROJECT_NAME}
        ${PATH_TO_DRIVERS}/driver_Linux.c
        ${PATH_TO_DRIVERS}/driver_Linux.h
        ${PATH_TO_SOURCES}/adjvar/adjvar.c
        ${PATH_TO_SOURCES}/adjvar/adjvar.h
        ${PATH_TO_SOURCES}/calib/calib.c
        ${PATH_TO_SOURCES}/calib/calib.h
        ${PATH_TO_SOURCES}/core/core.c
        ${PATH_TO_SOURCES}/core/core.h
        ${PATH_TO_SOURCES}/eeprom/eeprom.c
        ${PATH_TO_SOURCES}/eeprom/eeprom.h
        ${PATH_TO_SOURCES}/gimbalControl/gimbalControl.c
        ${PATH_TO_SOURCES}/gimbalControl/gimbalControl.h
        ${PATH_TO_SOURCES}/imu/imu.c
        ${PATH_TO_SOURCES}/imu/imu.h
        ${PATH_TO_SOURCES}/profiles/profiles.c
        ${PATH_TO_SOURCES}/profiles/profiles.h
        ${PATH_TO_SOURCES}/realtime/realtime.c
        ${PATH_TO_SOURCES}/realtime/realtime.h
        ${PATH_TO_SOURCES}/service/service.c
        ${PATH_TO_SOURCES}/service/service.h
        main.c)

target_include_directories(${PROJECT_NAME} PRIVATE ../../../drivers/LinuxDriver)
target_include_directories(${PROJECT_NAME} PRIVATE ../../../sources)
