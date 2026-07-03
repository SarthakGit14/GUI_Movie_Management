#include "MovieManager.h"
#include <sqlite3.h>
MovieManager::MovieManager()
{
    currentUser = nullptr;
    
    
    
}



bool MovieManager::login(
    const std::string& username,
    const std::string& password)
{
    sqlite3_stmt* stmt;

    const char* sql =
        "SELECT id, username, password, admin "
        "FROM Users "
        "WHERE username=? AND password=?;";

    if(sqlite3_prepare_v2(
            database.getDB(),
            sql,
            -1,
            &stmt,
            nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_text(
        stmt,
        1,
        username.c_str(),
        -1,
        SQLITE_TRANSIENT);

    sqlite3_bind_text(
        stmt,
        2,
        password.c_str(),
        -1,
        SQLITE_TRANSIENT);

    bool success = false;

    if(sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);

        std::string uname =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt,1));

        std::string pass =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt,2));

        bool admin =
            sqlite3_column_int(stmt,3);

        currentUser = new User(
            id,
            uname,
            pass,
            admin);

        currentUser->setLoggedIn(true);

        success = true;
    }

    sqlite3_finalize(stmt);

    return success;
}

bool MovieManager::signup(
    const std::string& username,
    const std::string& password)
{
    if(username.empty() || password.empty())
        return false;

    sqlite3_stmt* stmt;

    const char* sql =
        "INSERT INTO Users(username,password,admin)"
        " VALUES(?,?,0);";

    if(sqlite3_prepare_v2(
            database.getDB(),
            sql,
            -1,
            &stmt,
            nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_text(
        stmt,
        1,
        username.c_str(),
        -1,
        SQLITE_TRANSIENT);

    sqlite3_bind_text(
        stmt,
        2,
        password.c_str(),
        -1,
        SQLITE_TRANSIENT);

    bool success =
        sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);

    return success;
}

bool MovieManager::initializeDatabase()
{
    return database.open("../MovieRental.db");
}

void MovieManager::logout()
{
    if(currentUser)
    {
        currentUser->setLoggedIn(false);
        currentUser = nullptr;
    }
}

User* MovieManager::getCurrentUser()
{
    return currentUser;
} 

std::vector<Movie>& MovieManager::getMovies()
{
    movies.clear();

    sqlite3_stmt* stmt;

    const char* sql =
        "SELECT id,title,genre,rating,available,rentPrice,buyPrice "
        "FROM Movies;";

    if(sqlite3_prepare_v2(
            database.getDB(),
            sql,
            -1,
            &stmt,
            nullptr) != SQLITE_OK)
    {
        return movies;
    }

    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        Movie movie(
            sqlite3_column_int(stmt,0),

            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt,1)),

            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt,2)),

            sqlite3_column_double(stmt,3),

            sqlite3_column_int(stmt,4),

            sqlite3_column_int(stmt,5),

            sqlite3_column_int(stmt,6)
        );

        movies.push_back(movie);
    }

    sqlite3_finalize(stmt);

    return movies;
}

bool MovieManager::rentMovie(int movieId)
{
    sqlite3_stmt* stmt;

    const char* sql =
        "UPDATE Movies SET available=0 "
        "WHERE id=? AND available=1;";

    if(sqlite3_prepare_v2(
            database.getDB(),
            sql,
            -1,
            &stmt,
            nullptr)!=SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt,1,movieId);

    bool success =
        sqlite3_step(stmt)==SQLITE_DONE &&
        sqlite3_changes(database.getDB())>0;

    sqlite3_finalize(stmt);

    if(success)
    {
        std::string insert =
            "INSERT INTO Rentals(userId,movieId,rentDate,status)"
            " VALUES("
            + std::to_string(currentUser->getId())
            + ","
            + std::to_string(movieId)
            + ",date('now'),'Rented');";

        database.execute(insert);
    }

    return success;
}

bool MovieManager::purchaseMovie(int movieId)
{
    if(currentUser == nullptr)
        return false;

    sqlite3_stmt* stmt;

    const char* sql =
        "INSERT INTO Purchases(userId,movieId,purchaseDate)"
        " VALUES(?,?,date('now'));";

    if(sqlite3_prepare_v2(
            database.getDB(),
            sql,
            -1,
            &stmt,
            nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt,1,currentUser->getId());
    sqlite3_bind_int(stmt,2,movieId);

    bool success = sqlite3_step(stmt)==SQLITE_DONE;

    sqlite3_finalize(stmt);

    if(success)
    {
        removeMovie(movieId);
    }

    return success;
}

bool MovieManager::returnMovie(int movieId)
{
    sqlite3_stmt* stmt;

    const char* sql =
        "UPDATE Movies "
        "SET available = 1 "
        "WHERE id = ?;";

    if(sqlite3_prepare_v2(
            database.getDB(),
            sql,
            -1,
            &stmt,
            nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt,1,movieId);

    bool success =
        sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);

    return success;
}

void MovieManager::addMovie(const Movie& movie)
{
    sqlite3_stmt* stmt;

    const char* sql =
        "INSERT INTO Movies(title,genre,rating,available,rentPrice,buyPrice) "
        "VALUES(?,?,?,?,?,?);";

    if(sqlite3_prepare_v2(
            database.getDB(),
            sql,
            -1,
            &stmt,
            nullptr) != SQLITE_OK)
    {
        return;
    }

    sqlite3_bind_text(stmt,1,
                      movie.getTitle().c_str(),
                      -1,
                      SQLITE_TRANSIENT);

    sqlite3_bind_text(stmt,2,
                      movie.getGenre().c_str(),
                      -1,
                      SQLITE_TRANSIENT);

    sqlite3_bind_double(stmt,3,
                        movie.getRating());

    sqlite3_bind_int(stmt,4,
                     movie.isAvailable());

    sqlite3_bind_int(stmt,5,
                     movie.getRentPrice());

    sqlite3_bind_int(stmt,6,
                     movie.getBuyPrice());

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);
}
bool MovieManager::removeMovie(int movieId)
{
    sqlite3_stmt* stmt;

    const char* sql =
        "DELETE FROM Movies WHERE id=?;";

    if(sqlite3_prepare_v2(
            database.getDB(),
            sql,
            -1,
            &stmt,
            nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt,1,movieId);

    bool success =
        sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);

    return success;
}

