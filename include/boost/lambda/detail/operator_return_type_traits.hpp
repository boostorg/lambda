//  operator_return_type_traits.hpp -- Boost Lambda Library ------------------

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

#ifndef BOOST_LAMBDA_OPERATOR_RETURN_TYPE_TRAITS_HPP
#define BOOST_LAMBDA_OPERATOR_RETURN_TYPE_TRAITS_HPP

#include "boost/type_traits/same_traits.hpp"

#include <cstddef> // needed for the ptrdiff_t
#include <iosfwd>  // for istream and ostream

namespace boost { 
namespace lambda {
namespace detail {

// -- general helper templates for type deduction ------------------

// Much of the type deduction code for standard arithmetic types from Gary Powell

template <class A> struct promote_code { static const int value = -1; };
// this means that a code is not defined for A

// -- the next 5 types are needed in if_then_else_return 
// the promotion order is not important, but they must have distinct values.
template <> struct promote_code<bool> { static const int value = 10; };
template <> struct promote_code<char> { static const int value = 20; };
template <> struct promote_code<unsigned char> { static const int value = 30; };
template <> struct promote_code<signed char> { static const int value = 40; };
template <> struct promote_code<short int> { static const int value = 50; };
// ----------

template <> struct promote_code<int> { static const int value = 100; };
template <> struct promote_code<unsigned int> { static const int value = 200; };
template <> struct promote_code<long> { static const int value = 300; };
template <> struct promote_code<unsigned long> { static const int value = 400; };

template <> struct promote_code<float> { static const int value = 500; };
template <> struct promote_code<double> { static const int value = 600; };
template <> struct promote_code<long double> { static const int value = 700; };

// TODO: wchar_t

// forward delcaration of complex.

} // namespace detail
} // namespace lambda 
} // namespace boost

namespace std {
  template<class T> class complex;
}

namespace boost { 
namespace lambda {
namespace detail {

template <> struct promote_code< std::complex<float> > { static const int value = 800; };
template <> struct promote_code< std::complex<double> > { static const int value = 900; };
template <> struct promote_code< std::complex<long double> > { static const int value = 1000; };

// -- int promotion -------------------------------------------
template <class T> struct promote_to_int { typedef T type; };

template <> struct promote_to_int<bool> { typedef int type; };
template <> struct promote_to_int<char> { typedef int type; };
template <> struct promote_to_int<unsigned char> { typedef int type; };
template <> struct promote_to_int<signed char> { typedef int type; };
template <> struct promote_to_int<short int> { typedef int type; };

// The unsigned short int promotion rule is this:
// unsigned short int to signed int if a signed int can hold all values 
// of unsigned short int, otherwise go to unsigned int.
template <> struct promote_to_int<unsigned short int>
{ 
	typedef
		detail::IF<sizeof(int) <= sizeof(unsigned short int),	
// I had the logic reversed but ">" messes up the parsing.
		unsigned int,
		int>::RET type; 
};


// TODO: think, should there be default behaviour for non-standard types?

} // namespace detail

// ------------------------------------------ 
// Unary actions ----------------------------
// ------------------------------------------ 

template<class Act, class A> 
struct return_type_1<unary_arithmetic_action<Act>, A> { 
  typedef typename boost::remove_reference<A>::type type; 
};

// bitwise not, operator~()
template<class A> struct return_type_1<bitwise_action<not_action>, A> { 
  typedef typename boost::remove_reference<A>::type type; 
};

// identity_action
template<class A> struct return_type_1<other_action<identity_action>, A> { 
  typedef A type;
};


// prefix increment and decrement operators return their operand type as such
// it should be a reference
template<class Act, class A> 
struct return_type_1<pre_increment_decrement_action<Act>, A> {
  BOOST_STATIC_ASSERT(boost::is_reference<A>::value);
  typedef A type;
};

// post decrement just returns the same plain stype.
template<class Act, class A> 
struct return_type_1<post_increment_decrement_action<Act>, A> 
{ 
  typedef typename boost::remove_reference<A>::type type; 
};

// logical not, operator!()
template<class A>
struct return_type_1<logical_action<not_action>, A> {
  typedef bool type;
};

// address of action ---------------------------------------
// Note that this applies to all types. 
// A special user defined & may need to define its own
// specializations
template<class A> 
struct return_type_1<other_action<addressof_action>, A> { 
  typedef typename boost::remove_reference<A>::type*  type; 
};

// contentsof action ------------------------------------

// default is to assume that a typedef reference exists.
// This works with std::iterators.
template<class A> 
struct return_type_1<other_action<contentsof_action>, A> { 
  typedef typename A::reference type; 
};

// strip reference
template<class A>
struct return_type_1<other_action<contentsof_action>, A&> {
  typedef typename 
   return_type_1<other_action<contentsof_action>, A>::type type;
};

// strip constness, but preserve it 
template<class A> 
struct return_type_1<other_action<contentsof_action>, const A> { 
  // get the (potentially non-const) reference type
  typedef typename 
    return_type_1<other_action<contentsof_action>, A>::type type1;
  // return a reference to the underlying const type
  // the IF is because the A::reference in the primary template could
  // (in theory) be some class type rather than a real reference, hence
  // we do not want to make it a reference here either
  typename detail::IF<
    is_reference<type1>::value, 
    const typename boost::remove_reference<type1>::type &,
    const type1
  >::RET type;
};

template<class A> 
struct return_type_1<other_action<contentsof_action>, A*> { typedef A& type; };

// the pointers itself can be const, this const may safely be dropped
template<class A> 
struct return_type_1<other_action<contentsof_action>, A* const> { 
  typedef A& type; 
};

// for arrays, no need to specialise for const, if A is const, 
// the general const strips const away and puts it back (as it should)
template<class A, int N> 
struct return_type_1<other_action<contentsof_action>, A[N]> { typedef A& type; };


// ------------------------------------------------------------------
// binary actions ---------------------------------------------------
// ------------------------------------------------------------------

// error classes
class illegal_pointer_arithmetic{};
class type_deduction_did_not_succeed{};

namespace detail {
// pointer arithmetic type deductions ----------------------
// value = false means that this is not a pointer arithmetic case
// value = true means, that this can be a pointer arithmetic case, but not necessarily is
// This means, that for user defined operators for pointer types, say for some operator+(X, *Y),
// the deductions must be coded at an earliel level (return_type_2).

template<class Act, class A, class B> 
struct pointer_arithmetic_traits { static const bool value = false; };

template<class A, class B> 
struct pointer_arithmetic_traits<plus_action, A, B> { 

