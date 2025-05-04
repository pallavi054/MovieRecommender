/**
 * HashType.h
 * The HashType class defines a hash table and a corresponding
 * hash function for storing Movie objects. It includes various operations
 * like insertion, retrieval, deletion, and providing recommendations. The
 * class also features quadratic probing to handle collisions, sorting
 * recommendations based on rating, and checking viewer preferences.
 **/

#ifndef HASHTYPE_H
#define HASHTYPE_H

#include <iostream>
#include <vector>
#include "Movie.h"
#include "Viewer.h"

using namespace std;

const int MAX_ITEMS = 70000;  // Maximum items in the hash table
const int HASH_FACTOR = 31;   // Prime constant for hash function

class HashType {
public:
    // Class constructor
    HashType();

    void MakeEmpty();
    // Function: Returns the hash table to the empty state.
    // Post:  Hash table is empty.

    bool IsFull() const;
    // Function:  Determines whether hash table is full.
    // Pre:  Hash table has been initialized.
    // Post: Function value = (hash table is full)

    int GetNumItems() const;
    // Function: Determines the number of elements in the hash table.
    // Pre:  Hash table has been initialized.
    // Post: Function value = number of elements in the hash table

    vector<Movie> GetMovies() const;
    // Function: Gets all Movie objects stored in the hash table.
    // Pre: Hash table has been initialized.
    // Post: Returns a vector containing all stored Movie objects.

    /* This is the hash function for this class */
    int Hash(string movie_title, int movie_year, string movie_genre) const;
    // Function: Computes a hash value for a Movie based on its title, year, and genre.
    // Pre:  Hash table has been initialized.
    // Post: Returns an int representing the hash value of the Movie object.

    void InsertMovie(const Movie& movie);
    // Function: Adds Movie to hash table and uses a quadratic probing technique to
    //           resolve collisions.
    // Pre:  Hash table has been initialized.
    //       Hash table is not full.
    // Post: Movie object is in hash table.

    void RetrieveMovie(const Movie& searchMovie, bool& found, Movie& retrievedMovie);
    // Function: Retrieves hash table element whose key matches searchMovie's key (if
    //           present).
    // Pre:  Hash table has been initialized.
    //       Key member of retrievedMovie is initialized.
    // Post: If there is a movie retrievedMovie whose value matches
    //       searchMovie's value, then found = true and searchMovie contains 
    //       the contents of retrievedMovie if it is found.
    // 	     otherwise found = false and searchMovie is returned unchanged.
    //       Hash table is unchanged.

    void DeleteMovie(Movie movie);
    // Function: Deletes the element whose key matches movie's key.
    // Pre:  Hash table has been initialized.
    //       Key member of movie is initialized.
    //       One and only one element in hash table has a key matching movie's key.
    // Post: No element in hash table has a key matching movie's key.

    void RecommendMovies(const Viewer& viewer) const;
    // Function: Gives personalized movie recommendations for a Viewer.
    // Pre:   Hash table has been initialized.
    //        Viewer preferences are available (favorite directors and/or preferred genres).
    // Post:  Display a list of recommended movies based on the Viewer's 
    //        preferred genres, favorite directors, and watchlist.

    void SortRecommendations(vector<Movie>& recommendedList) const;
    // Function: Sorts a list of recommended movies by rating (highest to lowest).
    // Pre:  The recommended list contains unsorted Movie objects.
    // Post: Movies in the list are now ordered from highest to lowest rating.

    bool IsPreferredGenre(const Viewer& viewer, const string& movie_genre) const;
    // Function: Checks if a given movie genre is one of Viewer's preferred genres.
    // Pre:  Viewer object has been initialized.
    // Post: Returns true if the genre is in the Viewer's preferred genres.
    //       Otherwise, returns false.

    bool IsFavoriteDirector(const Viewer& viewer, const string& movie_director) const;
    // Function: Checks if a given director is one of Viewer's favorite directors.
    // Pre:  Viewer object has been initialized.
    // Post: Returns true if the director is in the Viewer's favorite directors.
    //       Otherwise, returns false.

    bool IsMovieWatched(const Viewer& viewer, const string& movie_title) const;
    // Function: Checks if a Viewer has already seen a given movie.
    // Pre:  Viewer object has been initialized.
    // Post: Returns true if the movie appears in the Viewer's watchlist.
    //       Otherwise, returns false.

private:
    int size;      // size of the hash table
    int numItems;  // number of items in the hash table
    int factor;    // the value used for the hash function
    string emptyItem = "";  // the empty string 
    unsigned long int numCollisions;  // number of collisions encountered
    vector<Movie> movies;   // vector of Movies in the hash table
    vector<bool> occupied;  // tracks occupied slots of the hash table
};

