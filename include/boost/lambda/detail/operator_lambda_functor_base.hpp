// Boost Lambda Library  - operator_lambda_functor_base.hpp -----------------
//
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

// ------------------------------------------------------------

#ifndef BOOST_LAMBDA_OPERATOR_LAMBDA_FUNCTOR_BASE_HPP
#define BOOST_LAMBDA_OPERATOR_LAMBDA_FUNCTOR_BASE_HPP

namespace boost { 
namespace lambda {


// These operators cannot be implemented as apply functions of action 
// templates


// Specialization for comma.
template<class Args>
class lambda_functor_base<action<2, other_action<comma_action> >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    return detail::select(boost::tuples::get<0>(args), a, b, c), 
           detail::select(boost::tuples::get<1>(args), a, b, c); 
  }
};  

// Specialization for logical and (to preserve shortcircuiting)
template<class Args>
class lambda_functor_base<action<2, logical_action<and_action> >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    return detail::select(boost::tuples::get<0>(args), a, b, c) && 
           detail::select(boost::tuples::get<1>(args), a, b, c); 
  }
};  

// Specialization for logical or (to preserve shortcircuiting)
template<class Args>
class lambda_functor_base<action<2, logical_action< or_action> >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    return detail::select(boost::tuples::get<0>(args), a, b, c) || 
           detail::select(boost::tuples::get<1>(args), a, b, c); 
  }
};  

} // namespace lambda
} // namespace boost

#endif
