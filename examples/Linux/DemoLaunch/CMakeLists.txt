cmake_minimum_required(VERSION 3.22)
project(SBGC32_LinuxDebug C)

set(CMAKE_C_STANDARD 11)

set(PATH_TO_SERIAL_API ../../../serialAPI)
set(PATH_TO_SOURCES ../../../serialAPI/sources)
set(PATH_TO_DRIVERS ../../../serialAPI/drivers/LinuxDriver)

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

        ${PATH_TO_SERIAL_API}/adjunct.h
        ${PATH_TO_SERIAL_API}/sbgc32.c
        ${PATH_TO_SERIAL_API}/sbgc32.h

        main.c serialAPI_Config.h)


target_include_directories(${PROJECT_NAME} PUBLIC .)
target_include_directories(${PROJECT_NAME} PUBLIC ../../../serialAPI)