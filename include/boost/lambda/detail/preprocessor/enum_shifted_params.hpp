#ifndef BOOST_PREPROCESSOR_ENUM_SHIFTED_PARAMS

//  Copyright (C) 2001 by Vesa Karvonen. Permission to copy, use, modify,
//  sell and distribute this software is granted provided this copyright
//  notice appears in all copies. This software is provided "as is" without
//  express or implied warranty, and with no claim as to its suitability for
//  any purpose.

//  DON'T WASTE YOUR TIME EDITING THIS GENERATED FILE!

#ifndef BOOST_PREPROCESSOR_REPEAT
#  include <boost/lambda/detail/preprocessor/repeat.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_COMMA_IF
#  include <boost/lambda/detail/preprocessor/comma_if.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_CAT
#  include <boost/lambda/detail/preprocessor/cat.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_INC
#  include <boost/lambda/detail/preprocessor/inc.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_DEC
#  include <boost/lambda/detail/preprocessor/dec.hpp>
#endif

#define BOOST_PREPROCESSOR_SHIFTED_PARAM(i,NAME,B) BOOST_PREPROCESSOR_COMMA_IF(i) BOOST_PREPROCESSOR_CAT(NAME,BOOST_PREPROCESSOR_INC(i))
#define BOOST_PREPROCESSOR_ENUM_SHIFTED_PARAMS(n,NAME) BOOST_PREPROCESSOR_REPEAT(BOOST_PREPROCESSOR_DEC(n),BOOST_PREPROCESSOR_SHIFTED_PARAM,NAME,B)
#endif
