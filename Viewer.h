/**
 * Viewer.h
 * The Viever class defines ...
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

#endif