// Class constructor
HashType::HashType() {
    size = MAX_ITEMS;
    numItems = 0;
    factor = HASH_FACTOR;
    numCollisions = 0;
    movies.resize(size, Movie());
    occupied.resize(size, false);
}

void HashType::MakeEmpty() {
    // Function: Returns the hash table to the empty state.
    // Post:  Hash table is empty.
    numItems = 0;  // set number of hash table items to 0
    // Make slots in the hash table empty
    for (int i = 0; i < size; i++) {
        movies[i] = Movie();
        occupied[i] = false;
    }
}

bool HashType::IsFull() const {
    // Function:  Determines whether hash table is full.
    // Pre:  Hash table has been initialized.
    // Post: Function value = (hash table is full)
    return (numItems == size);
}

int HashType::GetNumItems() const {
    // Function: Determines the number of elements in the hash table.
    // Pre:  Hash table has been initialized.
    // Post: Function value = number of elements in the hash table
    return numItems;
}

vector<Movie> HashType::GetMovies() const {
    // Function: Gets all Movie objects stored in the hash table.
    // Pre: Hash table has been initialized.
    // Post: Returns a vector containing all stored Movie objects.
    vector<Movie> movieList;

    // Loop over the hash table and add occupied slots to the movieList vector
    for (int i = 0; i < size; i++) {
        if (occupied[i])
            movieList.push_back(movies[i]);
    }
    return movieList;
}

/* This is the hash function for this class */
int HashType::Hash(string movie_title, int movie_year, string movie_genre) const {
    // Function: Computes a hash value for a Movie based on its title, year, and genre.
    // Pre:  Hash table has been initialized.
    // Post: Returns an int representing the hash value of the Movie object.
    int hash = 0;  // initialize hash value

    // Create a key using title, year, and genre of the movie
    string key = movie_title + to_string(movie_year) + movie_genre;
    for (char c : key)
        hash = (hash * factor + c) % size;  // apply hashing formula using constant factor

    return abs(hash % size);
}

void HashType::InsertMovie(const Movie& movie) {
    // Function: Adds Movie to hash table and uses a quadratic probing technique to
    //           resolve collisions.
    // Pre:  Hash table has been initialized.
    //       Hash table is not full.
    // Post: Movie object is in hash table.
    int index = Hash(movie.GetTitle(), movie.GetYear(), movie.GetGenre());

    int rehash_count = 1;     // initialize a rehash counter
    int operation_count = 1;  // to flip between + and -

    while (occupied[index]) {
        numCollisions++;

        // add rehash_count squared
        if (operation_count % 2 == 1) {
            index = (index + (rehash_count * rehash_count)) % size;
            operation_count++;
        }
        // subtract rehash_count squared
        else {
            index = (index - (rehash_count * rehash_count)) % size;
            // Fix index if it is negative
            if (index < 0)
                index = (index + size) % size;

            operation_count++;
            rehash_count++;  // increment rehash counter every two runs (+ / -)
        }
    }
    movies[index] = movie;
    occupied[index] = true;
    numItems++;
}

// Retrieve Movie using Quadratic Probing
void HashType::RetrieveMovie(const Movie& searchMovie, bool& found, Movie& retrievedMovie) {
    // Function: Retrieves hash table element whose key matches searchMovie's key (if
    //           present).
    // Pre:  Hash table has been initialized.
    //       Key member of retrievedMovie is initialized.
    // Post: If there is a movie retrievedMovie whose value matches
    //       searchMovie's value, then found = true and searchMovie contains 
    //       the contents of retrievedMovie if it is found.
    // 	     otherwise found = false and searchMovie is returned unchanged.
    //       Hash table is unchanged.
    int index = Hash(searchMovie.GetTitle(), searchMovie.GetYear(), searchMovie.GetGenre());

    found = false;
    int rehash_count = 1;  // initialize a rehash counter
    int operation_count = 1;  // to flip between + and -

    while (occupied[index]) {
        if (movies[index].GetTitle() == searchMovie.GetTitle() &&
            movies[index].GetYear() == searchMovie.GetYear() &&
            movies[index].GetGenre() == searchMovie.GetGenre()) {
            found = true;
            retrievedMovie = movies[index];  // movie is found
            return;
        }

        // add rehash_count squared
        if (operation_count % 2 == 1) {
            index = (index + (rehash_count * rehash_count)) % size;
            operation_count++;
        }
        // subtract rehash_count squared
        else {
            index = (index - (rehash_count * rehash_count)) % size;
            // Fix index if it is negative
            if (index < 0)
                index = (index + size) % size;

            operation_count++;
            rehash_count++;  // increment rehash counter every two runs (+ / -)
        }
    }

    // If movie is not found, return default empty Movie object
    retrievedMovie = Movie();
}

