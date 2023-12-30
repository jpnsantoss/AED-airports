
#ifndef PROJECT_AED_AIRPORTS_AIRLINEFILTERCONTROLLER_H
#define PROJECT_AED_AIRPORTS_AIRLINEFILTERCONTROLLER_H

#include "../FlightController.h"
#include "controllers/BestOptionController.h"
#include <vector>
#include <string>

class AirlineFilterController : public BestOptionController {
public:
    explicit AirlineFilterController(const std::vector<std::string>& airlines);
};

#endif //PROJECT_AED_AIRPORTS_AIRLINEFILTERCONTROLLER_H