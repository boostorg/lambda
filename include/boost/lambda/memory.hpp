// -- memory.hpp -- Lambda Library -----------------------------------

// Copyright (C) 2000 Gary Powell (gary.powell@sierra.com)
// Copyright (C) 1999, 2000 Jaakko Järvi (jaakko.jarvi@cs.utu.fi)
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
// For more information, see http://lambda.cs.utu.fi 

// revision history

// 11 09 00 added details namespace (GWP)
// 10 02 00 Reworked and changed so that the type of the 
//          object to be 'newed' is given
//          as a explicitely specified template parameter, e.g.:
//          new_ptr<Foo>(a, b, c)() returns new Foo(a, b, c) (JJ)
// 10 02 00 Initial version (GWP)
//
// Delayed memory creation and deletion 


#if !defined(MEMORY_HPP)
#define MEMORY_HPP

#include "ll/details/ll_defines_on.hpp"
#include "ll_advanced/details/ll_memory.hpp"

namespace boost { 
namespace lambda {

// new_ptr bind functions.
template <class T>
inline const ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<0,  details::new_ptr_action<0, T> >, ::boost::tuples::nil, ::boost::bind::details::combine_arities<>::value> >
new_ptr() { 
  return ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<0,  details::new_ptr_action<0, T> >, ::boost::tuples::nil, ::boost::bind::details::combine_arities<>::value> >
    ( ::boost::tuples::nil() );
}

template <class T, class Arg1>
inline const ::boost::bind::details::lambda_functor<
  ::boost::bind::details::lambda_functor_args<
    ::boost::bind::details::action< 
      1, 
       details::new_ptr_action<1, T> 
    >, 
    ::boost::tuples::tuple<typename 
         LL_DEFAULT_BIND_ARGUMENT_CONVERSION 
<
            LL_CONST Arg1>::type>, 
    ::boost::bind::details::combine_arities<Arg1>::value
  > 
>
new_ptr(LL_CONST Arg1& a1) { 
  return ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<1,  details::new_ptr_action<1, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type>, ::boost::bind::details::combine_arities<Arg1>::value> >
    ( ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type>(a1));
}


template <class T, class Arg1, class Arg2>
inline const ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<2,  details::new_ptr_action<2, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2>::value> >
new_ptr(LL_CONST Arg1& a1, LL_CONST Arg2& a2) { 
  return ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<2,  details::new_ptr_action<2, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2>::value> >
    ( ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type>(a1, a2));
}

template <class T, class Arg1, class Arg2, class Arg3>
inline const ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<3,  details::new_ptr_action<3, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3>::value> >
new_ptr(LL_CONST Arg1& a1, LL_CONST Arg2& a2, LL_CONST Arg3& a3) { 
  return ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<3,  details::new_ptr_action<3, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3>::value> >
    ( ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type>(a1, a2, a3));
}

template <class T, class Arg1, class Arg2, class Arg3, class Arg4>
inline const ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<4,  details::new_ptr_action<4, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3, Arg4>::value> >
new_ptr(LL_CONST Arg1& a1, LL_CONST Arg2& a2, LL_CONST Arg3& a3, LL_CONST Arg4& a4) { 
  return ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<4,  details::new_ptr_action<4, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3, Arg4>::value> >
    ( ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type>(a1, a2, a3, a4));
}

template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline const ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<5,  details::new_ptr_action<5, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5>::value> >
new_ptr(LL_CONST Arg1& a1, LL_CONST Arg2& a2, LL_CONST Arg3& a3, LL_CONST Arg4& a4, LL_CONST Arg5& a5) { 
  return ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<5,  details::new_ptr_action<5, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5>::value> >
    ( ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type>(a1, a2, a3, a4, a5));
}

template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline const ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<6,  details::new_ptr_action<6, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::value> >
new_ptr(LL_CONST Arg1& a1, LL_CONST Arg2& a2, LL_CONST Arg3& a3, LL_CONST Arg4& a4, LL_CONST Arg5& a5, LL_CONST Arg6& a6) { 
  return ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<6,  details::new_ptr_action<6, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::value> >
    ( ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type>(a1, a2, a3, a4, a5, a6));
}

template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
inline const ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<7,  details::new_ptr_action<7, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg7>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value> >
new_ptr(LL_CONST Arg1& a1, LL_CONST Arg2& a2, LL_CONST Arg3& a3, LL_CONST Arg4& a4, LL_CONST Arg5& a5, LL_CONST Arg6& a6, LL_CONST Arg7& a7) { 
  return ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<7,  details::new_ptr_action<7, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg7>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::value> >
    ( ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg7>::type>(a1, a2, a3, a4, a5, a6, a7));
}

template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8>
inline const ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<8,  details::new_ptr_action<8, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg7>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg8>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::value> >
new_ptr(LL_CONST Arg1& a1, LL_CONST Arg2& a2, LL_CONST Arg3& a3, LL_CONST Arg4& a4, LL_CONST Arg5& a5, LL_CONST Arg6& a6, LL_CONST Arg7& a7, LL_CONST Arg8& a8) { 
  return ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<8,  details::new_ptr_action<8, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg7>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg8>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>::value> >
    ( ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg7>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg8>::type>(a1, a2, a3, a4, a5, a6, a7, a8));
}

template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8, class Arg9>
inline const ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<9,  details::new_ptr_action<9, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg7>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg8>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg9>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9>::value> >
new_ptr(LL_CONST Arg1& a1, LL_CONST Arg2& a2, LL_CONST Arg3& a3, LL_CONST Arg4& a4, LL_CONST Arg5& a5, LL_CONST Arg6& a6, LL_CONST Arg7& a7, LL_CONST Arg8& a8, LL_CONST Arg9& a9) { 
  return ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<9,  details::new_ptr_action<9, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg7>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg8>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg9>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9>::value> >
    ( ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg7>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg8>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg9>::type>(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8, class Arg9, class Arg10>
inline const ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<10,  details::new_ptr_action<10, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg7>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg8>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg9>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg10>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10>::value> >
new_ptr(LL_CONST Arg1& a1, LL_CONST Arg2& a2, LL_CONST Arg3& a3, LL_CONST Arg4& a4, LL_CONST Arg5& a5, LL_CONST Arg6& a6, LL_CONST Arg7& a7, LL_CONST Arg8& a8, LL_CONST Arg9& a9, LL_CONST Arg10& a10) { 
  return ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<10,  details::new_ptr_action<10, T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg7>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg8>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg9>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg10>::type>, ::boost::bind::details::combine_arities<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10>::value> >
    ( ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg1>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg2>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg3>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg4>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg5>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg6>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg7>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg8>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg9>::type, typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION <LL_CONST Arg10>::type>(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10));
}

// new_array bind function.
template <class T, class Arg1>
inline const ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<1, details::new_array_action<T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION<LL_CONST Arg1>::type>, ::boost::bind::details::combine_arities<Arg1>::value> >
new_array(LL_CONST Arg1& a1) { 
  return ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<1, details::new_array_action<T> >, ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION<LL_CONST Arg1>::type>, ::boost::bind::details::combine_arities<Arg1>::value> >
    ( ::boost::tuples::tuple<typename LL_DEFAULT_BIND_ARGUMENT_CONVERSION<LL_CONST Arg1>::type>(a1));
}

// delete_ptr bind function.
template <class Arg1>
inline const ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<1, details::delete_action<details::delete_ptr_action> >, ::boost::tuples::tuple<typename ::boost::tuples::convert_to_ref_by_default <Arg1>::type>, ::boost::bind::details::combine_arities<Arg1>::value> >
delete_ptr(Arg1& a1) { 
  return ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<1, details::delete_action<details::delete_ptr_action> >, ::boost::tuples::tuple<typename ::boost::tuples::convert_to_ref_by_default <Arg1>::type>, ::boost::bind::details::combine_arities<Arg1>::value> >
    ( ::boost::tuples::tuple<typename ::boost::tuples::convert_to_ref_by_default <Arg1>::type>(a1));
}

// delete_array bind function.
template <class Arg1>
inline const ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<1, details::delete_action<details::delete_array_action> >, ::boost::tuples::tuple<typename ::boost::tuples::convert_to_ref_by_default <Arg1>::type>, ::boost::bind::details::combine_arities<Arg1>::value> >
delete_array(Arg1& a1) { 
  return ::boost::bind::details::lambda_functor< ::boost::bind::details::lambda_functor_args< ::boost::bind::details::action<1, details::delete_action<details::delete_array_action> >, ::boost::tuples::tuple<typename ::boost::tuples::convert_to_ref_by_default <Arg1>::type>, ::boost::bind::details::combine_arities<Arg1>::value> >
    ( ::boost::tuples::tuple<typename ::boost::tuples::convert_to_ref_by_default <Arg1>::type>(a1));
}

} // namespace lambda 
} // namespace boost

#include "ll/details/ll_defines_off.hpp"

#endif
