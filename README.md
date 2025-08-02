# Movie Ticket Booking System

This project implements a console-based Movie Ticket Booking System using C++. It provides functionalities for both users to book and manage movie tickets, and for administrators to manage movie listings. The system ensures data persistence by storing information in binary files.

## Features

*   **Movie Management:**
    *   Administrators can add new movies to the system.
    *   Movie details include: **ID**, **Name**, **Language**, **Genre**, **Duration**, **Release Date**, **Multiple Show Times**, **Available Seats per Show**, and **Ticket Price**.
    *   All available movies can be viewed by both users and administrators.
*   **Ticket Booking:**
    *   Users can browse available movies and their show times.
    *   Users can select a movie and a specific show time to book tickets.
    *   The system validates seat availability before confirming a booking.
    *   Calculates and displays the total price for the booked tickets.
*   **Booking Management:**
    *   Users can view their booking status by providing their name.
    *   Users have the option to cancel their active bookings, which restores the seats to availability.
*   **Data Persistence:**
    *   All movie and booking data are securely saved to binary files (`movies.dat` and `bookings.dat`).
    *   This ensures that all data is preserved even after the application is closed and reopened.
*   **Admin Panel:**
    *   A dedicated administrator login (`adminLogin()`) provides access to movie management functionalities.
    *   Admin credentials are read from a separate `admin.dat` file for security.
*   **User-Friendly Interface:**
    *   The system features a clear, menu-driven command-line interface.
    *   Output is formatted using `iomanip` for better readability, including tables and visual separators.
    *   Includes basic input validation and error handling to guide the user.

## System Design

The system is designed with an object-oriented approach, utilizing C++ classes to represent key entities and functions for managing their interactions and data persistence.

### Classes

*   **`Movie` Class:**
    *   **Purpose:** Encapsulates all details related to a movie.
    *   **Attributes:** `id` (unique identifier), `name`, `language`, `releaseDate`, `showTimes` (vector of strings for multiple show times), `duration`, `availableSeatsPerShow` (vector of integers, corresponding to `showTimes`), `price`, `genre`.
    *   **Methods:** `setMovieDetails()` (for admin input), `displayMovieDetails()` (for formatted output).

*   **`Booking` Class:**
    *   **Purpose:** Manages individual ticket booking records.
    *   **Attributes:** `bookingId` (unique identifier), `userName`, `movieId` (links to `Movie` object), `showIndex` (index of the chosen show time from `Movie::showTimes`), `seatNumbers` (vector of integers for booked seats), `status` (e.g., "Booked", "Cancelled").
    *   **Methods:** `setBookingDetails()` (to set booking information), `displayBooking()` (for formatted output).

### Data Storage

Data persistence is achieved through binary file I/O operations:

*   `movies.dat`: Stores serialized `Movie` objects. This file is created/updated when movies are added or seat availability changes.
*   `bookings.dat`: Stores serialized `Booking` objects. This file is created/updated when tickets are booked or cancelled.

### Key Functions

*   `saveMovies(const vector<Movie>& movies)`: Writes the current list of `Movie` objects to `movies.dat`.
*   `loadMovies()`: Reads `Movie` objects from `movies.dat` into memory.
*   `saveBookings(const vector<Booking>& bookings)`: Writes the current list of `Booking` objects to `bookings.dat`.
*   `loadBookings()`: Reads `Booking` objects from `bookings.dat` into memory.
*   `addMovie(vector<Movie>& movies)`: Prompts the admin for movie details and adds a new `Movie` object.
*   `viewMovies(const vector<Movie>& movies)`: Displays a formatted list of all movies and their show times.
*   `bookTicket(vector<Movie>& movies, vector<Booking>& bookings)`: Guides the user through the ticket selection and booking process.
*   `viewBookingStatus(const vector<Booking>& bookings, const vector<Movie>& movies)`: Allows users to check their booking details.
*   `cancelBooking(vector<Booking>& bookings, vector<Movie>& movies)`: Processes booking cancellations and updates seat availability.
*   `adminLogin()`: Handles administrator authentication.

## How to Compile and Run

### Prerequisites

*   A C++ compiler (e.g., GCC/G++).
*   A C++11 compatible environment (or newer, as `std::vector` and `std::string` are used extensively).

### Compilation

1.  Save the provided C++ code as `hello.cpp`.
2.  Open a terminal or command prompt.
3.  Navigate to the directory where you saved `hello.cpp`.
4.  Compile the source code using a C++ compiler. For g++, use the following command:

    ```bash
    g++ hello.cpp -o movie_booking -std=c++11
    ```
    (The `-std=c++11` flag ensures compatibility with C++11 features, which are commonly used.)

### Running the Application

After successful compilation, you can run the application from your terminal:

```bash
./movie_booking
```

### Admin Credentials

To access the admin functionalities, you need to create a file named `admin.dat` in the same directory as your executable. This file should contain the admin username and password, separated by a space.

**Example `admin.dat` content:**

```
admin admin123
```

Replace `admin` and `admin123` with your desired administrator username and password.

## Project Structure

```
.
├── hello.cpp             # Main C++ source code file
├── movies.dat            # Binary file storing movie data (generated on first run/save)
├── bookings.dat          # Binary file storing booking data (generated on first run/save)
└── admin.dat             # Admin credentials file (create manually)
```

## Future Enhancements

This project provides a solid foundation for a movie ticket booking system. Potential future enhancements include:

*   **Database Integration:** Migrate from binary file storage to a more robust database system (e.g., SQLite, MySQL) for better data management and scalability.
*   **Web Interface:** Develop a web-based user interface using frameworks like Flask, Django, or Node.js to provide a more accessible and modern user experience.
*   **Payment Gateway Integration:** Implement secure online payment processing for ticket purchases.
*   **Advanced Reporting:** Add features for generating detailed reports on movie popularity, revenue, and booking trends.
*   **Multi-theater Support:** Extend the system to manage bookings for multiple cinema locations or screens.
*   **User Accounts:** Implement a more comprehensive user authentication and profile management system.
*   **Graphical User Interface (GUI):** Develop a GUI application using libraries like Qt or GTK+ for a richer user experience.


