#pragma once

#include "book.hpp"
#include <string_view>

namespace bookdb::comp {

struct LessByAuthor {
    bool operator()(const Book &first, const Book &second) const { return first.author < second.author; }
    bool operator()(const Book &book, const std::string_view &author) const { return book.author < author; }
    bool operator()(const std::string_view &author, const Book &book) const { return author < book.author; }
};

struct LessByTitle {
    bool operator()(const Book &first, const Book &second) const { return first.title < second.title; }
    bool operator()(const Book &book, const std::string &title) const { return book.title < title; }
    bool operator()(const std::string &title, const Book &book) const { return title < book.title; }
};

struct LessByYear {
    bool operator()(const Book &first, const Book &second) const { return first.year < second.year; }
    bool operator()(const Book &book, const int year) const { return book.year < year; }
    bool operator()(const int year, const Book &book) const { return year < book.year; }
};

struct LessByGenre {
    bool operator()(const Book &first, const Book &second) const { return first.genre < second.genre; }
    bool operator()(const Book &book, const Genre genre) const { return book.genre < genre; }
    bool operator()(const Genre genre, const Book &book) const { return genre < book.genre; }
};

struct LessByPopularity {
    bool operator()(const Book &first, const Book &second) const { return first.rating < second.rating; }
    bool operator()(const Book &book, const double rating) const { return book.rating < rating; }
    bool operator()(const double rating, const Book &book) const { return rating < book.rating; }
};

struct LessByReadCount {
    bool operator()(const Book &first, const Book &second) const { return first.read_count < second.read_count; }
    bool operator()(const Book &book, const int read_count) const { return book.read_count < read_count; }
    bool operator()(const int read_count, const Book &book) const { return read_count < book.read_count; }
};

}  // namespace bookdb::comp