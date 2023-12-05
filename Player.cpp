#include "Player.hpp"

Player::Player(std::string name, int score, double multiplier)
{
    this->name = name;
    this->score = score;
    this->multiplier = multiplier;
}

void Player::SetName(std::string name)
{
    this->name = name;
}

void Player::UpdateScore(int factor)
{
    if(factor < 0)
    {
        if(this->score - factor <= 0)
            this->score = 0;
        else
            this->score += factor;
    }
    else
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

std::string Player::GetName() const
{
    return this->name;
}

double Player::GetCurrentMultiplier() const
{
    return this->multiplier;
}