#include "User.h"

User::User()
{
    id = 0;
    username = "";
    password = "";
    admin = false;
}

User::User(
    int id,
    const std::string& username,
    const std::string& password,
    bool admin)
{
    this->id = id;
    this->username = username;
    this->password = password;
    this->admin = admin;
}

int User::getId() const
{
    return id;
}

std::string User::getUsername() const
{
    return username;
}

std::string User::getPassword() const
{
    return password;
}

bool User::isAdmin() const
{
    return admin;
}
bool User::isLoggedIn() const
{
    return loggedIn;
}

void User::setLoggedIn(bool status)
{
    loggedIn = status;
}

void User::setPassword(const std::string& password)
{
    this->password = password;
}