void HashType::DeleteMovie(Movie movie) {
    // Function: Deletes the element whose key matches movie's key.
    // Pre:  Hash table has been initialized.
    //       Key member of movie is initialized.
    //       One and only one element in hash table has a key matching movie's key.
    // Post: No element in hash table has a key matching movie's key.
    int index = Hash(movie.GetTitle(), movie.GetYear(), movie.GetGenre());
    int rehash_count = 1;     // initialize a rehash counter
    int operation_count = 1;  // to flip between + and -

    while (occupied[index]) {
        if (movies[index].GetTitle() == movie.GetTitle() &&
            movies[index].GetYear() == movie.GetYear() &&
            movies[index].GetGenre() == movie.GetGenre()) {
            // clear the hash table slot if movie is found
            movies[index] = Movie();
            occupied[index] = false;
            numItems--;
            return;
        }
        // add rehash_count squared
        if (operation_count % 2 == 1) {
            index = (index + (rehash_count * rehash_count)) % size;
            operation_count++;
        }
        // subtract rehash_count squared
        else {
            index = (index - (rehash_count * rehash_count)) % size;
            // Fix index if it is negative
            if (index < 0)
                index = (index + size) % size;

            operation_count++;
            rehash_count++;  // increment rehash counter every two runs (+ / -)
        }
    }
    cout << "Movie to delete not found." << endl;
}

void HashType::RecommendMovies(const Viewer& viewer) const {
    // Function: Gives personalized movie recommendations for a Viewer.
    // Pre:   Hash table has been initialized.
    //        Viewer preferences are available (favorite directors and/or preferred genres).
    // Post:  Display a list of recommended movies based on the Viewer's 
    //        preferred genres, favorite directors, and watchlist.

    vector<Movie> recommended;          // vector of recommended movies
    vector<Movie> directorSuggested;    // movies recommended based on favorite director(s)
    vector<Movie> genreSuggested;       // movies recommended based on preferred genre(s)
    vector<string> distinctGenres;      // tracks distinct genres accounted for in recs
    vector<string> favoriteDirectors = viewer.GetFavoriteDirectors();

    cout << "\nFetching Movie Recommendations for " << viewer.GetViewerName() << "..." << endl;

    // Loop over movies in the hash table
    for (int i = 0; i < size; i++) {
        if (occupied[i]) {  // checks for non-empty slots
            bool MatchDirector = IsFavoriteDirector(viewer, movies[i].GetDirector());  // match on director
            bool MatchGenre = IsPreferredGenre(viewer, movies[i].GetGenre());  // match on genre
            bool IsUnwatched = !IsMovieWatched(viewer, movies[i].GetTitle());  // movie is not already watched
            bool IsHighlyRated = movies[i].GetRating() >= 7.5;  // movie is highly rated

            if (IsUnwatched) {  // movies must be unwatched to be recommendations
                // This loop handles director suggestions
                if (MatchDirector)
                    directorSuggested.push_back(movies[i]);  // note: directorSuggested movies need not be highly rated
                // This loop handles highly-rated genre suggestions
                else if (MatchGenre && IsHighlyRated) {
                    bool genreIncluded = false;  // tracks whether this a given genre has been accounted for

                    for (const string& currentGenre : distinctGenres) {
                        if (currentGenre == movies[i].GetGenre()) {
                            genreIncluded = true;
                            break;
                        }
                    }

                    if (!genreIncluded) {
                        genreSuggested.push_back(movies[i]);  // Add the movie as a genre suggestion
                        distinctGenres.push_back(movies[i].GetGenre());  // Add the genre as accounted for
                    }
                }
            }
        }
    }

    int numDirectors = static_cast<int>(favoriteDirectors.size());  // Number of favorite directors the viewer added

    /* First allocate recommendation spots based on number of favorite directors */
    // Give a max of 2 spots if there is 1 favorite director
    if (numDirectors == 1) {
        for (const Movie& movie : directorSuggested) {
            if (recommended.size() < 2 && movie.GetDirector() == favoriteDirectors[0])
                recommended.push_back(movie);
        }
    }

    // Split the 3 spots if the viewer provides 2 favorite directors
    else if (numDirectors == 2) {
        int count1 = 0;
        int count2 = 0;

        for (const Movie& movie : directorSuggested) {
            if (recommended.size() < 3) {
                if (movie.GetDirector() == favoriteDirectors[0] && count1 < 2) {
                    recommended.push_back(movie);
                    count1++;
                }
                else if (movie.GetDirector() == favoriteDirectors[1] && count2 < 1) {
                    recommended.push_back(movie);
                    count2++;
                }
            }
        }
    }

    // Split the 3 spots if the viewer provides 3+ favorite directors
    else if (numDirectors >= 3) {
        int count1 = 0;
        int count2 = 0;
        int count3 = 0;

        for (const Movie& movie : directorSuggested) {
            if (recommended.size() < 3) {
                if (movie.GetDirector() == favoriteDirectors[0] && count1 < 1) {
                    recommended.push_back(movie);
                    count1++;
                }
                else if (movie.GetDirector() == favoriteDirectors[1] && count2 < 1) {
                    recommended.push_back(movie);
                    count2++;
                }
                else if (movie.GetDirector() == favoriteDirectors[2] && count3 < 1) {
                    recommended.push_back(movie);
                    count3++;
                }
            }
        }
    }

    // Fill any remaining spots with highly-rated genre matches
    for (const Movie& movie : genreSuggested) {
        if (recommended.size() < 3)  // check if recommendation list size is less than 3
            recommended.push_back(movie);  // if so, add a genre match
    }

    // Fill any remaining spots now with unwatched movies from preferred genres
    for (const Movie& movie : movies) {
        // Stop if we hit 3 recommendations
        if (recommended.size() >= 3)
            break;

        // Otherwise enter this loop and check that the movie is unwatched, highly rated,
        // and is of the preferred genre(s)
        if (IsPreferredGenre(viewer, movie.GetGenre()) && !IsMovieWatched(viewer, movie.GetTitle()) &&
            movie.GetRating() >= 7.5) {

            bool movieAlreadyRecommended = false;
            // Check for duplicates before adding to recommended list
            for (const Movie& rhs : recommended) {
                if (movie == rhs) {
                    movieAlreadyRecommended = true;
                    break;
                }
            }
            // Add to recommended list if it's not already included
            if (!movieAlreadyRecommended)
                recommended.push_back(movie);
        }
    }

    // Sort recommendations (highest to lowest rating)
    SortRecommendations(recommended);

    // Get minimum of 3 recs or size of recommended list
    int n = min(3, static_cast<int>(recommended.size()));

    if (n == 0)
        cout << "\nSorry! No movies available match the viewer's preferences." << endl;
    else {
        cout << "\nTop " << n << " Movie Recommendations for " << viewer.GetViewerName() << ": " << endl;
        for (int i = 0; i < n; i++) {
            recommended[i].Print();  // print recommendations
        }
    }
    cout << "*******************************************************" << endl;
}

