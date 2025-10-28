cmake_minimum_required(VERSION 3.22)
project(DemoLaunch C)

set(CMAKE_C_STANDARD 11)

set(PATH_TO_SERIAL_API ../../../serialAPI)
set(PATH_TO_CORE ../../../serialAPI/core)
set(PATH_TO_DRIVERS ../../../serialAPI/drivers/driverLinux)
set(PATH_TO_MODULES ../../../serialAPI/modules)
set(PATH_TO_OS_GLUE ../../../serialAPI/os)


add_executable(${PROJECT_NAME}
        ${PATH_TO_CORE}/debug/debug.c
        ${PATH_TO_CORE}/debug/debug.h
        ${PATH_TO_CORE}/highLayer/highLayer.c
        ${PATH_TO_CORE}/highLayer/highLayer.h
        ${PATH_TO_CORE}/parser/parser.c
        ${PATH_TO_CORE}/parser/parser.h
        ${PATH_TO_CORE}/commandBuild.c
        ${PATH_TO_CORE}/core.h
        ${PATH_TO_CORE}/lowLayer.c

        ${PATH_TO_DRIVERS}/driverLinux.c
        ${PATH_TO_DRIVERS}/driverLinux.h

        ${PATH_TO_MODULES}/adjvar/adjvar.c
        ${PATH_TO_MODULES}/adjvar/adjvar.h
        ${PATH_TO_MODULES}/calib/calib.c
        ${PATH_TO_MODULES}/calib/calib.h
        ${PATH_TO_MODULES}/eeprom/eeprom.c
        ${PATH_TO_MODULES}/eeprom/eeprom.h
        ${PATH_TO_MODULES}/gimbalControl/gimbalControl.c
        ${PATH_TO_MODULES}/gimbalControl/gimbalControl.h
        ${PATH_TO_MODULES}/imu/imu.c
        ${PATH_TO_MODULES}/imu/imu.h
        ${PATH_TO_MODULES}/profiles/profiles.c
        ${PATH_TO_MODULES}/profiles/profiles.h
        ${PATH_TO_MODULES}/realtime/realtime.c
        ${PATH_TO_MODULES}/realtime/realtime.h
        ${PATH_TO_MODULES}/service/service.c
        ${PATH_TO_MODULES}/service/service.h

        ${PATH_TO_OS_GLUE}/glueAzureRTOS/glueAzureRTOS.c
        ${PATH_TO_OS_GLUE}/glueAzureRTOS/glueAzureRTOS.h
        ${PATH_TO_OS_GLUE}/glueFreeRTOS/glueFreeRTOS.c
        ${PATH_TO_OS_GLUE}/glueFreeRTOS/glueFreeRTOS.h
        ${PATH_TO_OS_GLUE}/gluePThread/gluePThread.c
        ${PATH_TO_OS_GLUE}/gluePThread/gluePThread.h

        ${PATH_TO_SERIAL_API}/adjunct.h
        ${PATH_TO_SERIAL_API}/sbgc32.c
        ${PATH_TO_SERIAL_API}/sbgc32.h

        main.c serialAPI_Config.h)


target_include_directories(${PROJECT_NAME} PUBLIC .)
target_include_directories(${PROJECT_NAME} PUBLIC ../../../serialAPI)