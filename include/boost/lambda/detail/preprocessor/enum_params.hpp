#ifndef BOOST_PREPROCESSOR_ENUM_PARAMS

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

#define BOOST_PREPROCESSOR_PARAM(i,P,B) BOOST_PREPROCESSOR_COMMA_IF(i) P##i
#define BOOST_PREPROCESSOR_ENUM_PARAMS(n,P) BOOST_PREPROCESSOR_REPEAT(n,BOOST_PREPROCESSOR_PARAM,P,B)

#define BOOST_PREPROCESSOR_PARAM_WITH_A_DEFAULT(i,P,D) BOOST_PREPROCESSOR_COMMA_IF(i) P##i=D
#define BOOST_PREPROCESSOR_ENUM_PARAMS_WITH_A_DEFAULT(n,P,D) BOOST_PREPROCESSOR_REPEAT(n,BOOST_PREPROCESSOR_PARAM_WITH_A_DEFAULT,P,D)

#define BOOST_PREPROCESSOR_PARAM_WITH_DEFAULT(i,P,D) BOOST_PREPROCESSOR_COMMA_IF(i) P##i=D##i
#define BOOST_PREPROCESSOR_ENUM_PARAMS_WITH_DEFAULTS(n,P,D) BOOST_PREPROCESSOR_REPEAT(n,BOOST_PREPROCESSOR_PARAM_WITH_DEFAULT,P,D)
#endif
