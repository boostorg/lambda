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

  // In some cases return type deduction should fail (an invalid lambda 
  // expression). Sometimes the lambda expression can be ok, the return type
  // just is not deducible (user defined operators). Then return type deduction
  // should never be entered at all, and the use of ret<> does this.
  // However, for nullary lambda functors, return type deduction is always
  // entered, and there seems to be no way around this.

  // (the return type is part of the prototype of the non-template
  // operator()(). The prototype is instantiated, even though the body 
  // is not.) 
 
  // So, in the case the return type deduction should fail, it should not
  // fail directly, but rather result in a valid but wrong return type,
  // causing a compile time error, if the function is really called.

namespace detail {

template<class> class return_type_deduction_failure {};

}

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
     detail::return_type_deduction_failure<return_type_1> type;
};

  // read the comments for return_type_2_0
template <class Act, class A> struct return_type_1_0 {

typedef typename boost::remove_reference<A>::type A1;

  typedef typename 
    detail::IF_type<
      boost::is_function<A1>::value,
      boost::add_reference<A1>,
      boost::add_const<A1>
    >::type A2;

typedef typename 
  detail::IF<
  is_lambda_functor<A>::value, 
    lambda_functor_sub<
      lambda_functor_args< 
        action<1, Act>, 
        tuple<A2>, 
        dig_arity<A>::value
      >
    >,
    typename return_type_1<Act, A>::type
  >::RET type;
};

// binary actions ---------------------------------------------------
  template <class Act, class A, class B> struct return_type_2;

// experimental feature
  // We may have a lambda functor as a result type of a subexpression 
  // (if protect) has  been used.
  // Thus, if one of the parameter types is a lambda functor, the result
  // is a lambda functor as well. 
  // We need to make a conservative choise here, all arguments in the 
  // resulting lambda functor will be stored as const copies. The true
  // result type may have non-const reference arguments, but it is either
  // impossible or very hard to find out that. And references here might 
  // be unsafe (references to temporaries that do not exist).

  // The return type is a subclass of lambda_functor, which has a converting 
  // copy constructor. It can copy any lambda functor, that has the same 
  // action type and code, and a copy compatible argument tuple.

template <class Act, class A, class B> struct return_type_2_0 {

  typedef typename boost::remove_reference<A>::type A1;
  typedef typename boost::remove_reference<B>::type B1;

  // adding const to a function type fails, these tests are to 
  // avoid that. Note that only the true branch is instantiated with this IF
  typedef typename 
    detail::IF_type<
      boost::is_function<A1>::value,
      boost::add_reference<A1>,
      boost::add_const<A1>
    >::type A2;

  typedef typename 
    detail::IF_type<
      boost::is_function<B1>::value,
      boost::add_reference<B1>,
      boost::add_const<B1>
    >::type B2;


typedef typename 
  detail::IF<
    is_lambda_functor<A>::value || is_lambda_functor<B>::value,
    lambda_functor_sub<
      lambda_functor_args< 
        action<2, Act>, 
        tuple<A2, B2>, 
        combine_arities<A, B>::value
      >
    >,
    typename return_type_2<Act, A, B>::type
  >::RET type;
};

  // Was needed for a while, not now, since no return type deduction depends
  // on more than two arguments

//  template <class Act, class A, class B, class C> struct return_type_3_0 {

//    typedef typename boost::remove_reference<A>::type A1;
//    typedef typename boost::remove_reference<B>::type B1;
//    typedef typename boost::remove_reference<C>::type C1;

//    // adding const to a function type fails, these tests are to 
//    // avoid that. Note that only the true branch is instantiated with this IF
//    typedef typename 
//      detail::IF_type<
//        boost::is_function<A1>::value,
//        boost::add_reference<A1>,
//        boost::add_const<A1>
//      >::type A2;

//    typedef typename 
//      detail::IF_type<
//        boost::is_function<B1>::value,
//        boost::add_reference<B1>,
//        boost::add_const<B1>
//      >::type B2;

//    typedef typename 
//      detail::IF_type<
//        boost::is_function<C1>::value,
//        boost::add_reference<C1>,
//        boost::add_const<C1>
//      >::type C2;


