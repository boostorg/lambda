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
  // causing a compile time error only if the function is really called.

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
struct return_type { 
  typedef Arg type;
};


  // different arities:
template <class Act, class A1> class return_type_1; // 1-ary actions
template <class Act, class A1, class A2> class return_type_2; // 2-ary
template <class Act, class Args> class return_type_N; // >3- ary


// Unary actions (result from unary operators)
// do not have a default return type.
template<class Act, class A> struct return_type_1 { 
   typedef typename 
     detail::return_type_deduction_failure<return_type_1> type;
};



  // read the comments for return_type_2_protect

namespace detail {

template <class A>
class protect_conversion {
  
  // T -> const T
  // T& -> T&
  // const T& -> const T
  // function& -> function&
  // const array& -> const array&
  // lambda functors are not stored as references
  // function reference types are function reference types 
  typedef typename boost::remove_reference<A>::type A1;

public:

  typedef typename detail::IF<
    boost::is_reference<A>::value 
    && !boost::is_const<A1>::value
    && !is_lambda_functor<A1>::value,
    A,  
    typename const_copy_argument<A1>::type // handles funtion and array type correctly
  >::RET type;
};

} // end detail

template <class Act, class A> struct return_type_1_protect {

typedef typename 
  detail::IF<
    is_lambda_functor<A>::value,
    lambda_functor<
      lambda_functor_args< 
        action<1, Act>, 
        tuple<typename detail::protect_conversion<A>::type>,
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
  // We need to make a conservative choise here.
  // The resulting lambda functor stores all const reference arguments as
  // const copies. References to non-const are stored as such.
  // So if the source of the argument is an const open argument, a bound
  // argument stroed as a const reference, or a function returning a 
  // const reference, that information is lost. There is no way of 
  // telling apart 'real const references' from just 'LL internal
  // const references' (or it would be really hard)

  // The return type is a subclass of lambda_functor, which has a converting 
  // copy constructor. It can copy any lambda functor, that has the same 
  // action type and code, and a copy compatible argument tuple.



template <class Act, class A, class B> struct return_type_2_protect {

//    typedef typename boost::remove_reference<A>::type A1;
//    typedef typename boost::remove_reference<B>::type B1;

//    // adding const to a function type fails, these tests are to 
//    // avoid that. Note that only the true branch is instantiated with this IF
//    typedef typename 
//      detail::IF_type<
//        !is_lambda_functor<A1>::value && (boost::is_function<A1>::value || !(boost::is_const<A1>::value)),
//        boost::add_reference<A1>,
//        boost::add_const<A1>
//      >::type A2;

//    typedef typename 
//      detail::IF_type<
//        !is_lambda_functor<B1>::value && (    boost::is_function<B1>::value || !(boost::is_const<B1>::value)), 
//        boost::add_reference<B1>,
//        boost::add_const<B1>
//      >::type B2;


typedef typename 
  detail::IF<
    is_lambda_functor<A>::value || is_lambda_functor<B>::value,
    lambda_functor<
      lambda_functor_args< 
        action<2, Act>, 
        tuple<typename detail::protect_conversion<A>::type, 
              typename detail::protect_conversion<B>::type>, 
        combine_arities<A, B>::value
      >
    >,
    typename return_type_2<Act, A, B>::type
  >::RET type;
};




//  // unary function action (it is binary action)
//  // If a function object overloads operator(), the return type could depend
//  // on the argument types. This is not taken into consideration.
//  template<class A, class B, class Ret> 
//  struct return_type_2<function_action<2, Ret>, A, B> {
//    typedef typename return_type_1<function_action<1, Ret>, A>::type type;
//  };


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
template<class A, class Ret> 
struct return_type_1<function_action<1, Ret>, A > { 
  typedef Ret type;
};
template<class A, class B, class Ret> 
struct return_type_2<function_action<2, Ret>, A, B > { 
  typedef Ret type;
};
template<int I, class Args, class Ret> 
struct return_type_N<function_action<I, Ret>, Args> { 
  typedef Ret type;
};

  // Ret is detail::unspecified, so try to deduce return type
template<class A> 
struct return_type_1<function_action<1, detail::unspecified>, A > { 
  typedef typename function_adaptor_with_actuals<typename tuple<A>::inherited>::type type;
};
template<class A, class B> 
struct return_type_2<function_action<2, detail::unspecified>, A, B > { 
  typedef typename function_adaptor_with_actuals<typename tuple<A, B>::inherited>::type type;
};
template<int I, class Args> 
struct return_type_N<function_action<I, detail::unspecified>, Args > { 
  typedef typename function_adaptor_with_actuals<Args>::type type;
};


namespace detail {

template <class T, class Open>
struct map_to_return_types {
  typedef typename return_type< 
    typename boost::tuples::access_traits<typename T::head_type>::const_type,
    Open
  >::type ret_type;

  // const and reference is added, so that specializations for return_type_1
  // become easier (we can rely on the Args always being references, so the
  // number of specializations doesn't explode.
  // Note! If T is already a reference to nonconst, it will remain that way
  // To return type deduction, const T& is the same as rvalue T 

  typedef typename boost::add_reference<
    typename boost::add_const<ret_type>::type
  >::type ref_to_const_ret_type;

  typedef boost::tuples::cons<
    ref_to_const_ret_type,
    typename map_to_return_types<typename T::tail_type, Open>::type
  > type;
};

template <class Open>
struct map_to_return_types<boost::tuples::null_type, Open> {
  typedef boost::tuples::null_type type;
};
  
} // end detail

// general unary and binary actions
template<class Act, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<1, Act>, Args, Code>, Open> {

  typedef typename return_type<
    typename detail::tuple_element_as_reference<0, Args>::type, 
    Open
  >::type A_type;

  // const and reference is added, so that specializations for return_type_1
  // become easier (we can rely on the Args always being references, so the
  // number of specializations doesn't explode.
  // Note! If T is already a reference to nonconst, it will remain that way
  // To return type deduction, const T& is the same as rvalue T 
  typedef typename boost::add_reference<
    typename boost::add_const<A_type>::type
  >::type refc_A_type;

public:

  typedef typename 
  detail::IF_type<
    detail::is_protectable_action<Act>::value, 
    return_type_1_protect<Act, refc_A_type>,
    return_type_1<Act, refc_A_type>
  >::type type;

};

template<class Act, class Args, int Code, class Open>
class return_type<lambda_functor_args<action<2, Act>, Args, Code>, Open> {

  typedef typename return_type<
    typename detail::tuple_element_as_reference<0, Args>::type, 
    Open
  >::type A_type;

  typedef typename return_type<
    typename detail::tuple_element_as_reference<1, Args>::type, 
    Open
  >::type B_type;

  typedef typename boost::add_reference<
    typename boost::add_const<A_type>::type
  >::type refc_A_type;
  typedef typename boost::add_reference<
    typename boost::add_const<B_type>::type
  >::type refc_B_type;

public:
 typedef typename 
 detail::IF_type<
   detail::is_protectable_action<Act>::value, 
   return_type_2_protect<Act, refc_A_type, refc_B_type>,
   return_type_2<Act, refc_A_type, refc_B_type>
 >::type type;

};

  // This is the general case. Will match any action with arity >= 3
template<int I, class Act, class Args, int Code, class Open>
class return_type<lambda_functor_args<action<I, Act>, Args, Code>, Open> {
  typedef typename detail::map_to_return_types<Args, Open>::type actual_args; 
public:
  typedef typename return_type_N<Act, actual_args>::type type;
};

//  template<class Act, class Args, int Code, class Open>
//  class return_type<lambda_functor_args<action<3, Act>, Args, Code>, Open> {

//    typedef typename return_type<
//      typename detail::tuple_element_as_reference<0, Args>::type, 
//      Open
//    >::type A_type;

//    typedef typename return_type<
//      typename detail::tuple_element_as_reference<1, Args>::type, 
//      Open
//    >::type B_type;

//    typedef typename return_type<
//      typename detail::tuple_element_as_reference<2, Args>::type, 
//      Open
//    >::type C_type;

//    typedef typename boost::add_reference<
//      typename boost::add_const<A_type>::type
//    >::type refc_A_type;
//    typedef typename boost::add_reference<
//      typename boost::add_const<B_type>::type
//    >::type refc_B_type;
//    typedef typename boost::add_reference<
//      typename boost::add_const<C_type>::type
//    >::type refc_C_type;

//  public:
//    // no 3- or higher ary protectable actions exist, no need to check
//    typedef typename return_type_3<Act, refc_A_type, refc_B_type, refc_C_type>::type type;
//  };

//    // 4 args or more (must be a function action)
//  template<int I, class Act, class Args, int Code, class Open>
//  class return_type<lambda_functor_args<action<I, Act>, Args, Code>, Open> {

//    typedef typename return_type<
//      typename detail::tuple_element_as_reference<0, Args>::type, 
//      Open
//    >::type A_type;

//    typedef typename return_type<
//      typename detail::tuple_element_as_reference<1, Args>::type, 
//      Open
//    >::type B_type;

//    typedef typename return_type<
//      typename detail::tuple_element_as_reference<2, Args>::type, 
//      Open
//    >::type C_type;

//    typedef typename return_type<
//      typename detail::tuple_element_as_reference<3, Args>::type, 
//      Open
//    >::type D_type;

//    typedef typename boost::add_reference<
//      typename boost::add_const<A_type>::type
//    >::type refc_A_type;
//    typedef typename boost::add_reference<
//      typename boost::add_const<B_type>::type
//    >::type refc_B_type;
//    typedef typename boost::add_reference<
//      typename boost::add_const<C_type>::type
//    >::type refc_C_type;
//    typedef typename boost::add_reference<
//      typename boost::add_const<D_type>::type
//    >::type refc_D_type;

//  public:
//    typedef typename return_type_4<Act, refc_A_type, refc_B_type, refc_C_type, refc_D_type>::type type;
//  };



// special case for comma action:
// As the return type needs to be exactly the type of the rightmost argument, 
// we cannot add a const and reference (we need to preserve rvalueness)
// note, that return_type_2_protect is still called, so user can overload
// return_type_2 for user defined types.

template<class Args, int Code, class Open>
class return_type<lambda_functor_args<action<2, other_action<comma_action> >, Args, Code>, Open> {

  typedef typename return_type<
    typename detail::tuple_element_as_reference<0, Args>::type, 
    Open
  >::type A_type;

  typedef typename return_type<
    typename detail::tuple_element_as_reference<1, Args>::type, 
    Open
  >::type B_type;

public:
  typedef typename 
    return_type_2_protect<other_action<comma_action>, A_type, B_type>::type type;
};
   
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




   
//  // 3 arguments or more ---------------------------------------------
//  // this must be a function_action. Note that the previous unary and binary 
//  // specalisations take care of nullary and unary function adaptors, that is,
//  // unary and binary actions.
//  // Since function_actions determine the return type based on the function
//  // object only, we can ignore the arguments and reuse return_type_1.

//  template <int I, class Act, class Args, int Code, class Open>
//  class return_type<lambda_functor_args<action<I, Act>, Args, Code>, Open> {

//    typedef typename return_type<
//      typename detail::tuple_element_as_reference<0, Args>::type, 
//      Open
//    >::type A_type;

//    // reference is added, so that specializations for return_type_1
//    // become easier. 
//    typedef typename boost::add_reference<
//      typename boost::add_const<A_type>::type
//    >::type refc_A_type;

//  public:

//   typedef typename return_type_1_protect<Act, refc_A_type>::type type;
//  };

// The explicit return type action case, it is unary
template<class RET, class Args, int Code, class Open>
struct return_type<
         lambda_functor_args<
           action<1, explicit_return_type_action<RET> >, 
           Args, 
           Code>, 
         Open> 
{
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

template<class Act, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<3, return_void_action<Act> >, 
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



