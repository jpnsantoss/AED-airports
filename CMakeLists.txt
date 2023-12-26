cmake_minimum_required(VERSION 3.25)
project(Project_AED_Airports)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(Project_AED_Airports src/main.cpp
        src/models/Airport.cpp
        src/models/Airport.h
        src/models/Airline.cpp
        src/models/Airline.h
        src/models/Flight.cpp
        src/models/Flight.h
        src/utils/Graph.h
        src/views/Menu.cpp
        src/views/Menu.h
        src/views/MainMenu.h
        src/utils/Dataset.cpp
        src/utils/Dataset.h
        src/models/Location.cpp
        src/models/Location.h
        src/controllers/FlightController.cpp
        src/controllers/FlightController.h
        src/views/FlightTest.h
        src/controllers/filters/MinimizeAirlinesFlightController.cpp
        src/controllers/filters/MinimizeAirlinesFlightController.h
        src/controllers/filters/AirlineFilterFlightController.cpp
        src/controllers/filters/AirlineFilterFlightController.h
        src/views/bestOption/FilterSelectionView.h
        src/views/bestOption/SourceSelectionView.h
        src/views/bestOption/DestinationSelectionView.h
)

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