void HashType::SortRecommendations(vector<Movie>& recommendedList) const {
    // Function: Sorts a list of recommended movies by rating (highest to lowest).
    // Pre:  The recommended list contains unsorted Movie objects.
    // Post: Movies in the list are now ordered from highest to lowest rating.
    int length = static_cast<int>(recommendedList.size());

    // Bubble sort
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (recommendedList[j].GetRating() < recommendedList[j + 1].GetRating())
                swap(recommendedList[j], recommendedList[j + 1]);
        }
    }
}

bool HashType::IsPreferredGenre(const Viewer& viewer, const string& movie_genre) const {
    // Function: Checks if a given movie genre is one of Viewer's preferred genres.
    // Pre:  Viewer object has been initialized.
    // Post: Returns true if the genre is in the Viewer's preferred genres.
    //       Otherwise, returns false.
    for (const string& genre : viewer.GetPreferredGenres()) {
        if (genre == movie_genre)
            return true;
    }
    return false;
}

bool HashType::IsFavoriteDirector(const Viewer& viewer, const string& movie_director) const {
    // Function: Checks if a given director is one of Viewer's favorite directors.
    // Pre:  Viewer object has been initialized.
    // Post: Returns true if the director is in the Viewer's favorite directors.
    //       Otherwise, returns false.
    for (const string& director : viewer.GetFavoriteDirectors()) {
        if (director == movie_director)
            return true;
    }
    return false;
}

bool HashType::IsMovieWatched(const Viewer& viewer, const string& movie_title) const {
    // Function: Checks if a Viewer has already seen a given movie.
    // Pre:  Viewer object has been initialized.
    // Post: Returns true if the movie appears in the Viewer's watchlist.
    //       Otherwise, returns false.
    for (const string& watched : viewer.GetWatchlist()) {
        if (watched == movie_title)
            return true;
    }
    return false;
}
#endif