  typedef typename 
    array_to_pointer<typename boost::remove_reference<A>::type>::type AP;
  typedef typename 
    array_to_pointer<typename boost::remove_reference<B>::type>::type BP;

  static const bool is_pointer_A = boost::is_pointer<AP>::value;
  static const bool is_pointer_B = boost::is_pointer<BP>::value;  

  static const bool value = is_pointer_A || is_pointer_B;

  // can't add two pointers.
  // note, that we do not check wether the other type is valid for 
  // addition with a pointer.
  // the compiler will catch it in the apply function
  // TODO: make the code fail immediately (use inner IF instead of the
  // illegal_pointer_arithmetic class
  typedef typename 
  detail::IF<is_pointer_A && is_pointer_B, illegal_pointer_arithmetic,
    typename detail::IF<is_pointer_A, const AP, const BP>::RET
  >::RET type; 

};

template<class A, class B> 
struct pointer_arithmetic_traits<minus_action, A, B> { 
  typedef typename 
    array_to_pointer<typename boost::remove_reference<A>::type>::type AP;
  typedef typename 
    array_to_pointer<typename boost::remove_reference<B>::type>::type BP;

  static const bool is_pointer_A = boost::is_pointer<AP>::value;
  static const bool is_pointer_B = boost::is_pointer<BP>::value;  

  static const bool value = is_pointer_A || is_pointer_B;

  static const bool same_pointer_type =
    is_pointer_A && is_pointer_B && 
    boost::is_same<
      typename boost::remove_const<
        typename boost::remove_pointer<
          typename boost::remove_const<AP>::type
        >::type
      >::type,
      typename boost::remove_const<
        typename boost::remove_pointer<
          typename boost::remove_const<BP>::type
        >::type
      >::type
    >::value;

