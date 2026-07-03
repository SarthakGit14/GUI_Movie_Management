#include "Movie.h"

Movie::Movie()
{
    id = 0;
    title = "";
    genre = "";
    rating = 0.0f;
    available = true;
    rentPrice = 0;
    buyPrice = 0;
}

Movie::Movie(
    int id,
    const std::string& title,
    const std::string& genre,
    float rating,
    bool available,
    int rentPrice,
    int buyPrice)
{
    this->id = id;
    this->title = title;
    this->genre = genre;
    this->rating = rating;
    this->available = available;
    this->rentPrice = rentPrice;
    this->buyPrice = buyPrice;
}

int Movie::getId() const
{
    return id;
}

std::string Movie::getTitle() const
{
    return title;
}

std::string Movie::getGenre() const
{
    return genre;
}

float Movie::getRating() const
{
    return rating;
}

bool Movie::isAvailable() const
{
    return available;
}

int Movie::getRentPrice() const
{
    return rentPrice;
}

int Movie::getBuyPrice() const
{
    return buyPrice;
}

void Movie::setAvailable(bool status)
{
    available = status;
}