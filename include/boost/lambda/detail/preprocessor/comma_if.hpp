#ifndef BOOST_PREPROCESSOR_COMMA_IF

//  Copyright (C) 2001 by Vesa Karvonen. Permission to copy, use, modify,
//  sell and distribute this software is granted provided this copyright
//  notice appears in all copies. This software is provided "as is" without
//  express or implied warranty, and with no claim as to its suitability for
//  any purpose.

//  DON'T WASTE YOUR TIME EDITING THIS GENERATED FILE!

#ifndef BOOST_PREPROCESSOR_IF
#  include <boost/lambda/detail/preprocessor/if.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_COMMA
#  include <boost/lambda/detail/preprocessor/comma.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_EMPTY
#  include <boost/lambda/detail/preprocessor/empty.hpp>
#endif

#define BOOST_PREPROCESSOR_COMMA_IF(c) BOOST_PREPROCESSOR_IF(c,BOOST_PREPROCESSOR_COMMA,BOOST_PREPROCESSOR_EMPTY)()
#endif
