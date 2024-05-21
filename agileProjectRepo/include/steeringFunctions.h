
#pragma once

void stopEngines()
{
    for (auto &engine : engines)
    {
        engine.setVelocity(0);
    }
}

void setEnginesVelocity(int velocity)
{
    for (auto &engine : engines)
    {
        engine.setVelocity(velocity);
    }
}