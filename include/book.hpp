#pragma once

#include <format>
#include <stdexcept>
#include <string_view>

namespace bookdb {

enum class Genre { Fiction, NonFiction, SciFi, Biography, Mystery, Unknown };

// Ваш код для constexpr преобразования строк в enum::Genre и наоборот здесь

constexpr Genre GenreFromString(std::string_view s) {
    if (s == "Fiction")
        return Genre::Fiction;
    if (s == "NonFiction")
        return Genre::NonFiction;
    if (s == "SciFi")
        return Genre::SciFi;
    if (s == "Biography")
        return Genre::Biography;
    if (s == "Mystery")
        return Genre::Mystery;

    return Genre::Unknown;
}

struct Book {
    // string_view для экономии памяти, чтобы ссылаться на оригинальную строку, хранящуюся в другом контейнере
    std::string_view author;
    std::string title;

    int year;
    Genre genre;
    double rating;
    int read_count;

    // Ваш код для конструкторов здесь

    constexpr Book() = default;

    constexpr Book(std::string_view _new_title, std::string_view _new_author, int _new_year, Genre _new_genre,
                   double _new_rating, int _new_read_count)
        : author(_new_author), title(_new_title), year(_new_year), genre(_new_genre), rating(_new_rating),
          read_count(_new_read_count) {}

    constexpr Book(std::string_view _new_title, std::string_view _new_author, int _new_year,
                   std::string_view _new_genre, double _new_rating, int _new_read_count)
        : Book(_new_title, _new_author, _new_year, GenreFromString(_new_genre), _new_rating, _new_rating) {}
};
}  // namespace bookdb

namespace std {
template <>
struct formatter<bookdb::Genre, char> {
    template <typename FormatContext>
    auto format(const bookdb::Genre g, FormatContext &fc) const {
        std::string genre_str;

        // clang-format off
        using bookdb::Genre;
        switch (g) {
            case Genre::Fiction:    genre_str = "Fiction"; break;
            case Genre::Mystery:    genre_str = "Mystery"; break;
            case Genre::NonFiction: genre_str = "NonFiction"; break;
            case Genre::SciFi:      genre_str = "SciFi"; break;
            case Genre::Biography:  genre_str = "Biography"; break;
            case Genre::Unknown:    genre_str = "Unknown"; break;
            default:
                throw logic_error{"Unsupported bookdb::Genre"};
            }
        // clang-format on
        return format_to(fc.out(), "{}", genre_str);
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

// Ваш код для std::formatter<Book> здесь
template <>
struct formatter<bookdb::Book, char> {
    template <typename FormatContext>
    auto format(const bookdb::Book &book, FormatContext &context) const {
        return format_to(context.out(),
                         "author: {},\t title: {},\t year: {},\t genre: {},\t rating: {},\t read count: {}",
                         book.author, book.title, book.year, book.genre, book.rating, book.read_count);
    }

    constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }
};

}  // namespace std
