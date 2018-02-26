get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(${SELF_DIR}/ngsocket-targets.cmake)
get_filename_component(ngsocket_INCLUDE_DIRS "${SELF_DIR}/../../include" ABSOLUTE)

find_library(ngsocket_LIBRARY
        ngsocket
        PATHS "${SELF_DIR}/../../lib/"
        PATH_SUFFIXES ngsocket
        NO_DEFAULT_PATH)

set(ngsocket_LIBRARIES ${ngsocket_LIBRARY})