﻿/*#######################################################################################
	Copyright (c) 2017-2019 Kasugaccho
	Copyright (c) 2018-2019 As Project
	https://github.com/Kasugaccho/DungeonTemplateLibrary
	wanotaitei@gmail.com

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#######################################################################################*/
#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_TYPE_S_SIZE_T_HPP
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_TYPE_S_SIZE_T_HPP

#if defined(UE_BUILD_FINAL_RELEASE) //UE4
namespace dtl { namespace type { using ssize = ::SSIZE_T; } }
#else
#include <cstddef>
namespace dtl { namespace type { using ssize = ::std::ptrdiff_t; } }
#endif

#endif //Included Dungeon Template Library