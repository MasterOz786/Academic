
#pragma once

struct PlayerData {
    std::string name;
    int score;

    PlayerData() : name(""), score(0) {}
    PlayerData(std::string name, int score) : name(name), score(score) {}
};

#include <iostream>
class Player {
    private:
        std::string name;
        int score;
        double multiplier;

    public:
        Player()
        {
            this->name = "";
            this->score = 0;
            this->multiplier = 1.0;
        }
        Player(std::string name, int score = 0, double multiplier = 1.0);

        void SetName(std::string name);
        void UpdateScore(int factor);
        void UpdateMultiplier(double multiplier);

        int GetCurrentScore() const;
        double GetCurrentMultiplier() const;
        std::string GetName() const;
};
