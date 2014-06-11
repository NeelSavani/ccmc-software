# c wrapper library
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${KAMELEON_LIB_DIR}/ccmc/c) 
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${KAMELEON_LIB_DIR}/ccmc/c)
file(GLOB CCMC_WRAPPER_C_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
file(GLOB CCMC_WRAPPER_C_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)
set(CMAKE_CXX_FLAGS "-fPIC")

set(ALL_SOURCE ${CCMC_WRAPPER_C_SOURCES})
set(ALL_HEADER ${CCMC_WRAPPER_C_HEADER})

add_library(ccmc_wrapper_c ${ALL_SOURCE} ${ALL_HEADER})

# include ccmc
include_directories(${KAMELEON_SRC_DIR})

target_link_libraries(ccmc_wrapper_c ccmc)