﻿/*#######################################################################################
	Copyright (c) 2017-2019 Kasugaccho
	https://github.com/Kasugaccho/DungeonTemplateLibrary
	wanotaitei@gmail.com

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#######################################################################################*/
#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_UTILITY_CHAR_CAST
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_UTILITY_CHAR_CAST

/* Character Code : UTF-8 (BOM) */
/* Bug Check : not checked */
/* Android NDK Compile (Clang 5.0) : already checked */

#include <sstream>
#include <string>

namespace dtl {
	inline namespace utility {

		template<typename Int_>
#if defined(_MSVC_LANG) //C++17 use nodiscard
#if (_MSVC_LANG >= 201703L)
		[[nodiscard]]
#endif
#elif defined(__cplusplus)
#if (__cplusplus >= 201703L)
		[[nodiscard]]
#endif
#endif
		auto charCast(const std::string& field_) noexcept {
			std::istringstream field_stream(field_);
			Int_ field_int{};
			field_stream >> field_int;
			return field_int;
		}
		template<>
#if defined(_MSVC_LANG) //C++17 use nodiscard
#if (_MSVC_LANG >= 201703L)
		[[nodiscard]]
#endif
#elif defined(__cplusplus)
#if (__cplusplus >= 201703L)
		[[nodiscard]]
#endif
#endif
		auto charCast<std::string>(const std::string& field_) noexcept {
			return field_;
		}
		template<>
#if defined(_MSVC_LANG) //C++17 use nodiscard
#if (_MSVC_LANG >= 201703L)
		[[nodiscard]]
#endif
#elif defined(__cplusplus)
#if (__cplusplus >= 201703L)
		[[nodiscard]]
#endif
#endif
		auto charCast<char>(const std::string& field_) noexcept {
			std::istringstream field_stream(field_);
			int field_int{};
			field_stream >> field_int;
			return static_cast<char>(field_int);
		}
		template<>
#if defined(_MSVC_LANG) //C++17 use nodiscard
#if (_MSVC_LANG >= 201703L)
		[[nodiscard]]
#endif
#elif defined(__cplusplus)
#if (__cplusplus >= 201703L)
		[[nodiscard]]
#endif
#endif
		auto charCast<signed char>(const std::string& field_) noexcept {
			std::istringstream field_stream(field_);
			int field_int{};
			field_stream >> field_int;
			return static_cast<signed char>(field_int);
		}
		template<>
#if defined(_MSVC_LANG) //C++17 use nodiscard
#if (_MSVC_LANG >= 201703L)
		[[nodiscard]]
#endif
#elif defined(__cplusplus)
#if (__cplusplus >= 201703L)
		[[nodiscard]]
#endif
#endif
		auto charCast<unsigned char>(const std::string& field_) noexcept {
			std::istringstream field_stream(field_);
			int field_int{};
			field_stream >> field_int;
			return static_cast<unsigned char>(field_int);
		}

	}
}

#endif //Included Dungeon Template Library