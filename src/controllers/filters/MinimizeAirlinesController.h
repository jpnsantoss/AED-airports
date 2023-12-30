
#ifndef PROJECT_AED_AIRPORTS_MINIMIZEAIRLINESCONTROLLER_H
#define PROJECT_AED_AIRPORTS_MINIMIZEAIRLINESCONTROLLER_H

#include "controllers/BestOptionController.h"
#include <vector>
#include <stdexcept>
#include <set>

class MinimizeAirlinesController : public BestOptionController {
public:
    vector<vector<Airport>> getShortestPathsBFS(const Airport &origin, const Airport &destination) override;
};

#endif //PROJECT_AED_AIRPORTS_MINIMIZEAIRLINESCONTROLLER_H