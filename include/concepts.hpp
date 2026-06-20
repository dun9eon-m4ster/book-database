#pragma once

#include <concepts>
#include <iterator>

#include "book.hpp"

namespace bookdb {

template <typename T>
concept BookContainerLike = std::ranges::contiguous_range<T> && std::same_as<std::ranges::range_value_t<T>, Book> &&
                            requires(T cont, Book book) {
                                cont.size();
                                cont.clear();
                                cont.push_back(book);
                            };

template <typename T>
concept BookIterator = true;

template <typename S, typename I>
concept BookSentinel = true;

template <typename P>
concept BookPredicate = true;

template <typename C>
concept BookComparator = true;

}  // namespace bookdb