/***********************************************************************************************
 * Name:        MovieRecommenderDr.cpp
 * Author:      1) Mohammed Al frijie
 *              2) Jessica Alba
 *              3) Pallavi Aggarwal
 * Date:        5/4/2025
 * Description: This driver tests the movie recommender program. It first reads a CSV file
 *              of base Rotten Tomatoes data for movies, including their ratings. Then 
 *              it inserts these entries into a hash table. The drivers shows how different
 *              viewers can be instantiated in the program with their favorite directors and/or
 *              preferred genres and be recommended movies not already in their watchlists.
***********************************************************************************************/
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
    //printHashTable(movieTable);
    
    // Set up a Mom profile with her preferences and watchlist
    Viewer mom("Mom", 38);
    mom.AddPreferredGenre("Romance");
    mom.AddPreferredGenre("Drama");
    mom.AddToWatchlist("The Notebook");
    mom.AddToWatchlist("27 Dresses");

    // Show Mom's details and recommendations
    mom.Print();
    movieTable.RecommendMovies(mom);

    // Set up a Dad profile with his preferences and watchlist
    Viewer dad("Dad", 40);
    dad.AddPreferredGenre("SciFi");
    dad.AddFavoriteDirector("Steven Spielberg");
    dad.AddToWatchlist("Jurassic Park");
    dad.AddToWatchlist("Inception");
    dad.AddToWatchlist("E.T. The Extra-Terrestrial");
    
    // Show Dad's details and recommendations
    dad.Print();
    movieTable.RecommendMovies(dad);

    // Set up a child's profile with preferences and watchlist
    Viewer daughter("Cindy", 8);
    daughter.AddPreferredGenre("Kids&Family");
    daughter.AddToWatchlist("Finding Nemo");
    daughter.AddToWatchlist("Toy Story 3");
    daughter.AddToWatchlist("Frozen");
    
    // Show Cindy's details and recommendations
    daughter.Print();
    movieTable.RecommendMovies(daughter);
    
    // Set up a teenage son's viewer with preferences and watchlist
    Viewer teenageSon("Dan", 15);
    teenageSon.AddPreferredGenre("Action");
    teenageSon.AddPreferredGenre("Comedy");
    teenageSon.AddFavoriteDirector("Joss Whedon");
    teenageSon.AddToWatchlist("Avengers: Infinity War");
    teenageSon.AddToWatchlist("The Hunger Games: Catching Fire");
    
    // Show Dan's details and recommendations
    teenageSon.Print();
    movieTable.RecommendMovies(teenageSon);

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
            cout << "Inserted movie: " << movie.GetTitle() << endl;
        }
        catch (const exception&) {
            cerr << "Error: Could not parse the line - " << line << endl;
            continue;
        }
    }

    cout << "All movies have been successfully loaded into the hash table!" << endl;
    cout << "The movie hash table has " << movieTable.GetNumItems() << " items stored." << endl;
    cout << "*******************************************************" << endl;
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