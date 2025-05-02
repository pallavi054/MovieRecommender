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

    while (getline(file, line)) {
        stringstream ss(line);
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
}

void printHashTable(const unordered_map<string, Movie>& table) {
    for (const auto& pair : table) {
        cout << "Title: " << pair.first << endl;
        cout << "Year: " << pair.second.year << endl;
        cout << "Genre: " << pair.second.genre << endl;
        cout << "Director: " << pair.second.director << endl;
        cout << "Cast: " << pair.second.cast << endl;
        cout << "Runtime: " << pair.second.runtime << " minutes" << endl;
        cout << "Rating: " << pair.second.rating << endl;
        cout << "-------------------" << endl;
    }
}

int main() {
    string filename = "movieData.csv";

    unordered_map<string, Movie> movieTable = readCSVToHashTable(filename);

    printHashTable(movieTable);

    return 0;
}

