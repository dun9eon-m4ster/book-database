#pragma once

#include "book.hpp"
#include "comparators.hpp"
#include <functional>
#include <string>
#include <string_view>

namespace bookdb {

struct TransparentStringLess {
    using is_transparent = void;

    bool operator()(const Book &book, const std::string &title) const { return comp::LessByTitle()(book, title); }
    bool operator()(const std::string &title, const Book &book) const { return comp::LessByTitle()(title, book); }

    bool operator()(const Book &book, const std::string_view &author) const {
        return comp::LessByAuthor()(book, author);
    }
    bool operator()(const std::string_view &author, const Book &book) const {
        return comp::LessByAuthor()(author, book);
    }
};

struct TransparentStringEqual {
    using is_transparent = void;

    bool operator()(const Book &book, const std::string &title) const { return book.title == title; }
    bool operator()(const std::string &title, const Book &book) const { return title == book.title; }

    bool operator()(const Book &book, const std::string_view &author) const { return book.author == author; }
    bool operator()(const std::string_view &author, const Book &book) { return author == book.author; }
};

struct TransparentStringHash {
    using is_transparent = void;

    //???
};

}  // namespace bookdb
