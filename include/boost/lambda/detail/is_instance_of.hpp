// Boost Lambda Library - is_instance_of.hpp ---------------------

// Copyright (C) 2001 Jaakko Järvi (jaakko.jarvi@cs.utu.fi)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies. 
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice 
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty, 
// and with no claim as to its suitability for any purpose.
//
// For more information, see www.boost.org

// ---------------------------------------------------------------

#ifndef BOOST_LAMBDA_IS_INSTANCE_OF
#define BOOST_LAMBDA_IS_INSTANCE_OF

#include "boost/preprocessor/enum_shifted_params.hpp"
#include "boost/preprocessor/repeat_2nd.hpp"

// is_instance_of --------------------------------
// 
// is_instance_of_n<A, B>::value is true, if type A is 
// an instantiation of a template B, or A derives from an instantiation 
// of template B
//
// n is the number of template arguments for B
// 
// Example:
// is_instance_of_2<std::istream, basic_stream>::value == true

// Vesa Karvonen's preprocessor library is not part of boost (yet), so 
// the relevant headers are under boost/lambda/detail

#define BOOST_LAMBDA_CLASS(N,A) BOOST_PP_COMMA_IF(N) class
#define BOOST_LAMBDA_CLASS_ARG(N,A) BOOST_PP_COMMA_IF(N) class T##N 
#define BOOST_LAMBDA_ARG(N,A) BOOST_PP_COMMA_IF(N) T##N 

#define BOOST_LAMBDA_CLASS_LIST(n) BOOST_PP_REPEAT(n, BOOST_LAMBDA_CLASS, FOO)

#define BOOST_LAMBDA_CLASS_ARG_LIST(n) BOOST_PP_REPEAT(n, BOOST_LAMBDA_CLASS_ARG, FOO)

#define BOOST_LAMBDA_ARG_LIST(n) BOOST_PP_REPEAT(n, BOOST_LAMBDA_ARG, FOO)

namespace boost {
namespace lambda {
namespace detail {

typedef char yes_type;
typedef double no_type;

#ifndef __GNUC__

  // store a pointer, as passing non-PODs through ellipsis results in	
  // warnings in some compilers						

#define BOOST_LAMBDA_IS_INSTANCE_OF_TEMPLATE(INDEX)				\
template <class From, template <BOOST_LAMBDA_CLASS_LIST(INDEX)> class To>	\
struct BOOST_PP_CAT(is_instance_of_,INDEX)		\
{										\
private:									\
   static no_type _m_check(...);						\
										\
   template <BOOST_LAMBDA_CLASS_ARG_LIST(INDEX)>				\
   static yes_type _m_check(const To<BOOST_LAMBDA_ARG_LIST(INDEX)>*);		\
										\
   static From* _m_from;							\
										\
public:										\
   static const bool value = sizeof( _m_check(_m_from) ) == sizeof(yes_type);	\
   void foo();									\
};


#else
  // GCC version

#define BOOST_LAMBDA_IS_INSTANCE_OF_TEMPLATE(INDEX)				\
template <class From, template <BOOST_LAMBDA_CLASS_LIST(INDEX)> class To>	\
struct BOOST_PP_CAT(is_instance_of_,INDEX)		\
{										\
private:									\
   static no_type _m_check(...);						\
										\
   template <BOOST_LAMBDA_CLASS_ARG_LIST(INDEX)>				\
   static yes_type _m_check(const To<BOOST_LAMBDA_ARG_LIST(INDEX)>*);		\
										\
   static From* _m_from;							\
										\
public:										\
   static const bool value;							\
   void foo();									\
};										\
										\
template <class From, template <BOOST_LAMBDA_CLASS_LIST(INDEX)> class To>	\
const bool									\
BOOST_PP_CAT(is_instance_of_,INDEX)<From, To>::value	\
  = sizeof( _m_check(_m_from) ) == sizeof(yes_type);  

#endif 

#define BOOST_LAMBDA_HELPER(N, A) BOOST_LAMBDA_IS_INSTANCE_OF_TEMPLATE( BOOST_PP_INC(N) )

// Generate the traits for 1-4 argument templates

BOOST_PP_REPEAT_2ND(4,BOOST_LAMBDA_HELPER,FOO)

#undef BOOST_LAMBDA_HELPER
#undef BOOST_LAMBDA_IS_INSTANCE_OF_TEMPLATE
#undef BOOST_LAMBDA_CLASS
#undef BOOST_LAMBDA_ARG
#undef BOOST_LAMBDA_CLASS_ARG
#undef BOOST_LAMBDA_CLASS_LIST
#undef BOOST_LAMBDA_ARG_LIST
#undef BOOST_LAMBDA_CLASS_ARG_LIST

} // detail
} // lambda
} // boost

#endif

