
#include "Player.hpp"

Player::Player(std::string name, int score, double multiplier)
{
    this->name = name;
    this->score = score;
    this->multiplier = multiplier;
}

void Player::UpdateScore(int factor)
{
    this->score += factor * multiplier;
}

void Player::UpdateMultiplier(double multiplier)
{
    this->multiplier = multiplier;
}

int Player::GetCurrentScore() const
{
    return this->score;
}

double Player::GetCurrentMultiplier() const
{
    return this->multiplier;
}
