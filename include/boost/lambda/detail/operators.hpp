// Boost Lambda Library - operators.hpp --------------------------------------

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

// ---------------------------------------------------------------

#ifndef BOOST_LAMBDA_BINARY_EXPRESSIONS_HPP
#define BOOST_LAMBDA_BINARY_EXPRESSIONS_HPP

#include "boost/lambda/detail/is_instance_of.hpp"

namespace boost { 
namespace lambda {

#if defined BOOST_LAMBDA_BINARY_EXPRESSION1
#error "Multiple defines of BOOST_LAMBDA_BINARY_EXPRESSION1"
#endif

#define BOOST_LAMBDA_BINARY_EXPRESSION1(OPER_FUNC_NAME, OPER_NAME, CONSTA, CONSTB, CONST_CONVERSION) template<class Arg, class B> \
inline const lambda_functor<lambda_functor_args<action<2, OPER_NAME >, \
                          tuple<lambda_functor<Arg>, \
                                typename CONST_CONVERSION <CONSTB B>::type>,\
                          dig_arity<Arg>::value> >\
OPER_FUNC_NAME (const lambda_functor<Arg>& a, \
                        CONSTB B& b)\
{\
  return lambda_functor<lambda_functor_args<action<2, OPER_NAME >, \
                            tuple<lambda_functor<Arg>, typename CONST_CONVERSION <CONSTB B>::type>, \
                            dig_arity<Arg>::value> >\
    (\
      tuple<lambda_functor<Arg>, typename CONST_CONVERSION <CONSTB B>::type>(a, b)\
    );\
}\
\

#if defined BOOST_LAMBDA_BINARY_EXPRESSION2
#error "Multiple defines of BOOST_LAMBDA_BINARY_EXPRESSION2"
#endif

#define BOOST_LAMBDA_BINARY_EXPRESSION2(OPER_FUNC_NAME, OPER_NAME, CONSTA, CONSTB, CONST_CONVERSION) template<class A, class Arg> \
inline const lambda_functor<lambda_functor_args<action<2, OPER_NAME >,\
                          tuple<typename CONST_CONVERSION <CONSTA A>::type, \
                                lambda_functor<Arg> >,\
                          dig_arity<Arg>::value> >\
OPER_FUNC_NAME (CONSTA A& a,\
                        const lambda_functor<Arg>& b)\
{\
  return lambda_functor<lambda_functor_args<action<2, OPER_NAME >, \
                            tuple<typename CONST_CONVERSION <CONSTA A>::type, lambda_functor<Arg> >, \
                            dig_arity<Arg>::value> >\
    (\
      tuple<typename CONST_CONVERSION <CONSTA A>::type, lambda_functor<Arg> >(a, b)\
    );\
}\
\

#if defined BOOST_LAMBDA_BINARY_EXPRESSION3
#error "Multiple defines of BOOST_LAMBDA_BINARY_EXPRESSION3"
#endif

#define BOOST_LAMBDA_BINARY_EXPRESSION3(OPER_FUNC_NAME, OPER_NAME, CONSTA, CONSTB, CONST_CONVERSION) template<class ArgA, class ArgB> \
inline const lambda_functor<lambda_functor_args<action<2, OPER_NAME >,\
                                tuple<lambda_functor<ArgA>, \
                                      lambda_functor<ArgB> >,\
                                combine_arities<ArgA, ArgB>::value> >\
OPER_FUNC_NAME (const lambda_functor<ArgA>& a, \
                        const lambda_functor<ArgB>& b)\
{\
  return lambda_functor<lambda_functor_args<action<2, OPER_NAME >, \
                            tuple<lambda_functor<ArgA>, \
                                  lambda_functor<ArgB> >,\
                            combine_arities<ArgA, ArgB>::value> >\
    (\
       boost::make_tuple(a, b)\
    );\
}\
\

#if defined BOOST_LAMBDA_BINARY_EXPRESSION
#error "Multiple defines of BOOST_LAMBDA_BINARY_EXPRESSION"
#endif

#define BOOST_LAMBDA_BINARY_EXPRESSION(OPER_FUNC_NAME, OPER_NAME, CONSTA, CONSTB, CONST_CONVERSION) \
BOOST_LAMBDA_BINARY_EXPRESSION1(OPER_FUNC_NAME, OPER_NAME, CONSTA, CONSTB, CONST_CONVERSION)\
BOOST_LAMBDA_BINARY_EXPRESSION2(OPER_FUNC_NAME, OPER_NAME, CONSTA, CONSTB, CONST_CONVERSION)\
BOOST_LAMBDA_BINARY_EXPRESSION3(OPER_FUNC_NAME, OPER_NAME, CONSTA, CONSTB, CONST_CONVERSION)


BOOST_LAMBDA_BINARY_EXPRESSION(operator+, arithmetic_action< plus_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator-, arithmetic_action< minus_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator*, arithmetic_action< multiply_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator/, arithmetic_action< divide_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator%, arithmetic_action< remainder_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator<<, bitwise_action< leftshift_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator>>, bitwise_action< rightshift_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator&, bitwise_action< and_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator|, bitwise_action< or_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator^, bitwise_action< xor_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator&&, logical_action< and_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator||, logical_action< or_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator<, relational_action< less_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator>, relational_action< greater_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator<=, relational_action< lessorequal_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator>=, relational_action< greaterorequal_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator==, relational_action< equal_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator!=, relational_action< notequal_action>, const, const, const_copy_argument)

BOOST_LAMBDA_BINARY_EXPRESSION(operator+=, arithmetic_assignment_action< plus_action>, , const, reference_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator-=, arithmetic_assignment_action< minus_action>, , const, reference_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator*=, arithmetic_assignment_action< multiply_action>, , const, reference_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator/=, arithmetic_assignment_action< divide_action>, , const, reference_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator%=, arithmetic_assignment_action< remainder_action>, , const, reference_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator<<=, bitwise_assignment_action< leftshift_action>, , const, reference_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator>>=, bitwise_assignment_action< rightshift_action>, , const, reference_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator&=, bitwise_assignment_action< and_action>, , const, reference_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator|=, bitwise_assignment_action< or_action>, , const, reference_argument)
BOOST_LAMBDA_BINARY_EXPRESSION(operator^=, bitwise_assignment_action< xor_action>, , const, reference_argument)


// A special trick for comma operator for correct preprocessing
#if defined BOOST_LAMBDA_COMMA_OPERATOR_NAME
#error "Multiple defines of BOOST_LAMBDA_COMMA_OPERATOR_NAME"
#endif

#define BOOST_LAMBDA_COMMA_OPERATOR_NAME operator,

BOOST_LAMBDA_BINARY_EXPRESSION1(BOOST_LAMBDA_COMMA_OPERATOR_NAME, other_action< comma_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION2(BOOST_LAMBDA_COMMA_OPERATOR_NAME, other_action< comma_action>, const, const, const_copy_argument)
BOOST_LAMBDA_BINARY_EXPRESSION3(BOOST_LAMBDA_COMMA_OPERATOR_NAME, other_action< comma_action>, const, const, const_copy_argument)



namespace detail {

// special cases for ostream& << Any and istream& >> Any ---------------
// the actual stream classes may vary and thus a specialisation for, 
// say ostream& does not match (the general case above is chosen). 
// Therefore we specialise for non-const reference:
// if the left argument is a stream, we store the stream as reference
// if it is something else, we store a const plain by default

// Note that the overloading is const vs. non-const first argument

#ifdef BOOST_NO_TEMPLATED_STREAMS
template<class T> struct convert_ostream_to_ref_others_to_c_plain_by_default {
  typedef typename detail::IF<
                       boost::is_convertible<T*, std::ostream*>::value,
                       T&,
                       typename const_copy_argument <T>::type
                     >::RET type;
};

template<class T> struct convert_istream_to_ref_others_to_c_plain_by_default {
  typedef typename detail::IF<
                       boost::is_convertible<T*, std::istream*>::value,
                       T&,
                       typename const_copy_argument <T>::type
                     >::RET type;
};
#else

template<class T> struct convert_ostream_to_ref_others_to_c_plain_by_default {
  typedef typename detail::IF<
                       is_instance_of_2<
                         T, std::basic_ostream
                       >::value,
                       T&,
                       typename const_copy_argument <T>::type
                     >::RET type;
};

template<class T> struct convert_istream_to_ref_others_to_c_plain_by_default {
  typedef typename detail::IF<
                       is_instance_of_2<
                         T, std::basic_istream
                       >::value,
                       T&,
                       typename const_copy_argument <T>::type
                     >::RET type;
};
#endif

} // detail

BOOST_LAMBDA_BINARY_EXPRESSION2(operator<<, bitwise_action< leftshift_action>, , const, detail::convert_ostream_to_ref_others_to_c_plain_by_default)
BOOST_LAMBDA_BINARY_EXPRESSION2(operator>>, bitwise_action< rightshift_action>, , const, detail::convert_istream_to_ref_others_to_c_plain_by_default)      


// special case for io_manipulators.
// function references cannot be given as arguments to lambda operator
// expressions in general. With << and >> the use of manipulators is
// so common, that specializations are provided to make them work.

template<class Arg, class Ret, class ManipArg>
inline const 
lambda_functor<
  lambda_functor_args<
    action<2, bitwise_action<leftshift_action> >,
    tuple<lambda_functor<Arg>, Ret(&)(ManipArg)>,
    dig_arity<Arg>::value
  > 
>
operator<<(const lambda_functor<Arg>& a, Ret(&b)(ManipArg))
{
  return 
    lambda_functor<
      lambda_functor_args<
        action<2, bitwise_action<leftshift_action> >,
        tuple<lambda_functor<Arg>, Ret(&)(ManipArg)>,
        dig_arity<Arg>::value
      > 
    > ( tuple<lambda_functor<Arg>, Ret(&)(ManipArg)>(a, b) );
}

template<class Arg, class Ret, class ManipArg>
inline const 
lambda_functor<
  lambda_functor_args<
    action<2, bitwise_action<rightshift_action> >,
    tuple<lambda_functor<Arg>, Ret(&)(ManipArg)>,
    dig_arity<Arg>::value
  > 
>
operator>>(const lambda_functor<Arg>& a, Ret(&b)(ManipArg))
{
  return 
    lambda_functor<
      lambda_functor_args<
        action<2, bitwise_action<rightshift_action> >,
        tuple<lambda_functor<Arg>, Ret(&)(ManipArg)>,
        dig_arity<Arg>::value
      > 
    > ( tuple<lambda_functor<Arg>, Ret(&)(ManipArg)>(a, b) );
}


// (+ and -) take their arguments as const references. 
// This has consquences with pointer artihmetic
// E.g int a[]; ... *a = 1 works but not *(a+1) = 1. 
// the result of a+1 would be const
// To make the latter work too, 
// non-const arrays are taken as non-const and stored as non-const as well.
#if defined  BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION1
#error "Multiple defines of  BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION1"
#endif

#define BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION1(OPER_FUNC_NAME, OPER_NAME, CONST) template<class Arg, int N, class B> \
inline const lambda_functor<lambda_functor_args<action<2, OPER_NAME >, \
                          tuple<lambda_functor<Arg>, \
                          CONST B (&) [N]>,\
                          dig_arity<Arg>::value> > \
OPER_FUNC_NAME (const lambda_functor<Arg>& a, \
                      CONST B (&b) [N])\
{\
  return lambda_functor<lambda_functor_args<action<2, OPER_NAME >, \
                            tuple<lambda_functor<Arg>, CONST B (&) [N]>, \
                            dig_arity<Arg>::value> >\
    (\
      tuple<lambda_functor<Arg>, CONST B (&) [N]>(a, b)\
    );\
}\
\

#if defined  BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION2
#error "Multiple defines of  BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION2"
#endif

#define BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION2(OPER_FUNC_NAME, OPER_NAME, CONST) template<int N, class A, class Arg> \
inline const lambda_functor<lambda_functor_args<action<2, OPER_NAME >, \
                          tuple<CONST A (&) [N], lambda_functor<Arg> >, \
                          dig_arity<Arg>::value> > \
OPER_FUNC_NAME (CONST A (&a) [N], const lambda_functor<Arg>& b) \
{\
  return lambda_functor<lambda_functor_args<action<2, OPER_NAME >, \
                            tuple<CONST A (&) [N], lambda_functor<Arg> >, \
                            dig_arity<Arg>::value> >\
    (\
      tuple<CONST A (&) [N], lambda_functor<Arg> >(a, b)\
    );\
}\
\

BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION1(operator+, arithmetic_action< plus_action>,)
BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION2(operator+, arithmetic_action< plus_action>,)
BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION1(operator+, arithmetic_action< plus_action>,const)
BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION2(operator+, arithmetic_action< plus_action>,const)


//BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION1(operator-, arithmetic_action<minus_action>)
// This is not needed, since the result of ptr-ptr is an rvalue anyway

BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION2(operator-, arithmetic_action< minus_action>, )
BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION2(operator-, arithmetic_action< minus_action>, const)


#undef BOOST_LAMBDA_BINARY_EXPRESSION1
#undef BOOST_LAMBDA_BINARY_EXPRESSION2
#undef BOOST_LAMBDA_BINARY_EXPRESSION3
#undef BOOST_LAMBDA_BINARY_EXPRESSION
#undef BOOST_LAMBDA_COMMA_OPERATOR_NAME

#undef BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION1
#undef BOOST_LAMBDA_PTR_ARITHMETIC_EXPRESSION2


// ---------------------------------------------------------------------
// unary operators -----------------------------------------------------
// ---------------------------------------------------------------------

#if defined BOOST_LAMBDA_UNARY_EXPRESSION
#error "Multiple defines of BOOST_LAMBDA_UNARY_EXPRESSION"
#endif

#define BOOST_LAMBDA_UNARY_EXPRESSION(FUNCTION_NAME, ACTION_NAME) \
template<class Arg>\
inline const lambda_functor<lambda_functor_args<action<1, ACTION_NAME >,\
                                tuple<lambda_functor<Arg> >,\
                                dig_arity<Arg>::value> >\
FUNCTION_NAME (const lambda_functor<Arg>& a)\
{\
  return lambda_functor<lambda_functor_args<action<1, ACTION_NAME >,\
                            tuple<lambda_functor<Arg> >,\
                            dig_arity<Arg>::value> >\
    ( make_tuple(a) );\
}\
\

BOOST_LAMBDA_UNARY_EXPRESSION(operator+, unary_arithmetic_action<plus_action>)
BOOST_LAMBDA_UNARY_EXPRESSION(operator-, unary_arithmetic_action<minus_action>)
BOOST_LAMBDA_UNARY_EXPRESSION(operator~, bitwise_action<not_action>)
BOOST_LAMBDA_UNARY_EXPRESSION(operator!, logical_action<not_action>)
BOOST_LAMBDA_UNARY_EXPRESSION(operator++, pre_increment_decrement_action<increment_action>)
BOOST_LAMBDA_UNARY_EXPRESSION(operator--, pre_increment_decrement_action<decrement_action>)
BOOST_LAMBDA_UNARY_EXPRESSION(operator*, other_action<contentsof_action>)
BOOST_LAMBDA_UNARY_EXPRESSION(operator&, other_action<addressof_action>)

#if defined BOOST_LAMBDA_POSTFIX_UNARY_EXPRESSION
#error "Multiple defines of BOOST_LAMBDA_POSTFIX_UNARY_EXPRESSION"
#endif

#define BOOST_LAMBDA_POSTFIX_UNARY_EXPRESSION(FUNCTION_NAME, ACTION_NAME) \
template<class Arg>\
inline const lambda_functor<lambda_functor_args<action<1, ACTION_NAME >,\
                                tuple<lambda_functor<Arg> >,\
                                dig_arity<Arg>::value> >\
FUNCTION_NAME (const lambda_functor<Arg>& a, int)\
{\
  return lambda_functor<lambda_functor_args<action<1, ACTION_NAME >,\
                            tuple<lambda_functor<Arg> >,\
                            dig_arity<Arg>::value> >\
    ( make_tuple(a) );\
}\
\

BOOST_LAMBDA_POSTFIX_UNARY_EXPRESSION(operator++, post_increment_decrement_action<increment_action>)
BOOST_LAMBDA_POSTFIX_UNARY_EXPRESSION(operator--, post_increment_decrement_action<decrement_action>)

#undef BOOST_LAMBDA_UNARY_EXPRESSION
#undef BOOST_LAMBDA_POSTFIX_UNARY_EXPRESSION

} // namespace lambda
} // namespace boost

#endif
