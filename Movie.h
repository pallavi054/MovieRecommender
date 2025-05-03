/**
 * Movie.h
 * The Movie class represents movies and their attributes, including
 * title, year, genre, director, lead cast member, runtime, and Rotten
 * Tomatoes rating. The user has functions available like storing new 
 * movies, storing viewer-specific ratings, and printing movie details.
 **/

#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Movie {
    public:
        // Default class constructor
        Movie();

        // Parameterized class constructor
        Movie(string movie_title, int movie_year, string movie_genre, 
              string movie_director, string movie_cast, 
              int movie_runtime, double movie_rating);
        
        /* Getters */
        string GetTitle() const;
        // Function: Gets the title of a Movie object.
		// Pre:  Movie has been initialized.
		// Post: Function value = title of the Movie.
        
        int GetYear() const;
        // Function: Gets the release year of a Movie object.
		// Pre:  Movie has been initialized.
		// Post: Function value = year of the Movie.
        
        string GetGenre() const;
        // Function: Gets the genre of a Movie object.
		// Pre:  Movie has been initialized.
		// Post: Function value = genre of the Movie.
        
        string GetDirector() const;
        // Function: Gets the director of a Movie object.
		// Pre:  Movie has been initialized.
		// Post: Function value = director of the Movie.
        
        string GetCast() const;
        // Function: Gets the lead cast member of a Movie object.
		// Pre:  Movie has been initialized.
		// Post: Function value = cast member of the Movie.
        
        int GetRuntime() const;
        // Function: Gets the runtime (in minutes) of a Movie object.
		// Pre:  Movie has been initialized.
		// Post: Function value = runtime of the Movie.
        
        double GetRating() const;
        // Function: Gets the rating of a Movie object.
		// Pre:  Movie has been initialized.
		// Post: Function value = rating of the Movie.
        
        /* Setters */
        void UpdateMovie(string movie_title, int movie_year, 
                         string movie_genre, string movie_director,
                         string movie_cast, int movie_runtime,
                         double movie_rating, vector<double> viewer_ratings);
        // Function: Updates the attributes of a Movie object.
        // Pre:  Movie has been initialized.
        // Post: Movie attributes are updated with the provided values.
        
        void AddRating(double user_rating);
        // Function: Adds a viewer-provided rating to a Movie object.
        // Pre:  Movie has been initialized.
        // Post: Viewer's rating is added to the Movie's rating.
        
        /* Overloaded equality operator */
        bool operator==(const Movie& rhs) const;
        // Function: Checks if two Movie objects are equal
        // Pre:  Both Movie objects have been initialized.
        // Post: Returns true if all attributes of the Movie objects are the same.
        //       Otherwise, returns false.
        
        /* Print */
        void Print() const;
        // Function: Prints the attributes of a Movie object.
        // Pre:  Movie has been initialized.
        // Post: The attributes of a Movie object are displayed.
       
    private:
    	string title;     // Name of the movie
    	int year;	      // Release year
    	string genre;     // Movie category (Action, Comedy, Drama, etc.)
    	string director;  // Name of the movie's director
    	string cast;  	  // Name of the primary actor/actress appearing in the movie
    	int runtime;      // The runtime length of the movie, in minutes
        double rating;    // The pre-populated Rotten Tomatoes rating of the movie
    	vector<double> viewerRatings;  // Store each viewer's ratings for the movie
};

// Default class constructor
Movie::Movie() {
    title = "";
    year = 0;
    genre = "";
    director = "";
    cast = "";
    runtime = 0;
    rating = 0.0;
}

Movie::Movie(string movie_title, int movie_year, string movie_genre, 
             string movie_director, string movie_cast, 
             int movie_runtime, double movie_rating) {
    title = movie_title;
    year = movie_year;
    genre = movie_genre;
    director = movie_director;
    cast = movie_cast;
    runtime = movie_runtime;
    rating = movie_rating;
}

string Movie::GetTitle() const {
// Function: Gets the title of a Movie object.
// Pre:  Movie has been initialized.
// Post: Function value = title of the Movie.
    return title;
}

int Movie::GetYear() const {
// Function: Gets the release year of a Movie object.
// Pre:  Movie has been initialized.
// Post: Function value = year of the Movie.
    return year;
}

string Movie::GetGenre() const {
// Function: Gets the genre of a Movie object.
// Pre:  Movie has been initialized.
// Post: Function value = genre of the Movie.
    return genre;
}

string Movie::GetDirector() const {
// Function: Gets the director of a Movie object.
// Pre:  Movie has been initialized.
// Post: Function value = director of the Movie.
    return director;
}

string Movie::GetCast() const {
// Function: Gets the lead cast member of a Movie object.
// Pre:  Movie has been initialized.
// Post: Function value = cast member of the Movie.
    return cast;
}

int Movie::GetRuntime() const {
// Function: Gets the runtime (in minutes) of a Movie object.
// Pre:  Movie has been initialized.
// Post: Function value = runtime of the Movie.
    return runtime;
}

double Movie::GetRating() const {
// Function: Gets the rating of a Movie object.
// Pre:  Movie has been initialized.
// Post: Function value = rating of the Movie.
    return rating;
}

void Movie::UpdateMovie( string movie_title = "", int movie_year = -1, 
                         string movie_genre = "", string movie_director = "",
                         string movie_cast = "", int movie_runtime = -1,
                         double movie_rating = -1.0, 
                         vector<double> viewer_ratings = {}) {
// Function: Updates the attributes of a Movie object.
// Pre:  Movie has been initialized.
// Post: Movie attributes are updated with the provided values.

    // Updates any parameters that are not default values
    if (!movie_title.empty()) 
        title = movie_title;
    if (movie_year != -1)
        year = movie_year;
    if (!movie_genre.empty()) 
        genre = movie_genre;
    if (!movie_director.empty()) 
        director = movie_director;
    if (!movie_cast.empty()) 
        cast = movie_cast;
    if (movie_runtime != -1) 
        runtime = movie_runtime;
    if (movie_rating != -1.0) 
        rating = movie_rating;
    if (!viewer_ratings.empty()) 
        viewerRatings = viewer_ratings;
}

void Movie::AddRating(double user_rating) {
// Function: Adds a viewer-provided rating to a Movie object.
// Pre:  Movie has been initialized.
// Post: Viewer's rating is added to the Movie's rating.
    viewerRatings.push_back(user_rating);  // add new rating to the vector
    double total = 0;
    for (double r: viewerRatings)
        total += r;
    rating = total / viewerRatings.size();  // recalculate average rating
}

bool Movie::operator==(const Movie& rhs) const {
// Function: Checks if two Movie objects are equal
// Pre:  Both Movie objects have been initialized.
// Post: Returns true if all attributes of the Movie objects are the same.
//       Otherwise, returns false.
    return (title == rhs.title && 
            year == rhs.year && 
            genre == rhs.genre && 
            director == rhs.director && 
            cast == rhs.cast && 
            runtime == rhs.runtime);
}
        
void Movie::Print() const {
// Function: Prints the attributes of a Movie object.
// Pre:  Movie has been initialized.
// Post: The attributes of a Movie object are displayed.
    cout << "Movie Title: " << title << endl;
    cout << "Release Year: " << year << endl;
    cout << "Genre: " << genre << endl;
    cout << "Director: " << director << endl;
    cout << "Cast: " << cast << endl;
    cout << "Runtime (in minutes): " << runtime << endl;
    cout << "Rating: " << rating << endl;
    cout << endl;
}
#endif
