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
    private:
        string name;
        int age;
        vector<string> preferredGenres;

    public:
        // Constructors
        Viewer(string viewerName);
        Viewer(string viewerName, int viewerAge);

        //Getters
        string GetViewerName() const;
        int GetViewerAge() const;

        void AddPreferredGenre(const string& genre);
        vector<string> GetPreferredGenres() const;

        //Overload operators and output
        bool operator==(const Viewer& rhs) const;
        void Print() const;
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

bool Viewer::operator==(const Viewer& rhs) const{
    return name == rhs.name && age == rhs.age;
}

void Viewer::Print() const {
    cout << "Viewer Name: " << name << endl;
    cout << "Viewer Age: " << age << endl;
    cout << "Preferred Genres: ";
    for (const string& genre : preferredGenres) {
        cout << genre << " ";
    }
    cout << endl;
}

#endif


