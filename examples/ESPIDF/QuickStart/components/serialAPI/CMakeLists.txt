# components/serialAPI/CMakeLists.txt

set(SBGC_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../../../../serialAPI")

file(GLOB_RECURSE SBGC_SRCS
	"${SBGC_ROOT}/*.c"
    "${SBGC_ROOT}/core/*.c"
    "${SBGC_ROOT}/modules/*.c"
    "${SBGC_ROOT}/os/*.c"
    "${SBGC_ROOT}/drivers/driverESP32/*.c"
)

idf_component_register(
    SRCS ${SBGC_SRCS}
    INCLUDE_DIRS
        "${SBGC_ROOT}"
        "${CMAKE_CURRENT_LIST_DIR}/include"
    REQUIRES
        driver
        esp_timer
        freertos
        log
)
