# 🎬 Movie Rental Management System

A desktop-based **Movie Rental Management System** developed in **C++** using **Dear ImGui** for the graphical user interface and **SQLite** for persistent data storage. The application supports secure user authentication, movie rental and purchase operations, and an administrator dashboard for inventory and user management.


## Overview

This project is a GUI-based extension of my earlier **Movie Rental Management System (CLI)**. The original command-line application established the core object-oriented architecture, while this version enhances it with:

- Dear ImGui-based graphical interface
- SQLite database integration
- Persistent authentication and movie management
- Administrator dashboard
- Improved user experience

**CLI Repository:** https://github.com/SarthakGit14/Movie-Rental-System.git

---

## 🚀 Features

### 👤 User Module
- User Login & Signup
- Browse available movies
- Search movies by title
- View movie details
- Rent movies
- Purchase movies
- Return rented movies

### 🛠️ Admin Module
- Administrator Login
- View registered users
- View rental history
- View purchase history
- Add new movies
- Remove existing movies
- View system statistics
  - Total Movies
  - Available Movies
  - Rented Movies
  - Registered Users

---

## 💻 Technologies Used

- **C++17**
- **Dear ImGui**
- **SQLite3**
- **GLFW**
- **OpenGL**
- **CMake**

---

## 📂 Project Structure

```
MovieGUI/
│
├── backend/
│   ├── Movie.cpp
│   ├── MovieManager.cpp
│   ├── User.cpp
│
├── database/
│   ├── Database.cpp
│   ├── Database.h
│
├── screens/
│   ├── LoginScreen.cpp
│   ├── SignupScreen.cpp
│   ├── DashboardScreen.cpp
│   ├── AdminScreen.cpp
│
├── include/
│   ├── AppData.h
│   ├── AppState.h
│
├── src/
│   └── main.cpp
│
├── imgui/
│
├── CMakeLists.txt
│
└── README.md
```

---

## 🗄️ Database Schema

The application uses **SQLite** with the following tables:

### Users
| Column | Type |
|---------|------|
| id | INTEGER |
| username | TEXT |
| password | TEXT |
| admin | INTEGER |

### Movies
| Column | Type |
|---------|------|
| id | INTEGER |
| title | TEXT |
| genre | TEXT |
| rating | REAL |
| available | INTEGER |
| rentPrice | INTEGER |
| buyPrice | INTEGER |

### Rentals
| Column | Type |
|---------|------|
| id | INTEGER |
| userId | INTEGER |
| movieId | INTEGER |
| rentDate | TEXT |
| returnDate | TEXT |
| status | TEXT |

### Purchases
| Column | Type |
|---------|------|
| id | INTEGER |
| userId | INTEGER |
| movieId | INTEGER |
| purchaseDate | TEXT |

---

## ⚙️ Build Instructions

### Clone the Repository

```bash
git clone https://github.com/YOUR_USERNAME/Movie-Rental-System.git
cd Movie-Rental-System
```

### Build

```bash
mkdir build
cd build

cmake ..
make -j4
```

### Run

```bash
./MovieGUI
```

---

## 📸 Screenshots

### Login Screen

_Add screenshot here_

---

### User Dashboard

_Add screenshot here_

---

### Admin Dashboard

_Add screenshot here_

---

## 📌 Future Improvements

- Password hashing
- Advanced movie search and filters
- Movie posters and thumbnails
- Edit movie details
- User profile management
- Transaction reports
- Better UI themes
- Enhanced error handling

---

## 👨‍💻 Author

**Sarthak Sehgal**

- GitHub: https://github.com/SarthakGit14
- LinkedIn: https://www.linkedin.com/in/sarthak-sehgal

---

## 📄 License

This project is intended for educational and learning purposes.
