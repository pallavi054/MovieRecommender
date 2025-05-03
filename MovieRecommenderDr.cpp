/*****************************************************************************************
 * Name:        MovieRecommenderDr.cpp
 * Author:      1) FILL IN
 *              2) Jessica Alba
 *              3) Pallavi Aggarwal
 * Date:        5/3/2025
 * Description: (CHANGE) This driver tests the function allPairsShortestPaths which takes a graph
 *              as an argument. The function uses Floyd’s algorithm to modify the graph
 *              so that it contains the shortest paths between any vertices that are
 *              connected by paths.
 * 
 *              Floyd’s algorithm solves the all-pairs shortest-path problem. That is,
 *              for each vertex v in a graph, the algorithm finds the shortest path from
 *              vertex v to any other vertex w that is reachable from v.
*****************************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include "Movie.h"
#include "Viewer.h"
#include "HashType.h"

using namespace std;

// Function prototypes
void readCSVToHashTable(HashType& movieTable, const string& filename);
void printHashTable(const HashType& movieTable);

int main() {
    // File containing movie data
    string filename = "movieData.csv";

    // Create a hash table to store movies
    HashType movieTable;

    // Load movie data from the CSV file into the hash table
    readCSVToHashTable(movieTable, filename);

    // Display all movies in the hash table
    printHashTable(movieTable);

    // Set up a viewer with preferences and watchlist
    Viewer viewer("Jane Doe", 25);
    viewer.AddPreferredGenre("Adventure");
    viewer.AddPreferredGenre("Sci-Fi");
    viewer.AddFavoriteDirector("Steven Spielberg");
    viewer.AddToWatchlist("Jurassic Park");
    viewer.AddToWatchlist("Inception");
    viewer.AddToWatchlist("E.T. The Extra-Terrestrial");

    // Show the viewer's details
    viewer.Print();

    // This is where additional tests or features can be added

    return 0;
}

/**
 * Reads movie data from a CSV file and inserts it into the hash table.
 * 
 * @param movieTable The hash table where movies will be stored.
 * @param filename The name of the CSV file containing the movie data.
 */
void readCSVToHashTable(HashType& movieTable, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return;
    }

    string line;
    getline(file, line);  // Skip the header line

    cout << "Loading movies from the CSV file into the hash table..." << endl;

    while (getline(file, line)) {
        stringstream ss(line);
        string title, temp, genre, director, cast;
        int year, runtime;
        double rating;

        try {
            // Parse the CSV data
            getline(ss, title, ',');
            getline(ss, temp, ','); year = stoi(temp);
            getline(ss, genre, ',');
            getline(ss, director, ',');
            getline(ss, cast, ',');
            getline(ss, temp, ','); runtime = stoi(temp);
            getline(ss, temp, ','); rating = stod(temp);

            // Create a Movie object and add it to the hash table
            Movie movie(title, year, genre, director, cast, runtime, rating);
            movieTable.InsertMovie(movie);
            cout << "Added movie: " << movie.GetTitle() << endl;
        }
        catch (const exception&) {
            cerr << "Error: Could not parse the line - " << line << endl;
            continue;
        }
    }

    cout << "All movies have been successfully loaded into the hash table!" << endl;
}

/**
 * Prints all the movies currently stored in the hash table.
 * 
 * @param movieTable The hash table containing movies to be printed.
 */
void printHashTable(const HashType& movieTable) {
    vector<Movie> movieList = movieTable.GetMovies();

    for (const Movie& movie : movieList) {
        cout << "Title: " << movie.GetTitle() << endl;
        cout << "Year: " << movie.GetYear() << endl;
        cout << "Genre: " << movie.GetGenre() << endl;
        cout << "Director: " << movie.GetDirector() << endl;
        cout << "Cast: " << movie.GetCast() << endl;
        cout << "Runtime: " << movie.GetRuntime() << " minutes" << endl;
        cout << "Rating: " << movie.GetRating() << endl;
        cout << "-------------------" << endl;
    }
}
