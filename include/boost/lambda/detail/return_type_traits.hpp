//  return_type_traits.hpp -- Boost Lambda Library ---------------------------

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
// For more information, see www.boost.org


#ifndef BOOST_LAMBDA_RETURN_TYPE_TRAITS_HPP
#define BOOST_LAMBDA_RETURN_TYPE_TRAITS_HPP

#include <cstddef> // needed for the ptrdiff_t

namespace boost { 
namespace lambda {

// Much of the type deduction code for standard arithmetic types 
// from Gary Powell

template<class A, class B, class C> 
struct open_args {
  typedef A type1; 
  typedef B type2; 
  typedef C type3; 
};


// -- return type -------------------------------------
  // does not handle lambda_functor lambda_functors
  // e.g. if the lambda_functor action is a lambda_functor

// The primary template:
// if we know nothing about Arg, it is not a lambda_functor. 
// Hence the return type is Arg itself.
template <class Arg, class Open> 
struct return_type { typedef Arg type; };

// Unary actions (result from unary operators)
// do not have a default return type.
template<class Act, class A> struct return_type_1 { 
   typedef typename 
     detail::generate_error<return_type_1>::type_deduction_did_not_succeed 
       type;
};

// binary actions ---------------------------------------------------
template <class Act, class A, class B> struct return_type_2;

// unary function action (it is binary action)
// If a function object overloads operator(), the return type could depend
// on the argument types. This is not taken into consideration.
template<class A, class B> struct return_type_2<function_action<2>, A, B> {
  typedef typename return_type_1<function_action<1>, A>::type type;
};

// reduce to lambda_functor_args
// to be on the safe side, constness and references are stripped away,
// though the type should always be plain 
template <class Arg, class Open>
struct return_type<lambda_functor<Arg>, Open> {
  typedef typename return_type<Arg, Open>::type type;
};
template <class Arg, class Open>
struct return_type<const lambda_functor<Arg>, Open> {
  typedef typename return_type<Arg, Open>::type type;
};
template <class Arg, class Open>
struct return_type<lambda_functor<Arg>&, Open> {
  typedef typename return_type<Arg, Open>::type type;
};
template <class Arg, class Open>
struct return_type<const lambda_functor<Arg>&, Open> {
  typedef typename return_type<Arg, Open>::type type;
};

// placeholders
// to be on the safe side, constness and references are stripped away,
// though the type should always be plain
 template<int I, class Open>
struct return_type<const placeholder<I>, Open> { 
  typedef typename return_type<placeholder<I>, Open>::type type;
};
template<int I, class Open>
struct return_type<placeholder<I>&, Open> { 
  typedef typename return_type<placeholder<I>, Open>::type type;
};
template<int I, class Open>
struct return_type<const placeholder<I>&, Open> { 
  typedef typename return_type<placeholder<I>, Open>::type type;
};

template <class Open> 
struct return_type<placeholder<FIRST>, Open> { 
  typedef typename Open::type1 type; 
};

template <class Open> 
struct return_type<placeholder<SECOND>, Open> { 
  typedef typename Open::type2 type; 
};

template <class Open> 
struct return_type<placeholder<THIRD>, Open> { 
  typedef typename Open::type2 type; 
};

// the exception placeholder deduction, the third placeholder slot
// is reused
template <class Open> 
struct return_type<placeholder<EXCEPTION>, Open> { 
  typedef typename Open::type3 type;
};

// handle different kind of actions ------------------------

// function action: this covers all arities:
// If a function object overloads operator(), the return type could depend
// on the argument types. This is not taken into consideration.
template<int I, class A> struct return_type_1<function_action<I>, A > { 
  typedef typename function_adaptor<
                     typename detail::remove_reference_and_cv<A>::type
                   >::result_type type;
};


// general unary and binary actions
template<class Act, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<1, Act>, Args, Code>, Open> {
 typedef 
//   typename detail::constify_rvalues<
     typename return_type_1<
       Act, 
       typename return_type<
         typename detail::tuple_element_as_reference<
           0, Args
         >::type, Open>::type 
     >::type
//   >::type 
   type;
};

template<class Act, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<2, Act>, Args, Code>, Open> {
  typedef 
//   typename detail::constify_rvalues<     
     typename return_type_2<
       Act, 
       typename return_type<
          typename detail::tuple_element_as_reference<0, Args>::type, 
          Open
       >::type, 
       typename return_type<
          typename detail::tuple_element_as_reference<1, Args>::type, 
          Open
       >::type
     >::type
//   >::type 
  type;
};

// unary to 3-ary lambda_functor_actions
template<class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<1, lambda_functor_action<1> >, Args, Code>, Open> {

// first call recursively return_type again. There can be arbitrary
// many nested lambda_functors with lambda_functor_action, 
// this traverses them all.
   typedef typename 
   return_type<
       typename detail::tuple_element_as_reference<0,Args>::type, Open
     >::type type_1;

// type_1 must be something that can be called (it must be bindable),
// hence we can use function_adaptor to dig out its return type.
   typedef typename 
     function_adaptor<
       typename detail::remove_reference_and_cv<type_1>::type
     >::result_type type;
};
     
template<class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<2, lambda_functor_action<2> >, Args, Code>, Open> {
 typedef typename return_type<
   typename detail::tuple_element_as_reference<0,Args>::type, Open
  >::type type_1;
  typedef typename function_adaptor<
    typename detail::remove_reference_and_cv<type_1>::type
  >::result_type type;
};

   
template<class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<3, lambda_functor_action<3> >, Args, Code>, Open> {
  typedef typename return_type<
    typename detail::tuple_element_as_reference<0,Args>::type, Open
  >::type type_1;
  typedef typename function_adaptor<
    typename detail::remove_reference_and_cv<type_1>::type
  >::result_type type;
};

template<class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<4, lambda_functor_action<4> >, Args, Code>, Open> {
  typedef typename return_type<
    typename detail::tuple_element_as_reference<0,Args>::type, Open
  >::type type_1;
  typedef typename function_adaptor<
    typename detail::remove_reference_and_cv<type_1>::type
  >::result_type type;
};

   
// protect action:
// the return type is the lambda_functor wrapped inside protect
template<class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<1, protect_action>, Args, Code>, Open> {
  typedef typename detail::tuple_element_as_reference<0,Args>::type type;
};


   
// 3 arguments or more ---------------------------------------------
// this must be a function_action. Note that the previous unary and binary 
// specalisations take care of nullary and unary function adaptors, that is,
// unary and binary actions.
// Since function_actions determine the return type based on the function
// object only, we can ignore the arguments and reuse return_type_1.

template <int I, class Act, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<I, Act>, Args, Code>, Open> {
 typedef
//   typename detail::constify_rvalues<
     typename return_type_1<
       Act, 
       typename return_type<
         typename detail::tuple_element_as_reference<0,Args>::type, 
         Open
       >::type
     >::type
//   >::type 
  type;
};

// The explicit return type action case, it is unary
template<class RET, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<1, explicit_return_type_action<RET> >, Args, Code>, Open> {
  typedef //typename detail::constify_rvalues<RET>::type 
     RET type;
};


// return types of control constructs (all return void)
template<class Act, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<1, return_void_action<Act> >, Args, Code>, Open >
{ 
  typedef void type; 
};

template<class Act, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<2, return_void_action<Act> >, Args, Code>, Open >
{ 
  typedef void type; 
};

template<int I, class Act, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<I, return_void_action<Act> >, Args, Code>, Open >
{ 
  typedef void type; 
};


} // namespace lambda
} // namespace boost

#endif
