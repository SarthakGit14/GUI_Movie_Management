#ifndef MOVIE_H
#define MOVIE_H

#include <string>

class Movie
{
private:
    int id;
    std::string title;
    std::string genre;
    float rating;
    bool available;
    int rentPrice;
    int buyPrice;

public:
    Movie();

    Movie(
        int id,
        const std::string& title,
        const std::string& genre,
        float rating,
        bool available,
        int rentPrice,
        int buyPrice
    );

    // Getters
    int getId() const;
    std::string getTitle() const;
    std::string getGenre() const;
    float getRating() const;
    bool isAvailable() const;
    int getRentPrice() const;
    int getBuyPrice() const;

    // Setters
    void setAvailable(bool status);
};

#endif