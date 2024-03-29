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
        src/views/Menu.h
        src/views/MainMenu.h
        src/utils/Dataset.cpp
        src/utils/Dataset.h
        src/models/Location.cpp
        src/models/Location.h
        src/controllers/FlightController.cpp
        src/controllers/FlightController.h
        src/controllers/filters/MinimizeAirlinesController.cpp
        src/controllers/filters/MinimizeAirlinesController.h
        src/controllers/filters/AirlineFilterController.cpp
        src/controllers/filters/AirlineFilterController.h
        src/views/StatisticsMenu.h
        src/views/StatisticsMenu.cpp
        src/controllers/StatisticsController.h
        src/controllers/StatisticsController.cpp
        src/controllers/BestOptionController.cpp
        src/controllers/BestOptionController.h
        src/views/BestOption.cpp
        src/views/BestOption.h
        src/views/MainMenu.cpp
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
