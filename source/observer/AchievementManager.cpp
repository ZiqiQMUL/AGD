#include "../../include/observer/AchievementManager.h"
#include <iostream>

AchievementManager::AchievementManager()
{
    resetShout();
    resetPotion();
}

void AchievementManager::onNotify(const std::string& event)
{
    if (event == "shout")
    {
        shoutCount++;
        std::cout << "Shout count: " << shoutCount << std::endl;
        if (shoutCount >= totalShouts)
        {
            std::cout << "=====================Shouted 5 times!=====================" << std::endl;
            resetShout();
        }
    }
    else if (event == "potion")
    {
        potionCount++;
        std::cout << "Potion count: " << potionCount << std::endl;
        if (potionCount >= totalPotions)
        {
            std::cout << "=====================Collected all potions!=====================" << std::endl;
            resetPotion();
        }
    }
}

void AchievementManager::resetShout()
{
    shoutCount = 0;
}

void AchievementManager::resetPotion()
{
    potionCount = 0;
}
