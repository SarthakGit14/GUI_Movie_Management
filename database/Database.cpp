#include "Database.h"

#include <iostream>

Database::Database()
{
    db = nullptr;
}

Database::~Database()
{
    close();
}

bool Database::open(const std::string& filename)
{
    if(sqlite3_open(filename.c_str(), &db) != SQLITE_OK)
    {
        return false;
    }

   
    execute(
    "CREATE TABLE IF NOT EXISTS Users ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "username TEXT UNIQUE NOT NULL,"
    "password TEXT NOT NULL,"
    "admin INTEGER DEFAULT 0"
    ");"
);

    execute(
    "INSERT OR IGNORE INTO Users(username,password,admin)"
    " VALUES('admin','admin',1);"
);

execute(
    "INSERT OR IGNORE INTO Users(username,password,admin)"
    " VALUES('user','1234',0);"
);

execute(
    "CREATE TABLE IF NOT EXISTS Movies ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "title TEXT NOT NULL,"
    "genre TEXT,"
    "rating REAL,"
    "available INTEGER,"
    "rentPrice INTEGER,"
    "buyPrice INTEGER"
    ");"
);

execute(
"INSERT OR IGNORE INTO Movies(id,title,genre,rating,available,rentPrice,buyPrice)"
" VALUES(1,'Batman','Action',4.8,1,99,499);");

execute(
"INSERT OR IGNORE INTO Movies(id,title,genre,rating,available,rentPrice,buyPrice)"
" VALUES(2,'Avatar','Sci-Fi',4.5,0,119,549);");

execute(
"INSERT OR IGNORE INTO Movies(id,title,genre,rating,available,rentPrice,buyPrice)"
" VALUES(3,'Joker','Crime',4.7,1,89,399);");

execute(
"INSERT OR IGNORE INTO Movies(id,title,genre,rating,available,rentPrice,buyPrice)"
" VALUES(4,'Interstellar','Sci-Fi',4.9,1,129,599);");

execute(
"INSERT OR IGNORE INTO Movies(id,title,genre,rating,available,rentPrice,buyPrice)"
" VALUES(5,'Inception','Thriller',4.8,1,109,499);");

execute(
    "CREATE TABLE IF NOT EXISTS Rentals ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "userId INTEGER,"
    "movieId INTEGER,"
    "rentDate TEXT,"
    "returnDate TEXT,"
    "status TEXT"
    ");"
);

execute(
    "CREATE TABLE IF NOT EXISTS Purchases ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "userId INTEGER,"
    "movieId INTEGER,"
    "purchaseDate TEXT"
    ");"
);

    return true;
}

void Database::close()
{
    if(db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::execute(const std::string& sql)
{
    char* errMsg = nullptr;

    int rc = sqlite3_exec(
        db,
        sql.c_str(),
        nullptr,
        nullptr,
        &errMsg);

    if(rc != SQLITE_OK)
    {
        std::cout << "SQLite Error: "
                  << errMsg
                  << std::endl;

        sqlite3_free(errMsg);

        return false;
    }

    return true;
}

sqlite3* Database::getDB() const
{
    return db;
}