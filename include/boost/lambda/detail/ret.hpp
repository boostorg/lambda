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

   
} // namespace lambda 
} // namespace boost

#endif
