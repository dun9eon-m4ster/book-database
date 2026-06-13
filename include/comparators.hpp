#pragma once

#include "book.hpp"
#include <string_view>

namespace bookdb::comp {

struct LessByAuthor {
    bool operator()(const Book &book, const std::string_view &author) { return book.author < author; }
    bool operator()(const std::string_view &author, const Book &book) { return author < book.author; }
};

struct LessByTitle {
    bool operator()(const Book &book, const std::string &title) { return book.title < title; }
    bool operator()(const std::string &title, const Book &book) { return title < book.title; }
};

struct LessByYear {
    bool operator()(const Book &book, const int year) { return book.year < year; }
    bool operator()(const int year, const Book &book) { return year < book.year; }
};

struct LessByGenre {
    bool operator()(const Book &book, const Genre genre) { return book.genre < genre; }
    bool operator()(const Genre genre, const Book &book) { return genre < book.genre; }
};

struct LessByRating {
    bool operator()(const Book &book, const double rating) { return book.rating < rating; }
    bool operator()(const double rating, const Book &book) { return rating < book.rating; }
};

struct LessByReadCount {
    bool operator()(const Book &book, const int read_count) { return book.read_count < read_count; }
    bool operator()(const int read_count, const Book &book) { return read_count < book.read_count; }
};

}  // namespace bookdb::comp