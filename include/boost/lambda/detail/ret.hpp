// Boost Lambda Library  ret.hpp -----------------------------------------

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


#ifndef BOOST_LAMBDA_RET_HPP
#define BOOST_LAMBDA_RET_HPP

namespace boost { 
namespace lambda {

// -- ret -------------------------
// the explicit return type template 
template<class RET, class Arg>
inline const 
lambda_functor<
  lambda_functor_args<
    action<1, explicit_return_type_action<RET> >, 
    tuple<lambda_functor<Arg> >,
    dig_arity<Arg>::value
  > 
>
ret(const lambda_functor<Arg>& a1)
{
  return lambda_functor<
           lambda_functor_args<
             action<1, explicit_return_type_action<RET> >, 
             tuple<lambda_functor<Arg> >,
             dig_arity<Arg>::value
           > 
         >
         (tuple<lambda_functor<Arg> >(a1));
}

// protect ------------------

  // protecting others than lambda functors has no effect
template <class T>
inline const T& protect(const T& t) { return t; }

template<class Arg>
inline const 
lambda_functor<
  lambda_functor_args<
    action<1, protect_action>, 
    tuple<lambda_functor<Arg> >,
    NONE
  > 
>
protect(const lambda_functor<Arg>& a1)
{
  return lambda_functor<
      lambda_functor_args<
        action<1, protect_action>, 
        tuple<lambda_functor<Arg> >,
        NONE
      > 
    >
    (tuple<lambda_functor<Arg> >(a1));
}
   
// -- identity -------------------------
// identity templates
template<class Arg>
inline const 
lambda_functor<
  lambda_functor_args<
    action<1, other_action<identity_action> >, 
    tuple<typename const_copy_argument<const Arg>::type>, 
    NONE> >
constant(const Arg& a)
{
  return 
    lambda_functor<
      lambda_functor_args<
        action<1, other_action<identity_action> >, 
        tuple<typename const_copy_argument<const Arg>::type>,
        NONE
      > 
    > (tuple<typename const_copy_argument<const Arg>::type>(a));
}

// since typedef's can't take template arguments, 
// I made this struct so you can use
// constant_type<TYPE>::type constant_name(constant(value)); (GWP)

template<class Arg>
class constant_type {
public:
  typedef const 
    lambda_functor<
      lambda_functor_args<
        action<1, other_action<identity_action> >, 
        tuple<typename const_copy_argument<const Arg>::type>, 
	NONE
      > 
    > type;
};


template<class Arg>
inline const 
lambda_functor<
  lambda_functor_args<
    action<1, other_action<identity_action> >, 
    tuple<typename reference_argument<Arg>::type>, 
    NONE
  > 
>
var(Arg& a)
{
  return 
    lambda_functor<
      lambda_functor_args<
         action<1, other_action<identity_action> >, 
         tuple<typename reference_argument<Arg>::type>,
         NONE
      > 
    > (tuple<typename reference_argument<Arg>::type>(a));
}

// since typedef's can't take template arguments, I made this struct so 
// you can use var_type<TYPE>::type var_name(var(i)); (GWP)

template<class Arg>
class var_type {
public:
  typedef 
    lambda_functor<
       lambda_functor_args<
         action<1, other_action<identity_action> >, 
         tuple<typename reference_argument<Arg>::type>, 
         NONE
       > 
     > type;
};


// -------------------------------------------------------------------

// Hides the lambda functorness of a lambda functor. 
// After this, the functor is immune to argument substitution, etc.
// This can be used, e.g. to make it safe to pass lambda functors as 
// arguments to functions, which might use them as target functions

// note, unlambda and protect are different things. Protect hides the lambda
// functor for one application, unlambda for good.

template <class Arg>
class non_lambda_functor {
  lambda_functor<Arg> lf; // a lambda functor
public:

  // This functor defines the result_type typedef.
  // The result type must be deducible without knowing the arguments

  // TODO: check that passing unspecified as open args fails 
  typedef typename 
    return_type<Arg, 
                open_args<detail::unspecified, 
                          detail::unspecified, 
                          detail::unspecified> >::type 
      result_type;

  non_lambda_functor(const lambda_functor<Arg>& a) : lf(a) {}

  result_type operator()() const {
    return lf.template ret_call<result_type>(); 
  }

  template<class A>
  result_type operator()(A& a) const {
    return lf.template ret_call<result_type>(a); 
  }

  template<class A, class B>
  result_type operator()(A& a, B& b) const {
    return lf.template ret_call<result_type>(a, b); 
  }

  template<class A, class B, class C>
  result_type operator()(A& a, B& b, C& c) const {
    return lf.template ret_call<result_type>(a, b, c); 
  }
};

template <class Arg>
inline const Arg& unlambda(const Arg& a) { return a; }

template <class Arg>
inline const non_lambda_functor<Arg> unlambda(const lambda_functor<Arg>& a)
{
  return non_lambda_functor<Arg>(a);
};

  // Due to a language restriction, lambda functors cannot be made to
  // accept non-const rvalue arguments. Usually iterators do not return 
  // temporaries, but sometimes they do. That's why a workaround is provided.
  // Note, that this potentially breaks const correctness, so be careful!

template <class Arg>
inline const const_incorrect_lambda_functor<Arg> 
break_const(const lambda_functor<Arg>& lf)
{
  return const_incorrect_lambda_functor<Arg>(lf);
}  
   
} // namespace lambda 
} // namespace boost

#endif

