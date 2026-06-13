#pragma once

#include <string>
#include <string_view>

namespace bookdb {

struct TransparentStringLess {
    using is_transparent = void;

    bool operator()(const std::string_view &first, const std::string_view &second) const { return first < second; }
};

struct TransparentStringEqual {
    using is_transparent = void;

    bool operator()(std::string_view first, std::string_view second) const { return first == second; }
};

struct TransparentStringHash {
    using is_transparent = void;

    size_t operator()(std::string_view str) const { return std::hash<std::string_view>{}(str); }

    size_t operator()(const std::string &str) const { return std::hash<std::string_view>{}(str); }

    size_t operator()(const char *str) const { return std::hash<std::string_view>{}(str); }
};

}  // namespace bookdb