//  typedef typename 
//    detail::IF<
//      is_lambda_functor<A>::value || is_lambda_functor<B>::value ||
//      is_lambda_functor<C>::value,
//      lambda_functor_sub<
//        lambda_functor_args< 
//          action<3, Act>, 
//          tuple<A2, B2, C2>, 
//          combine_arities<A, B, C>::value
//        >
//      >,
//      typename return_type_1<Act, A>::type
//    >::RET type;
//  };

// unary function action (it is binary action)
// If a function object overloads operator(), the return type could depend
// on the argument types. This is not taken into consideration.
template<class A, class B, class Ret> 
struct return_type_2<function_action<2, Ret>, A, B> {
  typedef typename return_type_1<function_action<1, Ret>, A>::type type;
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

  // use the return type given in the bind invocation as bind<Ret>(...)
template<int I, class A, class Ret> 
struct return_type_1<function_action<I, Ret>, A > { 
  typedef Ret type;
};

  // Ret is detail::unspecified, so try to deduce return type
template<int I, class A> 
struct return_type_1<function_action<I, detail::unspecified>, A > { 
  typedef typename function_adaptor_sub<
                     typename detail::remove_reference_and_cv<A>::type
                   >::type type;
};


// general unary and binary actions
template<class Act, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<1, Act>, Args, Code>, Open> {
 typedef 
     typename return_type_1_0<
       Act, 
       typename return_type<
         typename detail::tuple_element_as_reference<
           0, Args
         >::type, Open>::type 
     >::type
   type;
};

template<class Act, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<2, Act>, Args, Code>, Open> {
  typedef 
     typename return_type_2_0<
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
  type;
};

  // Was needed for a while, not now, since no return type deduction depends
  // on more than two arguments

//  template<class Act, class Args, int Code, class Open>
//  struct return_type<lambda_functor_args<action<3, Act>, Args, Code>, Open> {
//    typedef 
//       typename return_type_3_0<
//         Act, 
//         typename return_type<
//            typename detail::tuple_element_as_reference<0, Args>::type, 
//            Open
//         >::type, 
//         typename return_type<
//            typename detail::tuple_element_as_reference<1, Args>::type, 
//            Open
//         >::type,
//         typename return_type<
//            typename detail::tuple_element_as_reference<2, Args>::type, 
//            Open
//         >::type
//       >::type
//    type;
//  };

   
// protect action:
// the return type is the lambda_functor wrapped inside protect
template<class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<1, protect_action>, Args, Code>, Open> {
  typedef typename detail::tuple_element_as_reference<0,Args>::type type;
};

// curry action:
template<class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<3, curry_action<1> >, 
                                       Args, Code>, Open> {
  // take one stored argument type and push it to the open args
  typedef typename 
    return_type<
     typename boost::tuples::element<0,Args>::type, 
     open_args<typename boost::tuples::element<1,Args>::type,
               typename Open::type1, 
               typename Open::type2> >::type
   type;
};

template<class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<4, curry_action<1> >, Args, Code>, Open> {
  // take one stored argument type and push it to the open args
  typedef typename 
    return_type<typename boost::tuples::element<0,Args>::type, 
                open_args<typename boost::tuples::element<1,Args>::type,
                          typename Open::type1, 
                          typename Open::type2> >::type
    type;
};
template<class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<4, curry_action<2> >, Args, Code>, Open> {
  // take two stored arguments type and push them to the open args
  typedef typename 
    return_type<typename boost::tuples::element<0,Args>::type, 
                open_args<typename boost::tuples::element<1,Args>::type,
                          typename boost::tuples::element<2,Args>::type,
                          typename Open::type1> >::type
    type;
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
     typename return_type_1_0<
       Act, 
       typename return_type<
         typename detail::tuple_element_as_reference<0,Args>::type, 
         Open
       >::type
     >::type
  type;
};

// The explicit return type action case, it is unary
template<class RET, class Args, int Code, class Open>
struct return_type<
         lambda_functor_args<
           action<1, explicit_return_type_action<RET> >, 
           Args, 
           Code>, 
         Open> {
  typedef RET type;
};


// return types of control constructs (all return void)
template<class Act, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<1, return_void_action<Act> >, 
                                       Args, Code>, Open >
{ 
  typedef void type; 
};

template<class Act, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<2, return_void_action<Act> >, 
                   Args, Code>, Open >
{ 
  typedef void type; 
};

template<int I, class Act, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<I, return_void_action<Act> >, 
                   Args, Code>, Open >
{ 
  typedef void type; 
};


} // namespace lambda
} // namespace boost

#endif



