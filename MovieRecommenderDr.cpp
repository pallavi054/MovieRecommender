/*****************************************************************************************
 * Name:        MovieRecommenderDr.cpp
 * Author:      1) FILL IN
 *              2) FILL IN
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
    string filename = "movieData.csv";
    HashType movieTable;

    readCSVToHashTable(movieTable, filename);

    printHashTable(movieTable);

    // Create a viewer with preferences
    // Complete this...
    
    return 0;
};

void readCSVToHashTable(HashType& movieTable, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error - unable to open the file!" << endl;
        return;
    }

    string line;
    getline(file, line);
    
    cout << "Beginning hash table initialization from CSV..." << endl;
    while (getline(file, line)) {
        stringstream ss(line);
        string title, temp, genre, director, cast;
        int year, runtime;
        double rating;

        try {
            getline(ss, title, ',');
            getline(ss, temp, ','); year = stoi(temp);
            getline(ss, genre, ',');
            getline(ss, director, ',');
            getline(ss, cast, ',');
            getline(ss, temp, ','); runtime = stoi(temp);
            getline(ss, temp, ','); rating = stod(temp);

            Movie movie(title, year, genre, director, cast, runtime, rating);
            movieTable.InsertMovie(movie);
            cout << "Inserted movie " << movie.GetTitle() << endl;
        }
        catch (const exception&) {
            cerr << "Error parsing line: " << line << endl;
            continue;
        }
    }
    cout << "Hash table initialization from CSV complete!" << endl;
}

void printHashTable(const HashType& movieTable) {
    vector<Movie> movieList = movieTable.GetMovies();

    for (const Movie& movie: movieList) {
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
