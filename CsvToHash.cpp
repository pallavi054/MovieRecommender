#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Movie {
    int year;
    string genre;
    string director;
    string cast;
    int runtime;
    double rating;
};

unordered_map<string, Movie> readCSVToHashTable(const string& filename) {
    unordered_map<string, Movie> movieTable;
    ifstream file(filename);
    string line;

    getline(file, line);

    while (getline(file, line)); {
        stringsteam ss(line);
        string title, temp;
        Movie movie;

        getline(ss, title, ',');
        getline(ss, temp, ','); movie.year = stoi(temp);
        getline(ss, movie.genre, ',');
        getline(ss, movie.director, ',');
        getline(ss, movie.cast, ',');
        getline(ss, temp, ','); movie.runtime = stoi(temp);
        getline(ss, temp, ','); movie.rating = stod(temp);

      movieTable[title] = movie;
  }

  return movieTable;
    
