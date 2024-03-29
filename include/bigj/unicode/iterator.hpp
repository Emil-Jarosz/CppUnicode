#pragma once

#include "encoding.hpp"

#include <iterator>

namespace bigj {
namespace unicode {

template<encoding E>
struct iterator {

    using code_unit = typename E::code_unit;

    using value_type = code_point;
    using pointer = const code_unit*;
    using iterator_category = std::bidirectional_iterator_tag;

    constexpr iterator() noexcept {}
    explicit constexpr iterator(pointer ptr) noexcept : m_ptr{ptr} {}

    constexpr auto operator*() const noexcept -> value_type {
        return E::decode(m_ptr);
    }

    constexpr auto operator++() noexcept -> iterator& {
        m_ptr = E::next_code_point(m_ptr);
        return *this;
    }

    constexpr auto operator++(int) noexcept -> iterator {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    constexpr auto operator--() noexcept -> iterator& {
        m_ptr = E::prev_code_point(m_ptr);
        return *this;
    }

    constexpr auto operator--(int) noexcept -> iterator {
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    constexpr auto operator<=>(const iterator&) const noexcept = default;

    constexpr auto address() const noexcept -> pointer {
        return m_ptr;
    }

  private:
    pointer m_ptr = nullptr;
};

} // namespace unicode
} // namespace bigj

namespace std {

template<bigj::unicode::encoding E>
struct iterator_traits<bigj::unicode::iterator<E>> {

    using difference_type = ptrdiff_t;
    using value_type = bigj::unicode::code_point;
    using pointer = const typename E::code_unit*;
    using reference = const bigj::unicode::code_point&;
    using iterator_category = std::bidirectional_iterator_tag;
};

} // namespace std