std::vector<User> MovieManager::getUsers()
{
    std::vector<User> users;

    sqlite3_stmt* stmt;

    const char* sql =
        "SELECT id, username, password, admin FROM Users;";

    if(sqlite3_prepare_v2(
            database.getDB(),
            sql,
            -1,
            &stmt,
            nullptr) != SQLITE_OK)
    {
        return users;
    }

    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        users.emplace_back(
            sqlite3_column_int(stmt,0),

            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt,1)),

            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt,2)),

            sqlite3_column_int(stmt,3));
    }

    sqlite3_finalize(stmt);

    return users;
}

int MovieManager::totalMovies() const
{
    sqlite3_stmt* stmt;

    int count = 0;

    sqlite3_prepare_v2(
        database.getDB(),
        "SELECT COUNT(*) FROM Movies;",
        -1,
        &stmt,
        nullptr);

    if(sqlite3_step(stmt)==SQLITE_ROW)
        count = sqlite3_column_int(stmt,0);

    sqlite3_finalize(stmt);

    return count;
}

int MovieManager::availableMovies() const
{
    sqlite3_stmt* stmt;

    int count = 0;

    sqlite3_prepare_v2(
        database.getDB(),
        "SELECT COUNT(*) FROM Movies WHERE available = 1;",
        -1,
        &stmt,
        nullptr);

    if(sqlite3_step(stmt) == SQLITE_ROW)
        count = sqlite3_column_int(stmt,0);

    sqlite3_finalize(stmt);

    return count;
}

int MovieManager::rentedMovies() const
{
    sqlite3_stmt* stmt;

    int count = 0;

    sqlite3_prepare_v2(
        database.getDB(),
        "SELECT COUNT(*) FROM Movies WHERE available = 0;",
        -1,
        &stmt,
        nullptr);

    if(sqlite3_step(stmt) == SQLITE_ROW)
        count = sqlite3_column_int(stmt,0);

    sqlite3_finalize(stmt);

    return count;
}

int MovieManager::totalUsers() const
{
    sqlite3_stmt* stmt;

    int count = 0;

    sqlite3_prepare_v2(
        database.getDB(),
        "SELECT COUNT(*) FROM Users;",
        -1,
        &stmt,
        nullptr);

    if(sqlite3_step(stmt) == SQLITE_ROW)
        count = sqlite3_column_int(stmt,0);

    sqlite3_finalize(stmt);

    return count;
}

int MovieManager::getCurrentUserId() const
{
    if(currentUser)
        return currentUser->getId();

    return -1;
}

std::vector<MovieManager::RentalInfo>
MovieManager::getRentalHistory()
{
    std::vector<RentalInfo> history;

    sqlite3_stmt* stmt;

    const char* sql =
        "SELECT Users.username,"
        "Movies.title,"
        "Rentals.rentDate,"
        "Rentals.status "
        "FROM Rentals "
        "JOIN Users ON Rentals.userId=Users.id "
        "JOIN Movies ON Rentals.movieId=Movies.id;";

    if(sqlite3_prepare_v2(
            database.getDB(),
            sql,
            -1,
            &stmt,
            nullptr)!=SQLITE_OK)
        return history;

    while(sqlite3_step(stmt)==SQLITE_ROW)
    {
        RentalInfo r;

        r.username =
            reinterpret_cast<const char*>(
            sqlite3_column_text(stmt,0));

        r.movie =
            reinterpret_cast<const char*>(
            sqlite3_column_text(stmt,1));

        r.rentDate =
            reinterpret_cast<const char*>(
            sqlite3_column_text(stmt,2));

        r.status =
            reinterpret_cast<const char*>(
            sqlite3_column_text(stmt,3));

        history.push_back(r);
    }

    sqlite3_finalize(stmt);

    return history;
}

std::vector<MovieManager::PurchaseInfo>
MovieManager::getPurchases()
{
    std::vector<PurchaseInfo> purchases;

    sqlite3_stmt* stmt;

    const char* sql =
        "SELECT Users.username,"
        "Movies.title,"
        "Purchases.purchaseDate "
        "FROM Purchases "
        "JOIN Users ON Purchases.userId = Users.id "
        "JOIN Movies ON Purchases.movieId = Movies.id;";

    if(sqlite3_prepare_v2(
            database.getDB(),
            sql,
            -1,
            &stmt,
            nullptr) != SQLITE_OK)
    {
        return purchases;
    }

    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        PurchaseInfo p;

        p.username =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt,0));

        p.movie =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt,1));

        p.purchaseDate =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt,2));

        purchases.push_back(p);
    }

    sqlite3_finalize(stmt);

    return purchases;
}

MovieManager::~MovieManager()
{
    database.close();
}