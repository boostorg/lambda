// -- operator_actions.hpp - Boost Lambda Library ----------------------

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

// For more information, see http://lambda.cs.utu.fi 

#ifndef BOOST_LAMBDA_OPERATOR_ACTIONS_HPP
#define BOOST_LAMBDA_OPERATOR_ACTIONS_HPP

namespace boost { 
namespace lambda {


// -- artihmetic ----------------------

class plus_action {};
class minus_action {};
class multiply_action {};
class divide_action {};
class remainder_action {};

// -- bitwise  -------------------

class leftshift_action {};
class rightshift_action {};
class xor_action {};


// -- bitwise/logical -------------------

class and_action {};
class or_action {};
class not_action {};

// -- relational -------------------------

class less_action {};
class greater_action {};
class lessorequal_action {};
class greaterorequal_action {};
class equal_action {};
class notequal_action {};

// -- increment/decrement ------------------------------

class increment_action {};
class decrement_action {};

// -- void return ------------------------------

class do_nothing_action {};

// -- other  ------------------------------

class addressof_action {};
  // class comma_action {}; // defined in actions.hpp
class contentsof_action {};
// class member_pointer_action {}; (defined in member_ptr.hpp)


// -- actioun group templates --------------------

template <class Action> class arithmetic_action;
template <class Action> class bitwise_action;
template <class Action> class logical_action;
template <class Action> class relational_action;
template <class Action> class arithmetic_assignment_action;
template <class Action> class bitwise_assignment_action;
template <class Action> class unary_arithmetic_action;
template <class Action> class pre_increment_decrement_action;
template <class Action> class post_increment_decrement_action;

// ---------------------------------------------------------
#if defined BOOST_LAMBDA_BINARY_ACTION
#error "Multiple defines of BOOST_LAMBDA_BINARY_ACTION"
#endif

#define BOOST_LAMBDA_BINARY_ACTION(OPER_SYMBOL, GROUP, OPER_NAME) \
template<> class GROUP < OPER_NAME> : public protectable {\
  public: \
  template<class RET, class A, class B>\
  static RET apply(A& a, B& b) { \
    return a OPER_SYMBOL b; }\
};\
\

BOOST_LAMBDA_BINARY_ACTION(+,arithmetic_action,plus_action)
BOOST_LAMBDA_BINARY_ACTION(-,arithmetic_action,minus_action)
BOOST_LAMBDA_BINARY_ACTION(*,arithmetic_action,multiply_action)
BOOST_LAMBDA_BINARY_ACTION(/,arithmetic_action,divide_action)
BOOST_LAMBDA_BINARY_ACTION(%,arithmetic_action,remainder_action)

BOOST_LAMBDA_BINARY_ACTION(<<,bitwise_action,leftshift_action)
BOOST_LAMBDA_BINARY_ACTION(>>,bitwise_action,rightshift_action)
BOOST_LAMBDA_BINARY_ACTION(&,bitwise_action,and_action)
BOOST_LAMBDA_BINARY_ACTION(|,bitwise_action,or_action)
BOOST_LAMBDA_BINARY_ACTION(^,bitwise_action,xor_action)

BOOST_LAMBDA_BINARY_ACTION(<,relational_action,less_action)
BOOST_LAMBDA_BINARY_ACTION(>,relational_action,greater_action)
BOOST_LAMBDA_BINARY_ACTION(<=,relational_action,lessorequal_action)
BOOST_LAMBDA_BINARY_ACTION(>=,relational_action,greaterorequal_action)
BOOST_LAMBDA_BINARY_ACTION(==,relational_action,equal_action)
BOOST_LAMBDA_BINARY_ACTION(!=,relational_action,notequal_action)

BOOST_LAMBDA_BINARY_ACTION(+=,arithmetic_assignment_action,plus_action)
BOOST_LAMBDA_BINARY_ACTION(-=,arithmetic_assignment_action,minus_action)
BOOST_LAMBDA_BINARY_ACTION(*=,arithmetic_assignment_action,multiply_action)
BOOST_LAMBDA_BINARY_ACTION(/=,arithmetic_assignment_action,divide_action)
BOOST_LAMBDA_BINARY_ACTION(%=,arithmetic_assignment_action,remainder_action)

BOOST_LAMBDA_BINARY_ACTION(<<=,bitwise_assignment_action,leftshift_action)
BOOST_LAMBDA_BINARY_ACTION(>>=,bitwise_assignment_action,rightshift_action)
BOOST_LAMBDA_BINARY_ACTION(&=,bitwise_assignment_action,and_action)
BOOST_LAMBDA_BINARY_ACTION(|=,bitwise_assignment_action,or_action)
BOOST_LAMBDA_BINARY_ACTION(^=,bitwise_assignment_action,xor_action)

// && and || are defined directly in specializations for lambda_functor_base
// to achieve short circuiting


BOOST_LAMBDA_BINARY_ACTION(=,other_action, assignment_action)
// subscript is done directly because BOOST_LAMBDA_BINARY_ACTION currently doesn't handle it.

template<> class other_action<subscript_action> : public protectable {
public:
  template<class RET, class A, class B>
  static RET apply(A& a, B& b) { return a[b]; }
};

// do_nothing_action is also specified directly for the same reason.
template<> class return_void_action<do_nothing_action> {
public:
  template<class RET>
  static RET apply() {}
};

// comma_action removed, a specialisation is provided to lambda_functor_base
// This is to handle void arguments (built-in comma operator can take void
// arguments whereas a user-defined function can't) (JJ)

#if defined BOOST_LAMBDA_PREFIX_UNARY_ACTION
#error "Multiple defines of BOOST_LAMBDA_PREFIX_UNARY_ACTION"
#endif

#define BOOST_LAMBDA_PREFIX_UNARY_ACTION(OPER_SYMBOL, GROUP, OPER_NAME) \
template<> class GROUP <OPER_NAME> : public protectable {\
public: \
  template<class RET, class A>\
  static RET apply(A& a) { return OPER_SYMBOL a; }\
};\
\

BOOST_LAMBDA_PREFIX_UNARY_ACTION(+, unary_arithmetic_action,plus_action)
BOOST_LAMBDA_PREFIX_UNARY_ACTION(-, unary_arithmetic_action,minus_action)
BOOST_LAMBDA_PREFIX_UNARY_ACTION(~, bitwise_action,not_action)
BOOST_LAMBDA_PREFIX_UNARY_ACTION(!, logical_action,not_action)
BOOST_LAMBDA_PREFIX_UNARY_ACTION(++, pre_increment_decrement_action,increment_action)
BOOST_LAMBDA_PREFIX_UNARY_ACTION(--, pre_increment_decrement_action,decrement_action)

BOOST_LAMBDA_PREFIX_UNARY_ACTION(&,other_action, addressof_action)
BOOST_LAMBDA_PREFIX_UNARY_ACTION(*,other_action, contentsof_action)

BOOST_LAMBDA_PREFIX_UNARY_ACTION( , other_action, identity_action)

#if defined BOOST_LAMBDA_POSTFIX_UNARY_ACTION
#error "Multiple defines of BOOST_LAMBDA_POSTFIX_UNARY_ACTION"
#endif

#define BOOST_LAMBDA_POSTFIX_UNARY_ACTION(OPER_SYMBOL, GROUP, OPER_NAME) \
template<> class GROUP <OPER_NAME> : public protectable {\
public: \
  template<class RET, class A>\
  static RET apply(A& a) { return a OPER_SYMBOL; }\
};\
\

BOOST_LAMBDA_POSTFIX_UNARY_ACTION(++, post_increment_decrement_action,increment_action)
BOOST_LAMBDA_POSTFIX_UNARY_ACTION(--, post_increment_decrement_action,decrement_action)


#undef BOOST_LAMBDA_BINARY_ACTION
#undef BOOST_LAMBDA_PREFIX_UNARY_ACTION
#undef BOOST_LAMBDA_POSTFIX_UNARY_ACTION

} // namespace lambda 
} // namespace boost

#endif
