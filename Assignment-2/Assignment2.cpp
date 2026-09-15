#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace chrono;

struct Movie {
    string name;
    double rating;
    int year;
    long long votes;
};

// Reads one complete CSV line
vector<string> parseCSVLine(const string& line) {
    vector<string> fields;
    string field;
    bool insideQuotes = false;

    for (char c : line) {

        if (c == '"') {
            insideQuotes = !insideQuotes;
        }
        else if (c == ',' && !insideQuotes) {
            fields.push_back(field);
            field.clear();
        }
        else {
            field += c;
        }
    }

    fields.push_back(field);

    return fields;
}

// Compares two movies according to user's choice
bool comesBefore(const Movie& a, const Movie& b, int choice) {

    if (choice == 1)
        return a.rating < b.rating;

    if (choice == 2)
        return a.year < b.year;

    // choice == 3
    return a.votes < b.votes;
}

// Quick Sort implementation
void quickSort(vector<Movie>& movies, int low, int high, int choice) {

    while (low < high) {

        int i = low;
        int j = high;

        // Select middle element as pivot
        Movie pivot = movies[low + (high - low) / 2];

        while (i <= j) {

            while (comesBefore(movies[i], pivot, choice))
                i++;

            while (comesBefore(pivot, movies[j], choice))
                j--;

            if (i <= j) {
                swap(movies[i], movies[j]);
                i++;
                j--;
            }
        }

        // Process smaller partition first
        if (j - low < high - i) {

            if (low < j)
                quickSort(movies, low, j, choice);

            low = i;
        }
        else {

            if (i < high)
                quickSort(movies, i, high, choice);

            high = j;
        }
    }
}

int main() {

    // Open CSV file
    ifstream file("movie.csv");

    if (!file.is_open()) {
        cerr << "Error: Could not open movie.csv\n";
        return 1;
    }

    string line;

    // Skip CSV header
    getline(file, line);

    vector<Movie> movies;

    // Read all movie records
    while (getline(file, line)) {

        vector<string> fields = parseCSVLine(line);

        // Our CSV has 4 columns:
        // title, rating, release_year, popularity
        if (fields.size() < 4)
            continue;

        try {

            Movie movie;

            movie.name = fields[0];
            movie.rating = stod(fields[1]);
            movie.year = stoi(fields[2]);
            movie.votes = stoll(fields[3]);

            movies.push_back(movie);
        }
        catch (...) {

            // Skip invalid rows
            continue;
        }
    }

    file.close();

    cout << "Movies loaded: " << movies.size() << "\n\n";

    // Check whether movies were loaded
    if (movies.empty()) {
        cout << "No valid movie records found.\n";
        return 1;
    }

    int choice;

    cout << "Sort movies by:\n";
    cout << "1. IMDb Rating\n";
    cout << "2. Year of Release\n";
    cout << "3. Popularity (Votes)\n";
    cout << "Enter choice: ";

    cin >> choice;

    if (choice < 1 || choice > 3) {
        cout << "Invalid choice.\n";
        return 1;
    }

    // Start timer
    auto start = high_resolution_clock::now();

    // Apply Quick Sort
    quickSort(movies, 0, static_cast<int>(movies.size()) - 1, choice);

    // Stop timer
    auto stop = high_resolution_clock::now();

    auto duration =
        duration_cast<microseconds>(stop - start);

    cout << "\nQuick Sort completed successfully.\n";

    cout << "Sorting time: "
         << duration.count()
         << " microseconds\n";

    // Display first 20 sorted movies
    cout << "\nFirst 20 sorted movies:\n";

    cout << "------------------------------------------------------------\n";

    cout << left
         << setw(30) << "Movie"
         << setw(10) << "Rating"
         << setw(10) << "Year"
         << setw(15) << "Votes"
         << "\n";

    cout << "------------------------------------------------------------\n";

    int limit = min(20, static_cast<int>(movies.size()));

    for (int i = 0; i < limit; i++) {

        cout << left
             << setw(30) << movies[i].name
             << setw(10) << fixed << setprecision(1) << movies[i].rating
             << setw(10) << movies[i].year
             << setw(15) << movies[i].votes
             << "\n";
    }

    return 0;
}
