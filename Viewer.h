/**
 * Viewer.h
 * The Viewer class represents a person who watches content (e.g., movies, TV shows)
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
    // Function: Gets the name of a Viewer object.
    // Pre:  Viewer has been initialized.
    // Post: Function value = name of the Viewer.

    int GetViewerAge() const;
    // Function: Gets the age of a Viewer object.
    // Pre:  Viewer has been initialized.
    // Post: Function value = age of the Viewer.

    vector<string> GetPreferredGenres() const;
    // Function: Gets the preferred genres of a Viewer object.
    // Pre:  Viewer has been initialized.
    // Post: Function value = preferred genres of the Viewer.

    vector<string> GetFavoriteDirectors() const;
    // Function: Gets the favorite directors of a Viewer object.
    // Pre:  Viewer has been initialized.
    // Post: Function value = favorite directors of the Viewer.

    vector<string> GetWatchlist() const;
    // Function: Gets the watchlist a Viewer object.
    // Pre:  Viewer has been initialized.
    // Post: Function value = watchlist of the Viewer.

    //Setters
    void AddPreferredGenre(const string& genre);
    // Function: Adds a genre to a Viewer objects preferredGenres.
    // Pre:  Viewer has been initialized.
    // Post: Genre is added to the Viewer's preferredGenres.

    void AddFavoriteDirector(const string& director);
    // Function: Adds a director to a Viewer objects favoriteDirectors.
    // Pre:  Viewer has been initialized.
    // Post: Director is added to the Viewer's favoriteDirectors.

    void AddToWatchlist(const string& title);
    // Function: Adds a movie title to a Viewer objects watchlist.
    // Pre:  Viewer has been initialized.
    // Post: Movie title is added to the Viewer's watchlist.

    //Overload operators and output
    bool operator==(const Viewer& rhs) const;
    // Function: Checks if two Viewer objects are equal
    // Pre:  Both Viewer objects have been initialized.
    // Post: Returns true if name and age attributes of the Viewer objects are the same.
    //       Otherwise, returns false.

    void Print() const;
    // Function: Prints the attributes of a Viewer object.
    // Pre:  Viewer has been initialized.
    // Post: The attributes of a Viewer object are displayed.

private:
    string name;    // Name of the viewer
    int age;        // Age of the viewer
    vector<string> preferredGenres;     // A list of genres the viewer prefers to watch
    vector<string> favoriteDirectors;   // A list of the viewers favorite directors
    vector<string> watchlist;           // A list of movies the viewer has seen
};

// Constructor implementations
Viewer::Viewer(string viewerName) {
    name = viewerName;
    age = -1;
}

Viewer::Viewer(string viewerName, int viewerAge) {
    name = viewerName;
    age = viewerAge;
}

string Viewer::GetViewerName() const {
    // Function: Gets the name of a Viewer object.
    // Pre:  Viewer has been initialized.
    // Post: Function value = name of the Viewer.
    return name;
}

int Viewer::GetViewerAge() const {
    // Function: Gets the age of a Viewer object.
    // Pre:  Viewer has been initialized.
    // Post: Function value = age of the Viewer.
    return age;
}

void Viewer::AddPreferredGenre(const string& genre) {
    // Function: Adds a genre to a Viewer objects preferredGenres.
    // Pre:  Viewer has been initialized.
    // Post: Genre is added to the Viewer's preferredGenres.
    preferredGenres.push_back(genre);
}

void Viewer::AddFavoriteDirector(const string& director) {
    // Function: Adds a director to a Viewer objects favoriteDirectors.
    // Pre:  Viewer has been initialized.
    // Post: Director is added to the Viewer's favoriteDirectors.
    favoriteDirectors.push_back(director);
}

void Viewer::AddToWatchlist(const string& title) {
    // Function: Adds a movie title to a Viewer objects watchlist.
    // Pre:  Viewer has been initialized.
    // Post: Movie title is added to the Viewer's watchlist.
    watchlist.push_back(title);
}

vector<string> Viewer::GetPreferredGenres() const {
    // Function: Gets the preferred genres of a Viewer object.
    // Pre:  Viewer has been initialized.
    // Post: Function value = preferred genres of the Viewer.
    return preferredGenres;
}

vector<string> Viewer::GetFavoriteDirectors() const {
    // Function: Gets the favorite directors of a Viewer object.
    // Pre:  Viewer has been initialized.
    // Post: Function value = favorite directors of the Viewer.
    return favoriteDirectors;
}

vector<string> Viewer::GetWatchlist() const {
    // Function: Gets the watchlist a Viewer object.
    // Pre:  Viewer has been initialized.
    // Post: Function value = watchlist of the Viewer.
    return watchlist;
}

bool Viewer::operator==(const Viewer& rhs) const {
    // Function: Checks if two Viewer objects are equal
    // Pre:  Both Viewer objects have been initialized.
    // Post: Returns true if name and age attributes of the Viewer objects are the same.
    //       Otherwise, returns false.
    return name == rhs.name && age == rhs.age;
}

void Viewer::Print() const {
    // Function: Prints the attributes of a Viewer object.
    // Pre:  Viewer has been initialized.
    // Post: The attributes of a Viewer object are displayed.
    cout << "\nViewer Name: " << name << endl;
    cout << "Viewer Age: " << age << endl;
    cout << "Preferred Genres: ";
    for (size_t i = 0; i < preferredGenres.size(); i++) {
        cout << preferredGenres[i];
        if (i != preferredGenres.size() - 1)    // ensures no trailing comma
            cout << ", ";
    }
    cout << "\nFavorite Directors: ";
    for (size_t i = 0; i < favoriteDirectors.size(); i++) {
        cout << favoriteDirectors[i];
        if (i != favoriteDirectors.size() - 1)  // ensures no trailing comma
            cout << ", ";
    }
    cout << "\nViewer's Watchlist: ";
    for (size_t i = 0; i < watchlist.size(); i++) {
        cout << watchlist[i];
        if (i != watchlist.size() - 1)  // ensures no trailing comma
            cout << ", ";
    }
    cout << endl;
}

#endif