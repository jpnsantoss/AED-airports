cmake_minimum_required(VERSION 3.25)
project(Project_AED_Airports)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(Project_AED_Airports src/main.cpp
        src/Dataset.cpp
        src/Dataset.h
        src/models/Airport.cpp
        src/models/Airport.h
        src/models/Airline.cpp
        src/models/Airline.h
        src/models/Location.cpp
        src/models/Location.h
        src/models/Flight.cpp
        src/models/Flight.h
        src/utils/Graph.cpp
        src/utils/Graph.h
        src/utils/CSVReader.cpp
        src/utils/CSVReader.h
        src/controllers/FlightManagement.cpp
        src/controllers/FlightManagement.h
        src/views/Menu.cpp
        src/views/Menu.h)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)
