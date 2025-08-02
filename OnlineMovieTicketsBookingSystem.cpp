#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// Movie class
class Movie {
public:
    int id;
    string name;
    string language;
    string releaseDate;
    vector<string> showTimes; // Multiple show times
    string duration;
    vector<int> availableSeatsPerShow; // Seats for each show
    double price;
    string genre;

    // Movie() {
    //     id = 0;
    //     duration = 0;
    //     price = 0.0;
    // }

    void setMovieDetails(int _id) {
        id = _id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter movie name: ";
        getline(cin, name);
        cout << "Enter language: ";
        getline(cin, language);
        cout << "Enter genre: ";
        getline(cin, genre);
        cout << "Enter duration: ";
        cin >> duration;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter release date: ";
        getline(cin, releaseDate);

        int numShows;
        cout << "Enter number of show times: ";
        cin >> numShows;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showTimes.clear();
        availableSeatsPerShow.clear();
        for (int i = 0; i < numShows; ++i) {
            string st;
            int seats;
            cout << "Enter show time " << (i + 1) << ": ";
            getline(cin, st);
            showTimes.push_back(st);
            cout << "Enter available seats for this show: ";
            cin >> seats;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            availableSeatsPerShow.push_back(seats);
        }
        cout << "Enter ticket price: ";
        cin >> price;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void displayMovieDetails() const {
        cout << left << setw(5) << id << setw(25) << name << setw(15) << language
             << setw(15) << genre << setw(10) << duration << setw(15) << releaseDate
             << setw(10) << price << endl;
        cout << "  Show Times:\n";
        for (size_t i = 0; i < showTimes.size(); ++i) {
            cout << "    [" << (i + 1) << "] " << showTimes[i]
                 << " (Seats: " << availableSeatsPerShow[i] << ")\n";
        }
    }
};

// Booking class
class Booking {
public:
    int bookingId;
    string userName;
    int movieId;
    int showIndex; // Index of show time
    vector<int> seatNumbers; // List of seat numbers
    string status; // "Booked" or "Cancelled"

    Booking() : bookingId(0), movieId(0), showIndex(0), status("Booked") {}

    void setBookingDetails(int _bookingId, const string& _userName, int _movieId, int _showIndex, const vector<int>& _seatNumbers) {
        bookingId = _bookingId;
        userName = _userName;
        movieId = _movieId;
        showIndex = _showIndex;
        seatNumbers = _seatNumbers;
        status = "Booked";
    }

