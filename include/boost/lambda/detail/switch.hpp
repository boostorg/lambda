// Boost Lambda Library -- switch.hpp -----------------------------------
//
// Copyright (C) 2000 Gary Powell (gary.powell@sierra.com)
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

// --------------------------------------------------------------------------

#if !defined(BOOST_LAMBDA_SWITCH_HPP)
#define BOOST_LAMBDA_SWITCH_HPP

#include "boost/lambda/detail/preprocessor/enum_shifted_params.hpp"
#include "boost/lambda/detail/preprocessor/2nd_repeat.hpp"

namespace boost { 
namespace lambda {

// Switch actions
template <class Switch1 = null_type, class Switch2 = null_type, 
          class Switch3 = null_type, class Switch4 = null_type,
          class Switch5 = null_type, class Switch6 = null_type, 
          class Switch7 = null_type, class Switch8 = null_type, 
          class Switch9 = null_type>
struct switch_action {};


namespace detail {

  // templates to represent special lambda functors for the cases in 
  // switch statements
  
template <int Value> struct case_label {};
struct default_label {};

template<class Type> struct switch_case_tag {};

  // a normal case is represented as:
  // tagged_lambda_functor<switch_case_tag<case_label<N> > >, LambdaFunctor>
  
  // the default case as:
  // tagged_lambda_functor<switch_case_tag<default_label> >, LambdaFunctor>


} // end detail


/// create switch_case_tag tagged_lambda_functors
template <int CaseValue, class Arg>
inline const 
tagged_lambda_functor<
  detail::switch_case_tag<detail::case_label<CaseValue> >, 
  lambda_functor<Arg> 
> 
case_statement(const lambda_functor<Arg>& a) { 
  return 
    tagged_lambda_functor<
      detail::switch_case_tag<detail::case_label<CaseValue> >, 
      lambda_functor<Arg> 
    >(a); 
}

// No case body case.
template <int CaseValue>
inline const 
tagged_lambda_functor<
  detail::switch_case_tag<detail::case_label<CaseValue> >,
  lambda_functor< 
    lambda_functor_args< 
      action<0, return_void_action<do_nothing_action> >, 
      null_type, 
      NONE
    > 
  > 
> 
case_statement() { 
return 
  tagged_lambda_functor<
    detail::switch_case_tag<detail::case_label<CaseValue> >,
    lambda_functor< 
      lambda_functor_args< 
        action<0, return_void_action<do_nothing_action> >, 
        null_type, 
        NONE
      > 
    > 
  > () ;
}

// default label
template <class Arg>
inline const 
tagged_lambda_functor<
  detail::switch_case_tag<detail::default_label>, 
  lambda_functor<Arg> 
> 
default_statement(const lambda_functor<Arg>& a) { 
  return 
    tagged_lambda_functor<
      detail::switch_case_tag<detail::default_label>, 
      lambda_functor<Arg> 
    >(a); 
}

// default lable, no case body case.
inline const 
tagged_lambda_functor<
  detail::switch_case_tag<detail::default_label>,
  lambda_functor< 
    lambda_functor_args< 
      action<0, return_void_action<do_nothing_action> >, 
      null_type, 
      NONE
    > 
  > 
> 
default_statement() { 
return 
  tagged_lambda_functor<
    detail::switch_case_tag<detail::default_label>,
    lambda_functor< 
      lambda_functor_args< 
        action<0, return_void_action<do_nothing_action> >, 
        null_type, 
        NONE
      > 
    > 
  > () ;
}


// Specializations for lambda_functor_base of case_statement -----------------

// 0 case type:
// useless (just the condition part) but provided for completeness.
template<class Args>
class 
lambda_functor_base<
  action<1, return_void_action<switch_action< > > >, 
  Args
> 
{
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    detail::select(::boost::tuples::get<1>(args), a, b, c);  
  }
};

// 1 case type:
// template<class Args, int Case1>
// class 
// lambda_functor_base<
//   action<
//     2, 
//     return_void_action<switch_action<detail::case_label<Case1> > > 
//   >, 
//   Args
// > 
// {
//   Args args;
// public:
//   explicit lambda_functor_base(const Args& a) : args(a) {}

//   template<class RET, class A, class B, class C>
//   RET call(A& a, B& b, C& c) const {
//     switch( detail::select(::boost::tuples::get<0>(args), a, b, c) )  
//     {
//       case Case1:                
//         detail::select(::boost::tuples::get<1>(args), a, b, c);
//         break;
//     }
//   }
// };

// switch with default being the sole label - doesn't make much sense but
// it is there for completeness
// template<class Args>						
// class								
// lambda_functor_base<						
//   action<							
//     2,								
//     return_void_action<switch_action<detail::default_label> >	
//   >,								
//   Args								
// >								
// {								
//   Args args;							
// public:								
//   explicit lambda_functor_base(const Args& a) : args(a) {}	
// 								
//   template<class RET, class A, class B, class C>		
//   RET call(A& a, B& b, C& c) const {				
//     switch( detail::select(::boost::tuples::get<0>(args), a, b, c) )	
//     {								
//       default:							
//         detail::select(::boost::tuples::get<1>(args), a, b, c);		
//         break;							
//     }								
//   }								
// };



// // 2 case type:
// The different specializations are generated with Vesa Karvonen's 
// preprocessor library.

// This is just a comment to show what the generated classes look like

// template<class Args, int Case1, int Case2>
// class 
// lambda_functor_base<
//   action<3, 
//     return_void_action< 
//       switch_action< 
//         detail::case_label<Case1>,
//         detail::case_label<Case2>
//       > 
//     > 
//   >, 
//   Args
// > 
// {
//   Args args;
// public:
//   explicit lambda_functor_base(const Args& a) : args(a) {}

//   template<class RET, class A, class B, class C>
//   RET call(A& a, B& b, C& c) const {
//     switch( detail::select(::boost::tuples::get<0>(args), a, b, c) )  
//     {
//       case Case1:                
//         detail::select(::boost::tuples::get<1>(args), a, b, c);
//         break;
//       case Case2:                
//         detail::select(::boost::tuples::get<2>(args), a, b, c);
//         break;
//     }
//   }
// };

// template<class Args, int Case1>
// class 
// lambda_functor_base<
//   action<3, 
//     return_void_action< 
//       switch_action< 
//         detail::case_label<Case1>,
//         detail::default_label 
//       > 
//     > 
//   >, 
//   Args
// > 
// {
//   Args args;
// public:
//   explicit lambda_functor_base(const Args& a) : args(a) {}

//   template<class RET, class A, class B, class C>
//   RET call(A& a, B& b, C& c) const {
//     switch( detail::select(::boost::tuples::get<0>(args), a, b, c) )  
//     {
//       case Case1:                
//         detail::select(::boost::tuples::get<1>(args), a, b, c);
//         break;
//       default:                
//         detail::select(::boost::tuples::get<2>(args), a, b, c);
//         break;
//     }
//   }
// };
// -------------------------

// Some helper preprocessor macros ---------------------------------

// BOOST_LAMBDA_A_I_LIST(N, X) is a list of form X0, X1, ..., XN
// BOOST_LAMBDA_A_I_B_LIST(N, X, Y) is a list of form X0 Y, X1 Y, ..., XN Y
// BOOST_LAMBDA_A_I_B_LIST(N, X, Y) is a list of form X0 Y0, X1 Y1, ..., XN YN

#define BOOST_LAMBDA_A_I(i, A, FOO) 		\
BOOST_PREPROCESSOR_COMMA_IF(i) BOOST_PREPROCESSOR_CAT(A,i)

#define BOOST_LAMBDA_A_I_B(i, A, B) 		\
BOOST_PREPROCESSOR_COMMA_IF(i) BOOST_PREPROCESSOR_CAT(A,i) B

#define BOOST_LAMBDA_A_I_B_I(i, A, B)		\
BOOST_PREPROCESSOR_COMMA_IF(i) 			\
BOOST_PREPROCESSOR_CAT(A,i) 			\
BOOST_PREPROCESSOR_CAT(B,i)

#define BOOST_LAMBDA_A_I_LIST(i, A) 				\
BOOST_PREPROCESSOR_REPEAT(i,BOOST_LAMBDA_A_I, A, FOO) 		

#define BOOST_LAMBDA_A_I_B_LIST(i, A, B) 			\
BOOST_PREPROCESSOR_REPEAT(i,BOOST_LAMBDA_A_I_B, A, B) 		

#define BOOST_LAMBDA_A_I_B_I_LIST(i, A, B) 			\
BOOST_PREPROCESSOR_REPEAT(i, BOOST_LAMBDA_A_I_B_I, A, B) 

// Switch related macros -------------------------------------------
#define BOOST_LAMBDA_SWITCH_CASE_BLOCK(N, A, B)				  \
  case Case##N:								  \
  detail::select(::boost::tuples::get<BOOST_PREPROCESSOR_INC(N)>(args), a, b, c); \
  break;

#define BOOST_LAMBDA_SWITCH_CASE_BLOCK_LIST(N) 			\
BOOST_PREPROCESSOR_REPEAT(N, BOOST_LAMBDA_SWITCH_CASE_BLOCK, FOO, FOO)
// 2 case type:

#define BOOST_LAMBDA_SWITCH_NO_DEFAULT_CASE(N)				\
template<class Args, BOOST_LAMBDA_A_I_LIST(N, int Case)>	\
class									\
lambda_functor_base<							\
  action<BOOST_PREPROCESSOR_INC(N),					\
    return_void_action<							\
      switch_action<							\
        BOOST_LAMBDA_A_I_B_LIST(N, detail::case_label<Case,>)		\
      >									\
    >									\
  >,									\
  Args									\
>									\
{	\
public:								\
  Args args;								\
public:									\
  explicit lambda_functor_base(const Args& a) : args(a) {}		\
									\
  template<class RET, class A, class B, class C>			\
  RET call(A& a, B& b, C& c) const {					\
    switch( detail::select(::boost::tuples::get<0>(args), a, b, c) )		\
    {									\
      BOOST_LAMBDA_SWITCH_CASE_BLOCK_LIST(N)				\
    }									\
  }									\
};

	

#define BOOST_LAMBDA_SWITCH_WITH_DEFAULT_CASE(N)			\
template<								\
  class Args BOOST_PREPROCESSOR_COMMA_IF(BOOST_PREPROCESSOR_DEC(N))	\
  BOOST_LAMBDA_A_I_LIST(BOOST_PREPROCESSOR_DEC(N), int Case)		\
>									\
class									\
lambda_functor_base<							\
  action<BOOST_PREPROCESSOR_INC(N),					\
    return_void_action<							\
      switch_action<							\
        BOOST_LAMBDA_A_I_B_LIST(BOOST_PREPROCESSOR_DEC(N),		\
                                detail::case_label<Case, >)		\
        BOOST_PREPROCESSOR_COMMA_IF(BOOST_PREPROCESSOR_DEC(N))		\
        detail::default_label						\
      >									\
    >									\
  >,									\
  Args									\
>									\
{									\
public: \
  Args args;								\
public:									\
  explicit lambda_functor_base(const Args& a) : args(a) {}		\
									\
  template<class RET, class A, class B, class C>			\
  RET call(A& a, B& b, C& c) const {					\
    switch( detail::select(::boost::tuples::get<0>(args), a, b, c) )	\
    {									\
        BOOST_LAMBDA_SWITCH_CASE_BLOCK_LIST(BOOST_PREPROCESSOR_DEC(N))	\
      default:								\
        detail::select(::boost::tuples::get<N>(args), a, b, c);		\
        break;								\
    }									\
  }									\
};






// switch_statement bind functions -------------------------------------

// The zero argument case, for completeness sake
inline const 
lambda_functor< 
  lambda_functor_args< 
    action<0, return_void_action<do_nothing_action> >, 
    null_type, 
    NONE 
  > 
>
switch_statement() { 
  return 
    lambda_functor< 
      lambda_functor_args< 
        action<0, return_void_action<do_nothing_action> >, 
        null_type, 
        NONE 
      > 
    >
  ( null_type());
}

// 1 argument case, this is useless as well, just the condition part
template <class TestArg>
inline const 
lambda_functor< 
  lambda_functor_args< 
    action<1, return_void_action<switch_action<> > >, 
    tuple<lambda_functor<TestArg> >, 
    dig_arity<TestArg>::value
  > 
>
switch_statement(const lambda_functor<TestArg>& a1) { 
  return 
    lambda_functor< 
      lambda_functor_args< 
         action<1, return_void_action<switch_action<> > >, 
         tuple< lambda_functor<TestArg> >, 
         dig_arity<TestArg >::value 
      > 
    >
    ( tuple<lambda_functor<TestArg> >(a1));
}


#define HELPER(N, FOO, BAR)					\
BOOST_PREPROCESSOR_COMMA_IF(N)					\
BOOST_PREPROCESSOR_CAT(						\
  const tagged_lambda_functor<detail::switch_case_tag<TagData,	\
  N>)								\
BOOST_PREPROCESSOR_COMMA() Arg##N>& a##N

#define HELPER_LIST(N) BOOST_PREPROCESSOR_REPEAT(N, HELPER, FOO, FOO)


#define BOOST_LAMBDA_SWITCH_STATEMENT(N)				\
template <class TestArg,						\
          BOOST_LAMBDA_A_I_LIST(N, class TagData),			\
          BOOST_LAMBDA_A_I_LIST(N, class Arg)>				\
inline const								\
lambda_functor<								\
  lambda_functor_args<							\
    action<BOOST_PREPROCESSOR_INC(N),					\
      return_void_action<						\
        switch_action<							\
          BOOST_LAMBDA_A_I_LIST(N, TagData)				\
        >								\
      >									\
    >,									\
    tuple<lambda_functor<TestArg>, BOOST_LAMBDA_A_I_LIST(N, Arg)>,	\
    combine_arities< TestArg, BOOST_LAMBDA_A_I_LIST(N, Arg)>::value	\
  >									\
>									\
switch_statement(							\
  const lambda_functor<TestArg>& ta,					\
  HELPER_LIST(N)							\
)									\
{									\
  return								\
    lambda_functor<							\
      lambda_functor_args<						\
        action<BOOST_PREPROCESSOR_INC(N),				\
          return_void_action<						\
            switch_action<						\
              BOOST_LAMBDA_A_I_LIST(N, TagData)				\
            >								\
          >								\
        >,								\
        tuple<lambda_functor<TestArg>, BOOST_LAMBDA_A_I_LIST(N, Arg)>,	\
        combine_arities< TestArg, BOOST_LAMBDA_A_I_LIST(N, Arg)>::value	\
      >									\
    >									\
    ( tuple<lambda_functor<TestArg>, BOOST_LAMBDA_A_I_LIST(N, Arg)>	\
        (ta, BOOST_LAMBDA_A_I_LIST(N, a) ));				\
}




// Here's the actual generation

#define BOOST_LAMBDA_SWITCH(N) 			\
BOOST_LAMBDA_SWITCH_NO_DEFAULT_CASE(N)		\
BOOST_LAMBDA_SWITCH_WITH_DEFAULT_CASE(N)        

// Use this to avoid case 0, these macros work only from case 1 upwards
#define BOOST_LAMBDA_SWITCH_HELPER(N, A, B)		\
BOOST_LAMBDA_SWITCH( BOOST_PREPROCESSOR_INC(N) )

// Use this to avoid cases 0 and 1, these macros work only from case 2 upwards
#define BOOST_LAMBDA_SWITCH_STATEMENT_HELPER(N, A, B)			     \
BOOST_LAMBDA_SWITCH_STATEMENT(BOOST_PREPROCESSOR_INC(N))



  // up to 9 cases supported (counting default:)
BOOST_PREPROCESSOR_2ND_REPEAT(9,BOOST_LAMBDA_SWITCH_HELPER,FOO,FOO)
BOOST_PREPROCESSOR_2ND_REPEAT(9,BOOST_LAMBDA_SWITCH_STATEMENT_HELPER,FOO,FOO)


} // namespace lambda 
} // namespace boost


#undef HELPER
#undef HELPER_LIST

#undef BOOST_LAMBDA_SWITCH_HELPER
#undef BOOST_LAMBDA_SWITCH
#undef BOOST_LAMBDA_SWITCH_NO_DEFAULT_CASE
#undef BOOST_LAMBDA_SWITCH_WITH_DEFAULT_CASE

#undef BOOST_LAMBDA_SWITCH_CASE_BLOCK
#undef BOOST_LAMBDA_SWITCH_CASE_BLOCK_LIST

#undef BOOST_LAMBDA_SWITCH_STATEMENT
#undef BOOST_LAMBDA_SWITCH_STATEMENT_HELPER



#endif
