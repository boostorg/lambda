// -- Boost Lambda Library - actions.hpp ----------------------------------

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

// For more information, see www.boost.org

// ----------------------------------------------------------------

#ifndef BOOST_LAMBDA_ACTIONS_HPP
#define BOOST_LAMBDA_ACTIONS_HPP

namespace boost { 
namespace lambda {


template<int Arity, class Act> struct action;

   

// these need to be defined here, since the corresponding lambda 
// functions are members of lambda_functor classes

class assignment_action {};
class subscript_action {};

class identity_action {};
   
template <class Action> class other_action;

   
// action for specifying the explicit return type
template <class RET> class explicit_return_type_action {};

// action for preventing the expansion of a lambda expression
struct protect_action {};
   
template <class Action> class return_void_action;
template <int I> class function_action;
   
// lambda_functor_action arise when the target function in a bind expression
// is a lambda functor. We must use a separate action type to notify 
// the return type deduction system, but the apply functions of 
// function_action struct work just fine
template <int I> class lambda_functor_action : public function_action<I> {};



// ---------------------------------------------------------

template<> class function_action<1> {
public:
  template<class RET, class A1>
  static RET apply(A1& a1) {
    return function_adaptor<typename boost::remove_const<A1>::type>::apply(a1);
  }
};

template<> class function_action<2> {
public:
  template<class RET, class A1, class A2>
  static RET apply(A1& a1, A2& a2) {
    return function_adaptor<typename boost::remove_const<A1>::type>::apply
           (a1, a2);
  }
};

template<> class function_action<3> {
public:
  template<class RET, class A1, class A2, class A3>
  static RET apply(A1& a1, A2& a2, A3& a3) {
    return function_adaptor<typename boost::remove_const<A1>::type>::apply
           (a1, a2, a3);
  }
};

template<> class function_action<4> {
public:
  template<class RET, class A1, class A2, class A3, class A4>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4) {
    return function_adaptor<typename boost::remove_const<A1>::type>::apply
           (a1, a2, a3, a4);
  }
};

template<> class function_action<5> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return function_adaptor<typename boost::remove_const<A1>::type>::apply
           (a1, a2, a3, a4, a5);
  }
};

template<> class function_action<6> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return function_adaptor<typename boost::remove_const<A1>::type>::apply
           (a1, a2, a3, a4, a5, a6);
  }
};

template<> class function_action<7> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5,  
           class A6, class A7>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return function_adaptor<typename boost::remove_const<A1>::type>::apply
           (a1, a2, a3, a4, a5, a6, a7);
  }
};

template<> class function_action<8> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6, class A7, class A8>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, 
                   A8& a8) {
    return function_adaptor<typename boost::remove_const<A1>::type>::apply
           (a1, a2, a3, a4, a5, a6, a7, a8);
  }
};

template<> class function_action<9> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6, class A7, class A8, class A9>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, 
                   A8& a8, A9& a9) {
    return function_adaptor<typename boost::remove_const<A1>::type>::apply
           (a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }
};

template<> class function_action<10> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6, class A7, class A8, class A9, class A10>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, 
                   A8& a8, A9& a9, A10& a10) {
    return function_adaptor<typename boost::remove_const<A1>::type>::apply
           (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
  }
};

} // namespace lambda
} // namespace boost

#endif