    void displayBooking(const Movie& movie) const {
        cout << left << setw(10) << bookingId << setw(20) << userName << setw(25) << movie.name
             << setw(15) << movie.showTimes[showIndex]
             << setw(15);
        for (int sn : seatNumbers) cout << sn << " ";
        cout << setw(12) << status << endl;
    }
};

// Save and load functions for Movie
void saveMovies(const vector<Movie>& movies) {
    ofstream outFile("movies.dat", ios::binary);
    if (!outFile) {
        cerr << "Error opening movies.dat for writing!" << endl;
        return;
    }
    for (const auto& movie : movies) {
        outFile.write(reinterpret_cast<const char*>(&movie.id), sizeof(movie.id));
        size_t len;

        len = movie.name.length();
        outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outFile.write(movie.name.c_str(), len);

        len = movie.language.length();
        outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outFile.write(movie.language.c_str(), len);

        len = movie.genre.length();
        outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outFile.write(movie.genre.c_str(), len);

        outFile.write(reinterpret_cast<const char*>(&movie.duration), sizeof(movie.duration));

        len = movie.releaseDate.length();
        outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outFile.write(movie.releaseDate.c_str(), len);

        len = movie.showTimes.size();
        outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        for (const auto& st : movie.showTimes) {
            size_t stLen = st.length();
            outFile.write(reinterpret_cast<const char*>(&stLen), sizeof(stLen));
            outFile.write(st.c_str(), stLen);
        }

        len = movie.availableSeatsPerShow.size();
        outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        for (const auto& seats : movie.availableSeatsPerShow) {
            outFile.write(reinterpret_cast<const char*>(&seats), sizeof(seats));
        }

        outFile.write(reinterpret_cast<const char*>(&movie.price), sizeof(movie.price));
    }
    outFile.close();
}

vector<Movie> loadMovies() {
    vector<Movie> movies;
    ifstream inFile("movies.dat", ios::binary);
    if (!inFile) return movies;
    while (inFile.peek() != EOF) {
        Movie movie;
        size_t len;
        inFile.read(reinterpret_cast<char*>(&movie.id), sizeof(movie.id));

        inFile.read(reinterpret_cast<char*>(&len), sizeof(len));
        movie.name.resize(len);
        inFile.read(&movie.name[0], len);

        inFile.read(reinterpret_cast<char*>(&len), sizeof(len));
        movie.language.resize(len);
        inFile.read(&movie.language[0], len);

        inFile.read(reinterpret_cast<char*>(&len), sizeof(len));
        movie.genre.resize(len);
        inFile.read(&movie.genre[0], len);

        inFile.read(reinterpret_cast<char*>(&movie.duration), sizeof(movie.duration));

        inFile.read(reinterpret_cast<char*>(&len), sizeof(len));
        movie.releaseDate.resize(len);
        inFile.read(&movie.releaseDate[0], len);

        // Load show times
        inFile.read(reinterpret_cast<char*>(&len), sizeof(len));
        movie.showTimes.resize(len);
        for (size_t i = 0; i < len; ++i) {
            size_t stLen;
            inFile.read(reinterpret_cast<char*>(&stLen), sizeof(stLen));
            movie.showTimes[i].resize(stLen);
            inFile.read(&movie.showTimes[i][0], stLen);
        }

        // Load available seats per show
        inFile.read(reinterpret_cast<char*>(&len), sizeof(len));
        movie.availableSeatsPerShow.resize(len);
        for (size_t i = 0; i < len; ++i) {
            inFile.read(reinterpret_cast<char*>(&movie.availableSeatsPerShow[i]), sizeof(int));
        }

        inFile.read(reinterpret_cast<char*>(&movie.price), sizeof(movie.price));

        if (inFile) movies.push_back(movie);
    }
    inFile.close();
    return movies;
}

// Save and load functions for Booking
void saveBookings(const vector<Booking>& bookings) {
    ofstream outFile("bookings.dat", ios::binary);
    if (!outFile) {
        cerr << "Error opening bookings.dat for writing!" << endl;
        return;
    }
    for (const auto& booking : bookings) {
        outFile.write(reinterpret_cast<const char*>(&booking.bookingId), sizeof(booking.bookingId));
        size_t len;

        len = booking.userName.length();
        outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outFile.write(booking.userName.c_str(), len);

        outFile.write(reinterpret_cast<const char*>(&booking.movieId), sizeof(booking.movieId));
        outFile.write(reinterpret_cast<const char*>(&booking.showIndex), sizeof(booking.showIndex));

        // Save seat numbers
        size_t seatCount = booking.seatNumbers.size();
        outFile.write(reinterpret_cast<const char*>(&seatCount), sizeof(seatCount));
        for (int sn : booking.seatNumbers) {
            outFile.write(reinterpret_cast<const char*>(&sn), sizeof(sn));
        }

        len = booking.status.length();
        outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outFile.write(booking.status.c_str(), len);
    }
    outFile.close();
}

vector<Booking> loadBookings() {
    vector<Booking> bookings;
    ifstream inFile("bookings.dat", ios::binary);
    if (!inFile) return bookings;
    while (inFile.peek() != EOF) {
        Booking booking;
        size_t len;
        inFile.read(reinterpret_cast<char*>(&booking.bookingId), sizeof(booking.bookingId));

        inFile.read(reinterpret_cast<char*>(&len), sizeof(len));
        booking.userName.resize(len);
        inFile.read(&booking.userName[0], len);

        inFile.read(reinterpret_cast<char*>(&booking.movieId), sizeof(booking.movieId));
        inFile.read(reinterpret_cast<char*>(&booking.showIndex), sizeof(booking.showIndex));

        // Load seat numbers
        size_t seatCount;
        inFile.read(reinterpret_cast<char*>(&seatCount), sizeof(seatCount));
        booking.seatNumbers.resize(seatCount);
        for (size_t i = 0; i < seatCount; ++i) {
            inFile.read(reinterpret_cast<char*>(&booking.seatNumbers[i]), sizeof(int));
        }

        inFile.read(reinterpret_cast<char*>(&len), sizeof(len));
        booking.status.resize(len);
        inFile.read(&booking.status[0], len);

        if (inFile) bookings.push_back(booking);
    }
    inFile.close();
    return bookings;
}

// Add a new movie
void addMovie(vector<Movie>& movies) {
    Movie newMovie;
    int newId = movies.empty() ? 1 : movies.back().id + 1;
    newMovie.setMovieDetails(newId);
    movies.push_back(newMovie);
    saveMovies(movies);
    cout << "Movie added successfully!" << endl;
}

// View all movies
void viewMovies(const vector<Movie>& movies) {
    cout << "\n--- Available Movies ---\n";
    if (movies.empty()) {
        cout << "No movies available." << endl;
        return;
    }
    cout << left << setw(5) << "ID" << setw(25) << "Name" << setw(15) << "Language"
         << setw(15) << "Genre" << setw(10) << "Duration" << setw(15) << "Release"
         << setw(10) << "Price" << endl;
    cout << string(100, '-') << endl;
    for (const auto& movie : movies) {
        movie.displayMovieDetails();
    }
}

// Book tickets for a movie
void bookTicket(vector<Movie>& movies, vector<Booking>& bookings) {
    int movieId, numTickets;
    string userName;
    cout << "\n--- Book Tickets ---\n";
    viewMovies(movies);
    if (movies.empty()) return;
    cout << "Enter your name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, userName);
    cout << "Enter movie ID to book: ";
    cin >> movieId;

    Movie* selectedMovie = nullptr;
    for (auto& movie : movies) {
        if (movie.id == movieId) {
            selectedMovie = &movie;
            break;
        }
    }

    if (selectedMovie) {
        // Show available show times
        cout << "Available show times:\n";
        for (size_t i = 0; i < selectedMovie->showTimes.size(); ++i) {
            cout << "  [" << (i + 1) << "] " << selectedMovie->showTimes[i]
                 << " (Seats: " << selectedMovie->availableSeatsPerShow[i] << ")\n";
        }
        int showChoice;
        cout << "Select show time (enter number): ";
        cin >> showChoice;
        if (showChoice < 1 || showChoice > (int)selectedMovie->showTimes.size()) {
            cout << "Invalid show time selection.\n";
            return;
        }
        int showIdx = showChoice - 1;

        cout << "Available seats: " << selectedMovie->availableSeatsPerShow[showIdx] << endl;
        cout << "Enter number of tickets to book: ";
        cin >> numTickets;

        if (numTickets > 0 && numTickets <= selectedMovie->availableSeatsPerShow[showIdx]) {
            // Assign seat numbers (lowest available)
            vector<int> seatNumbers;
            int startSeat = 1 + (selectedMovie->availableSeatsPerShow[showIdx] - numTickets);
            for (int i = 0; i < numTickets; ++i) {
                seatNumbers.push_back(startSeat + i);
            }
            selectedMovie->availableSeatsPerShow[showIdx] -= numTickets;
            saveMovies(movies);
            int newBookingId = bookings.empty() ? 1 : bookings.back().bookingId + 1;
            Booking newBooking;
            newBooking.setBookingDetails(newBookingId, userName, movieId, showIdx, seatNumbers);
            bookings.push_back(newBooking);
            saveBookings(bookings);

            double totalPrice = numTickets * selectedMovie->price;
            cout << "Successfully booked " << numTickets << " tickets for " << selectedMovie->name << endl;
            cout << "Total price: $" << fixed << setprecision(2) << totalPrice << endl;

            // Show booking details in table format
            cout << "\n--- Booking Details ---\n";
            cout << left
                 << setw(10) << "BookingID"
                 << setw(20) << "User Name"
                 << setw(25) << "Movie"
                 << setw(15) << "Show Time"
                 << setw(25) << "Seat No(s)"
                 << setw(15) << "Status" << endl;
            cout << string(97, '-') << endl;
            newBooking.displayBooking(*selectedMovie);
        } else {
            cout << "Invalid number of tickets or not enough seats available." << endl;
        }
    } else {
        cout << "Movie not found." << endl;
    }
}

// View booking status for a user
void viewBookingStatus(const vector<Booking>& bookings, const vector<Movie>& movies) {
    string userName;
    cout << "\nEnter your name to view your bookings: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, userName);

    bool found = false;
    cout << left
         << setw(10) << "BookingID"
         << setw(20) << "User Name"
         << setw(25) << "Movie"
         << setw(15) << "Show Time"
         << setw(15) << "Seat No(s)"
         << setw(12) << "Status" << endl;
    cout << string(97, '-') << endl;
    for (const auto& booking : bookings) {
        if (booking.userName == userName) {
            const Movie* movie = nullptr;
            for (const auto& m : movies) {
                if (m.id == booking.movieId) {
                    movie = &m;
                    break;
                }
            }
            if (movie) {
                booking.displayBooking(*movie);
                found = true;
            }
        }
    }
    if (!found) {
        cout << "No bookings found for user: " << userName << endl;
    }
}

// Cancel a booking
void cancelBooking(vector<Booking>& bookings, vector<Movie>& movies) {
    string userName;
    int bookingId;
    cout << "\nEnter your name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, userName);
    cout << "Enter Booking ID to cancel: ";
    cin >> bookingId;

    bool found = false;
    for (auto& booking : bookings) {
        if (booking.bookingId == bookingId && booking.userName == userName && booking.status == "Booked") {
            // Restore seats for the correct show
            for (auto& movie : movies) {
                if (movie.id == booking.movieId) {
                    movie.availableSeatsPerShow[booking.showIndex] += booking.seatNumbers.size();
                    break;
                }
            }
            booking.status = "Cancelled";
            saveMovies(movies);
            saveBookings(bookings);
            cout << "Booking cancelled successfully.\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "No active booking found with that ID for user: " << userName << endl;
    }
}
// Function to check admin login from file (admin credentials stored in "admin.dat")
bool adminLogin() {
    string inputId, inputPass;
    cout << "\n--- Admin Login Required ---\n";
    cout << "Enter admin ID: ";
    cin >> inputId;
    cout << "Enter password: ";
    cin >> inputPass;

    ifstream adminFile("admin.dat");
    if (!adminFile) {
        cerr << "Admin credentials file not found.\n";
        return false;
    }
    string fileId, filePass;
    bool found = false;
    while (adminFile >> fileId >> filePass) {
        if (inputId == fileId && inputPass == filePass) {
            found = true;
            break;
        }
    }
    adminFile.close();
    if (found) {
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Invalid credentials. Access denied.\n";
        return false;
    }
}

int main() {
    vector<Movie> movies = loadMovies();
    vector<Booking> bookings = loadBookings();
    int choice;

    do {
        cout << "\n--- Movie Ticket Booking System ---\n";
        cout << "1. Add Movie\n";
        cout << "2. View Movies\n";
        cout << "3. Book Ticket\n";
        cout << "4. View Booking Status\n";
        cout << "5. Cancel Booking\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                if (adminLogin()) {
                    addMovie(movies);
                }
                break;
            case 2:
                viewMovies(movies);
                break;
            case 3:
                bookTicket(movies, bookings);
                break;
            case 4:
                viewBookingStatus(bookings, movies);
                break;
            case 5:
                cancelBooking(bookings, movies);
                break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

