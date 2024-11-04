project(R-Type-Utils)

set(NAME_LIB_UTILS "Utils")
set(NAME_DEBUG_EXE "${RTYPE}-Utils-Debug")

set(LIB_SOURCES
    ./ParametersMap/ParametersMap.cpp
    ./Response/Response.cpp
    ./Protocol/Protocol.cpp
    ./Network/Network.cpp
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_library(${NAME_LIB_UTILS} STATIC ${LIB_SOURCES})

set_target_properties(${NAME_LIB_UTILS} PROPERTIES
    OUTPUT_NAME ${NAME_LIB_UTILS}
    SUFFIX ".a"
)

target_link_libraries(${NAME_LIB_UTILS} PUBLIC ${NAME_LIB})

target_include_directories(${NAME_LIB_UTILS} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}Protocol
    ${CMAKE_CURRENT_SOURCE_DIR}Response
)
