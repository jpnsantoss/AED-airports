// AirlineFilterFlightController.h
#ifndef PROJECT_AED_AIRPORTS_AIRLINEFILTERFLIGHTCONTROLLER_H
#define PROJECT_AED_AIRPORTS_AIRLINEFILTERFLIGHTCONTROLLER_H

#include "../FlightController.h"
#include <vector>
#include <string>

class AirlineFilterFlightController : public FlightController {
public:
    AirlineFilterFlightController(const std::vector<std::string>& airlines);
};

#endif //PROJECT_AED_AIRPORTS_AIRLINEFILTERFLIGHTCONTROLLER_H