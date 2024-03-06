#pragma once///Step_3a
#include "Components.h"

class HealthComponent :public Component
{
public:
    HealthComponent(int startHealth, int maxHealth) : currentHealth(startHealth), maximumHealth(maxHealth) {}

    int getHealth() const { return currentHealth; }

    void changeHealth(int change)
    {
        currentHealth += change;
        if (currentHealth < 0)
        {
            currentHealth = 0;
        }
        else if (currentHealth > maximumHealth)
        {
            currentHealth = maximumHealth;
        }
    }
    ComponentID getID()const override { return ComponentID::HEALTH; }

protected:
    int currentHealth;
    int maximumHealth;
};
