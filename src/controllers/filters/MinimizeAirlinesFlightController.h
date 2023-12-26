// MinimizeAirlinesFlightController.h
#ifndef PROJECT_AED_AIRPORTS_MINIMIZEAIRLINESFLIGHTCONTROLLER_H
#define PROJECT_AED_AIRPORTS_MINIMIZEAIRLINESFLIGHTCONTROLLER_H

#include "../FlightController.h"
#include <vector>

class MinimizeAirlinesFlightController : public FlightController {
public:
    vector<vector<Airport>> getShortestPathsBFS(const Airport &origin, const Airport &destination) override;
};

#endif //PROJECT_AED_AIRPORTS_MINIMIZEAIRLINESFLIGHTCONTROLLER_H