  // ptr - ptr has type ptrdiff_t
  // note, that we do not check if, in ptr - B, B is 
  // valid for subtraction with a pointer.
  // the compiler will catch it in the apply function
  // TODO: make the inner IF's false part fail immediately, rather than using
  // illegal_pointer_artithmetic type
  typedef typename 
  detail::IF<
    same_pointer_type, const std::ptrdiff_t,
    typename detail::IF<
      is_pointer_A, 
      const AP, 
      illegal_pointer_arithmetic
    >::RET
  >::RET type; 
};

} // namespace detail
   
// -- arithmetic actions ---------------------------------------------

namespace detail {
   
template<bool is_pointer_arithmetic, class Act, class A, class B> 
struct return_type_2_arithmetic_phase_1;

template<class A, class B> struct return_type_2_arithmetic_phase_2;
template<class A, class B> struct return_type_2_arithmetic_phase_3;

} // namespace detail
   
// drop any qualifiers from the argument types within arithmetic_action
template<class A, class B, class Act> 
struct return_type_2<arithmetic_action<Act>, A, B>
{
    typedef typename
      detail::return_type_2_arithmetic_phase_1<
         detail::pointer_arithmetic_traits<Act, A, B>::value, Act, A, B
      >::type type;
};

namespace detail {
   
// perform integral promotion, no pointer arithmetic
template<bool is_pointer_arithmetic, class Act, class A, class B> 
struct return_type_2_arithmetic_phase_1
{
  typedef typename 
    return_type_2_arithmetic_phase_2<
      typename remove_reference_and_cv<A>::type,
      typename remove_reference_and_cv<B>::type
    >::type type;
};

// pointer_arithmetic
template<class Act, class A, class B> 
struct return_type_2_arithmetic_phase_1<true, Act, A, B>
{
  typedef typename 
    pointer_arithmetic_traits<Act, A, B>::type type;
};

template<class A, class B>
struct return_type_2_arithmetic_phase_2 {
  typedef typename
    return_type_2_arithmetic_phase_3<
      typename promote_to_int<A>::type, 
      typename promote_to_int<B>::type
    >::type type;
};

// specialization for unsigned int.
// We only have to do these two specialization because the value promotion will
// take care of the other cases.
// The unsigned int promotion rule is this:
// unsigned int to long if a long can hold all values of unsigned int,
// otherwise go to unsigned long.

// struct so I don't have to type this twice.
struct promotion_of_unsigned_int
{
	typedef
	detail::IF<sizeof(long) <= sizeof(unsigned int),	
// I had the logic reversed but ">" messes up the parsing.
		unsigned long,
		long>::RET type; 
};

template<>
struct return_type_2_arithmetic_phase_2<unsigned int, long>
{
	typedef promotion_of_unsigned_int::type type;
};
template<>
struct return_type_2_arithmetic_phase_2<long, unsigned int>
{
	typedef promotion_of_unsigned_int::type type;
};


template<class A, class B> struct return_type_2_arithmetic_phase_3 { 
   enum { promote_code_A_value = promote_code<A>::value,
         promote_code_B_value = promote_code<B>::value }; // enums for KCC
  typedef typename
    detail::IF<
      promote_code_A_value == -1 || promote_code_B_value == -1,
      type_deduction_did_not_succeed,
      typename detail::IF<
        ((int)promote_code_A_value > (int)promote_code_B_value), 
        A, 
        B
      >::RET
    >::RET type;                    
};

} // namespace detail

// --  bitwise actions -------------------------------------------
// note: for integral types deuduction is similar to arithmetic actions. 

// drop any qualifiers from the argument types within arithmetic action
template<class A, class B, class Act> 
struct return_type_2<bitwise_action<Act>, A, B>
{
  // bitwise operators not defined for floating point types
  BOOST_STATIC_ASSERT(boost::is_integral<typename boost::remove_reference<A>::type>::value && boost::is_integral<typename boost::remove_reference<B>::type>::value);
  typedef typename return_type_2<arithmetic_action<plus_action>, A, B >::type type; 
  // plus_action is just a random pick, has to be a concrete instance
};

// TODO: templated streams
// ostream
template<class A, class B> 
struct return_type_2<bitwise_action<leftshift_action>, A, B>
{
  typedef typename detail::IF<
    boost::is_convertible<
      typename boost::remove_reference<A>::type*, std::ostream*>::value,
      typename boost::add_reference<A>::type, //reference to the stream
      typename boost::remove_reference<A>::type
    // for left shift, the default resulting type is the same as the left 
    // operand. A can however be a reference (if it comes from a free variable
    // or if cref or ref  wrappers have been used), 
    // so we return a plain type.
  >::RET type;
};

// istream
template<class A, class B> 
struct return_type_2<bitwise_action<rightshift_action>, A, B>
{
  typedef typename detail::IF<
    boost::is_convertible<typename boost::remove_reference<A>::type*, 
                          std::istream*>::value,
    typename boost::add_reference<A>::type, // ref to the stream type
    typename boost::remove_reference<A>::type
    // for right shift, the default resulting type is the same as the 
    // left operand. A can however be a reference (if it comes from a 
    //free variable or if cref or ref 
    // wrappers have been used), so we return a const plain type.
  >::RET type;
};

// -- logical actions ----------------------------------------
// always bool
// TODO: this may not be true for some weird user-defined types,
// should this be a default, or should it fail for non-standard types ?
template<class A, class B, class Act> 
struct return_type_2<logical_action<Act>, A, B> { typedef bool type; };

// -- relational actions ----------------------------------------
// always bool
// TODO: this may not be true for some weird user-defined types,
// should this be a default, or should it fail for non-standard types ?
template<class A, class B, class Act> 
struct return_type_2<relational_action<Act>, A, B> { 
  typedef bool type; 
};

// Assingment actions -----------------------------------------------
// return type is the type of the first argument 
// (note: it must be a reference).

// TODO: this may not be true for some weird user-defined types,
// should this be a default, or should it fail for non-standard types ?
template<class A, class B, class Act> 
struct return_type_2<arithmetic_assignment_action<Act>, A&, B> { 
  typedef A& type; 
};

template<class A, class B, class Act> 
struct return_type_2<bitwise_assignment_action<Act>, A&, B> { 
  typedef A& type; 
};

template<class A, class B> 
struct return_type_2<other_action<assignment_action>, A&, B> { 
  typedef A& type; 
};

// -- other actions ----------------------------------------

// comma action ----------------------------------
// TODO: this may not be true for some weird user-defined types,
// should this be a default, or should it fail for non-standard types ?
template<class A, class B> 
struct return_type_2<other_action<comma_action>, A, B> { typedef B type; };

// subscript action -----------------------------------------------

// strip reference
template<class A, class B>
struct return_type_2<other_action<subscript_action>, A&, B> {
  typedef typename 
    return_type_2<other_action<subscript_action>, A, B>::type type;
};

// strip constness, but preserve it 
template<class A, class B> 
struct return_type_2<other_action<subscript_action>, const A, B> { 
  // get the (potentially non-const) reference type
  typedef typename 
     return_type_2<other_action<subscript_action>, A, B>::type type1;
  // return a const reference to the underlying type
  typedef const typename boost::remove_reference<type1>::type & type;
};

// The general case, matches all plain class types
// this covers vectors and sets (or any other container that 
// defines the typedef value_type
template<class A, class B> 
struct return_type_2<other_action<subscript_action>, A, B> { 
  typedef typename A::value_type& type;
};


template<class A, class B> 
struct return_type_2<other_action<subscript_action>, A*, B> { typedef A& type; };

// this is needed, because the general const stripping would otherwise add
// const to A as well, here the ptr itself is const not necessarily A. 
// This const may be safely dropped.
template<class A, class B> 
struct return_type_2<other_action<subscript_action>, A* const, B> { 
  typedef A& type; 
};

// for arrays, no need to specialise for const. If A is const, 
// the general const strips const away and puts it back (as it should)
template<class A, class B, const int N> 
struct return_type_2<other_action<subscript_action>, A[N], B> { 
  typedef A& type; 
};

// member_pointer action -----------------------------------------------
 
template<class A, class T, class B>
struct return_type_2<other_action<member_pointer_action>, A, T B::* const> {
  typedef T& type;
};

} // namespace lambda
} // namespace boost


