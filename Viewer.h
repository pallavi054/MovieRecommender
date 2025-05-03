/**
 * Viewer.h
 * The Viever class represents a person who watches content (e.g., movies, TV shows)
 * and has preferences for genres. This class provides functionality to manage the viewer's name,
 * age, and list of preferred genres.
 **/

#ifndef VIEWER_H
#define VIEWER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Viewer {
    public:
        // Constructors
        Viewer(string viewerName);
        Viewer(string viewerName, int viewerAge);

        //Getters
        string GetViewerName() const;
        int GetViewerAge() const;
        vector<string> GetPreferredGenres() const;
        vector<string> GetFavoriteDirectors() const;
	vector<string> GetWatchlist() const;

        //Setters
        void AddPreferredGenre(const string& genre);
        void AddFavoriteDirector(const string& director);
        void AddToWatchlist(const string& title);

        //Overload operators and output
        bool operator==(const Viewer& rhs) const;
        void Print() const;

    private:
        string name;    // Name of the viewer
        int age;    // Age of the viewer
        vector<string> preferredGenres;    // A list of genres the viewer prefers to watch
        vector<string> favoriteDirectors;   // A list of the viewers favorite directors
        vector<string> watchlist;           // A list of movies the viewer has seen
};

Viewer::Viewer(string viewerName) {
	name = viewerName;
    age = -1;
}

Viewer::Viewer(string viewerName, int viewerAge) {
    name = viewerName;
    age = viewerAge;
}

string Viewer::GetViewerName() const {
	return name;
}

int Viewer::GetViewerAge() const {
	return age;
}

void Viewer::AddPreferredGenre(const string& genre) {
    preferredGenres.push_back(genre);
}

vector<string> Viewer::GetPreferredGenres() const {
    return preferredGenres;
}

void Viewer::AddFavoriteDirector(const string& director) {
    favoriteDirectors.push_back(director);
}

void Viewer::AddToWatchlist(const string& title) {
    watchlist.push_back(title);
}

vector<string> Viewer::GetFavoriteDirectors() const {
    return favoriteDirectors;
}

vector<string> Viewer::GetWatchlist() const {
    return watchlist;
}

bool Viewer::operator==(const Viewer& rhs) const{
    return name == rhs.name && age == rhs.age;
}

void Viewer::Print() const {
    cout << "Viewer Name: " << name << endl;
    cout << "Viewer Age: " << age << endl;
    cout << "Preferred Genres: ";
    for (const string& genre : preferredGenres) {
        cout << genre << ", ";
    }
    cout << "\nFavorite Directors: ";
    for (const string& director : favoriteDirectors) {
        cout << director << ", ";
    }
    cout << "\nViewer's Watchlist: ";
    for (const auto& title : watchlist) {
        cout << title << ", ";
    }
    cout << endl;
}

#endif


