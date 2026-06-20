#include "book.hpp"
#include "book_database.hpp"
#include <gtest/gtest.h>

TEST(BookDatabaseTest, PushBackCheck) {
    bookdb::BookDatabase db;
    bookdb::Book book1("book title 1", "author 1", 2026, bookdb::Genre::Biography, 5.0, 10);
    bookdb::Book book2("book title 2", "author 2", 2026, bookdb::Genre::Fiction, 4.9, 10);
    bookdb::Book book3("book title 3", "author 3", 2026, bookdb::Genre::Mystery, 4.8, 10);

    db.PushBack(book1);
    db.PushBack(book2);
    db.PushBack(book3);

    EXPECT_EQ(db.size(), 3);

    auto it = db.begin();
    EXPECT_NE(it, db.end());
    EXPECT_EQ(book1.title, it->title);
    EXPECT_NE((++it), db.end());
    EXPECT_EQ(book2.title, it->title);
    EXPECT_NE((++it), db.end());
    EXPECT_EQ(book3.title, it->title);
}

TEST(BookDatabaseTest, AuthorsCheck) {
    bookdb::BookDatabase db;

    std::string author1 = "author 1";
    std::string author2 = "author 2";
    std::string author3 = "author 3";

    bookdb::Book book1("book title 1", author1, 2026, bookdb::Genre::Biography, 5.0, 10);
    bookdb::Book book2("book title 2", author2, 2026, bookdb::Genre::Fiction, 4.9, 10);
    bookdb::Book book3("book title 3", author3, 2026, bookdb::Genre::Mystery, 4.8, 10);

    db.PushBack(book1);
    db.PushBack(book2);
    db.PushBack(book3);

    auto authors = db.GetAuthors();
    EXPECT_TRUE(authors.contains(author1));
    EXPECT_TRUE(authors.contains(author2));
    EXPECT_TRUE(authors.contains(author3));
}

TEST(BookDatabaseTest, EmplaceBackCheck) {
    bookdb::BookDatabase db;

    db.EmplaceBack("book title 1", "author 1", 2026, bookdb::Genre::Biography, 5.0, 10);
    db.EmplaceBack("book title 2", "author 2", 2026, bookdb::Genre::Fiction, 4.9, 10);
    db.EmplaceBack("book title 3", "author 3", 2026, bookdb::Genre::Mystery, 4.8, 10);

    EXPECT_EQ(db.size(), 3);

    auto it = db.begin();
    EXPECT_NE(it, db.end());
    EXPECT_EQ("book title 1", it->title);
    EXPECT_NE((++it), db.end());
    EXPECT_EQ("book title 2", it->title);
    EXPECT_NE((++it), db.end());
    EXPECT_EQ("book title 3", it->title);
}