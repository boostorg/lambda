// -- Boost Lambda Library -------------------------------------------------

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

// --------------------------------------------------

#ifndef BOOST_LAMBDA_ARITY_CODE_HPP
#define BOOST_LAMBDA_ARITY_CODE_HPP

#include "boost/type_traits/cv_traits.hpp"
#include "boost/type_traits/transform_traits.hpp"

namespace boost { 
namespace lambda {

// These constants state, whether a lambda_functor instantiation results from 
// an expression which contains no placeholders (NONE), 
// only free1 placeholders (FIRST), 
// free2 placeholders and maybe free1 placeholders (SECOND),
// free3 and maybe free1 and free2 placeholders (THIRD),
// freeE placeholders and maybe free1 and free2  (EXCEPTION).
// RETHROW means, that a rethrow expression is used somewhere in the lambda_functor.

enum { NONE		= 0x00, // Notice we are using bits as flags here.
       FIRST		= 0x01, 
       SECOND		= 0x02, 
       THIRD		= 0x04, 
       EXCEPTION	= 0x08, 
       RETHROW		= 0x10};


// -- dig the arity from lambda_functor_args;   
template <class T> struct dig_arity;
   
namespace detail {


template <int Arity, int Step> struct reduce_arity
{
  BOOST_STATIC_CONSTANT(int, value = Arity >> Step);
};

// The implementation template, do not instantiate this directly
template <class Arg> struct dig_arity_ {
  static const int value = NONE;
};


template <class Args> struct dig_arity_<lambda_functor<Args> > {
   static const int value = dig_arity<Args>::value; 
// Args should be always plain, so it would be safe to instantiatie dig_arity_
// To be very sure, we use dig_arity
};

template <class Act, class Args, int ArityCode> 
struct dig_arity_<lambda_functor_args<Act, Args, ArityCode> >{
  static const int value = ArityCode;
};

template <int I> struct dig_arity_<placeholder<I> > {
  static const int value = I;
};

} // namespace detail

// -- dig the arity from lambda_functor_args;
template <class Arg> struct dig_arity {
   static const int value = 
   detail::dig_arity_<
     typename boost::remove_cv<
                typename boost::remove_reference<Arg>::type
              >::type
   >::value;
};
   
   

// compute the arity of a lambda expression (find the highest placeholder)
   
template <class A1 = boost::tuples::null_type, 
          class A2 = boost::tuples::null_type, 
          class A3 = boost::tuples::null_type, 
          class A4 = boost::tuples::null_type, 
          class A5 = boost::tuples::null_type, 
          class A6 = boost::tuples::null_type, 
          class A7 = boost::tuples::null_type, 
          class A8 = boost::tuples::null_type, 
          class A9 = boost::tuples::null_type, 
          class A10 = boost::tuples::null_type> 
struct combine_arities {
  static const int ored_value = 
                 dig_arity<A1>::value |
	         dig_arity<A2>::value | 
                 dig_arity<A3>::value | 
                 dig_arity<A4>::value | 
                 dig_arity<A5>::value | 
                 dig_arity<A6>::value | 
                 dig_arity<A7>::value | 
                 dig_arity<A8>::value | 
                 dig_arity<A9>::value | 
                 dig_arity<A10>::value;

  // leave the highest placeholder bit on, set the lower off
  // EXCEPTION and RETHROW bits are retained as they are
  static const int value = (ored_value & THIRD
	          ? THIRD 
                  : (ored_value & SECOND
                       ? SECOND 
                       : ored_value)) | ( (EXCEPTION | RETHROW) & ored_value);

};


} // namespace lambda
} // namespace boost

#endif
