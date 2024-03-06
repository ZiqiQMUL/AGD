#pragma once

#include "../../include/observer/Observer.h"
#include <string>

class AchievementManager : public Observer
{
private:
    int shoutCount = 0;
    int potionCount = 0;
    const int totalPotions = 6;
    const int totalShouts = 5;

public:
    AchievementManager();

    void onNotify(const std::string& event) override;

    void resetShout();
    void resetPotion();
};
