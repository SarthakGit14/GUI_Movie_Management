#ifndef USER_H
#define USER_H

#include <string>

class User
{
private:
    int id;
    std::string username;
    std::string password;

    bool admin = false;
    bool loggedIn = false;

public:
    User();

    User(
        int id,
        const std::string& username,
        const std::string& password,
        bool admin = false
    );

    // Getters
    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    bool isAdmin() const;
    bool isLoggedIn() const;

    // Setters
    void setPassword(const std::string& password);
    void setLoggedIn(bool status);
};

#endif