namespace std {
 template <class Key, class T, class Cmp, class Allocator> class map;
 template <class Key, class T, class Cmp, class Allocator> class multimap;
}

// do the same as map for sgi's hash_map, and hash_multimap.
// The SGI STL Port is included because it is so commonly used.
#if defined __SGI_STL_PORT
namespace __STLPORT_NAMESPACE {
template <class _Key, class _Tp, class _HashFcn, class _EqualKey,
          class _Alloc> class hash_map;
template <class _Key, class _Tp, class _HashFcn, class _EqualKey, 
          class _Alloc> class hash_multimap;
}
#endif

namespace boost { 
namespace lambda {

template<class Key, class T, class Cmp, class Allocator, class B> 
struct return_type_2<other_action<subscript_action>, std::map<Key, T, Cmp, Allocator>, B> { 
  typedef T& type;
  // T == std::map<Key, T, Cmp, Allocator>::mapped_type; 
};

template<class Key, class T, class Cmp, class Allocator, class B> 
struct return_type_2<other_action<subscript_action>, std::multimap<Key, T, Cmp, Allocator>, B> { 
  typedef T& type;
  // T == std::map<Key, T, Cmp, Allocator>::mapped_type; 
};

#if defined __SGI_STL_PORT
template <class _Key, class _Tp, class _HashFcn, class _EqualKey, class _Alloc, class B>
struct return_type_2<other_action<subscript_action>, ::__STLPORT_NAMESPACE::hash_map<_Key, _Tp, _HashFcn, _EqualKey, _Alloc>, B> { 
  typedef _Tp& type;
  // T == stlport::hash_map<_Key, _Tp, _HashFcn, _EqualKey, _Alloc>::mapped_type; 
};

template <class _Key, class _Tp, class _HashFcn, class _EqualKey, class _Alloc, class B>
struct return_type_2<other_action<subscript_action>, ::__STLPORT_NAMESPACE::hash_multimap<_Key, _Tp, _HashFcn, _EqualKey, _Alloc>, B> { 
  typedef _Tp& type;
  // T == stlport::hash_multimap<_Key, _Tp, _HashFcn, _EqualKey, _Alloc>::mapped_type; 
};
#endif


} // namespace lambda
} // namespace boost

#endif
