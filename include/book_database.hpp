#pragma once

#include <format>
#include <string>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

#include "book.hpp"
#include "concepts.hpp"
#include "heterogeneous_lookup.hpp"

namespace bookdb {

template <BookContainerLike BookContainer = std::vector<Book>>
class BookDatabase {
public:
    // Type aliases
    using iterator = BookContainer::iterator;
    using size_type = BookContainer::size_type;

    using AuthorContainer = std::unordered_set<std::string, TransparentStringHash, TransparentStringEqual>;

    BookDatabase() = default;

    void PushBack(const Book &_new_book) {
        auto copy = _new_book;
        PushBack(std::move(copy));
    }

    void PushBack(Book &&book) {
        auto insert_result = authors_.insert(std::string(book.author));
        book.author = *insert_result.first;
        books_.push_back(std::move(book));
    }

    template <typename... Args>
        requires std::constructible_from<Book, Args...>
    void EmplaceBack(Args &&...args) {
        Book book(std::forward<Args>(args)...);
        auto insert_result = authors_.insert(std::string(book.author));
        book.author = *insert_result.first;
        books_.emplace_back(std::move(book));
    }

    std::span<const Book> GetBooks() const { return books_; }

    std::span<Book> GetBooks() { return books_; }

    const AuthorContainer &GetAuthors() { return authors_; }

    const AuthorContainer &GetAuthors() const { return authors_; }

    void Clear() {
        books_.clear();
        authors_.clear();
    }

    // Standard container interface methods
    iterator begin() { return books_.begin(); }
    iterator end() { return books_.end(); }
    size_type size() const { return books_.size(); }

private:
    BookContainer books_;
    AuthorContainer authors_;
};

}  // namespace bookdb

namespace std {

template <>
struct formatter<bookdb::BookDatabase<std::vector<bookdb::Book>>> {
    template <typename FormatContext>
    auto format(const bookdb::BookDatabase<std::vector<bookdb::Book>> &db, FormatContext &fc) const {
        format_to(fc.out(), "BookDatabase (size = {}): ", db.size());

        format_to(fc.out(), "Books:\n");
        for (const auto &book : db.GetBooks()) {
            format_to(fc.out(), "- {}\n", book);
        }

        format_to(fc.out(), "Authors:\n");
        for (const auto &author : db.GetAuthors()) {
            format_to(fc.out(), "- {}\n", author);
        }

        return fc.out();
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};
}  // namespace std
