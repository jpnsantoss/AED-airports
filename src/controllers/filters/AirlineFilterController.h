
#ifndef PROJECT_AED_AIRPORTS_AIRLINEFILTERCONTROLLER_H
#define PROJECT_AED_AIRPORTS_AIRLINEFILTERCONTROLLER_H

#include "controllers/BestOptionController.h"
#include <vector>
#include <string>

class AirlineFilterController : public BestOptionController {
public:
    explicit AirlineFilterController(const vector<string>& airlines);
};

#endif //PROJECT_AED_AIRPORTS_AIRLINEFILTERCONTROLLER_H