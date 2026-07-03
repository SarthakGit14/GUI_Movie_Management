#ifndef MOVIEMANAGER_H
#define MOVIEMANAGER_H

#include <vector>
#include <string>
#include "Database.h"
#include "Movie.h"
#include "User.h"

class MovieManager
{
private:
    Database database;

    std::vector<Movie> movies;
    std::vector<User> users;

    User* currentUser;

    int nextMovieId;
    int nextUserId;

public:
    MovieManager();
    ~MovieManager();

    bool initializeDatabase();
    // Authentication
    bool login(const std::string& username,
               const std::string& password);

    bool signup(const std::string& username,
                const std::string& password);

    void logout();

    User* getCurrentUser();

    std::vector<User> getUsers();

    // Movies
    std::vector<Movie>& getMovies();


    bool rentMovie(int movieId);

    bool purchaseMovie(int movieId);

    bool returnMovie(int movieId);

    // Admin
    void addMovie(const Movie& movie);

    bool removeMovie(int movieId);

     // Statistics
    int totalMovies() const;
    int availableMovies() const;
    int rentedMovies() const;
    int totalUsers() const;
    int getCurrentUserId() const;

    // Rental History
    struct RentalInfo
    {
        std::string username;
        std::string movie;
        std::string rentDate;
        std::string status;
    };

    // Purchase History
    struct PurchaseInfo
    {
        std::string username;
        std::string movie;
        std::string purchaseDate;
    };

    std::vector<RentalInfo> getRentalHistory();
    std::vector<PurchaseInfo> getPurchases();
};

#endif