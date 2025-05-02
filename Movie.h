/**
 * Movie.h
 * The Movie class defines ...
 **/

#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <vector>

using namespace std;

class Movie {
    public:
    	// Functions go here..
    
    	// Default class constructor
    
    	// Parametrized class constructor

    private:
    	string title;     // Name of the movie
    	int year;	      // Release year
    	string genre;     // Movie category (Action, Comedy, Drama, etc.)
    	string director;  // Name of movie’s director
    	string cast;  	  // Name of the primary actor/actress appearing in the movie
    	int runtime;      // The runtime length of the movie, in minutes
    	vector<double> viewerRatings;  // Store each viewer’s ratings for the movie
};
#endif
