// -- select_functions.hpp -- Boost Lambda Library --------------------------

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
// For more information, see http://lambda.cs.utu.fi 


#ifndef BOOST_LAMBDA_SELECT_FUNCTIONS_HPP
#define BOOST_LAMBDA_SELECT_FUNCTIONS_HPP

namespace boost { 
namespace lambda {
namespace detail {

// selector<ArityCode>::select functions ---------------------------------

//   called from select functions

template <int Code> struct selector;


// The primary template covers all lambda functors with the EXCEPTION 
// placeholder as a subexpression
template <int Code> struct selector {
  template<class RET, class Op, class A, class B, class C>
  static RET select(Op& op, A& a, B& b, C& c) { 
    return op.template ret_call<RET>(a, b, c); 
  }
};

// The cases cover all other placeholders 
template <> struct selector<NONE> {
  template<class RET, class Op, class A, class B, class C>
  static RET select(Op& op, A& a, B& b, C& c) {   
    return op.template ret_call<RET>(); 
  }
};
template <> struct selector<FIRST> {
  template<class RET, class Op, class A, class B, class C>
  static RET select(Op& op, A& a, B& b, C& c) { 
    return op.template ret_call<RET>(a);
  }
};
template <> struct selector<SECOND> {
  template<class RET, class Op, class A, class B, class C>
  static RET select(Op& op, A& a, B& b, C& c) { 
    return op.template ret_call<RET>(a, b); 
  }
};
template <> struct selector<THIRD> {
  template<class RET, class Op, class A, class B, class C>
  static RET select(Op& op, A& a, B& b, C& c) { 
    return op.template ret_call<RET>(a, b, c); 
  }

};

// select functions -------------------------------
template<class Any, class A, class B, class C>
inline Any& select(Any& any, A&, B&, C&) { return any; }

template<class A, class B, class C>
inline A& select(const lambda_functor<placeholder<FIRST> >&, A& a, B&, C&) { 
  return a; 
}
template<class A, class B, class C>
inline A& select(lambda_functor<placeholder<FIRST> >&, A& a, B&, C&) { 
  return a; 
}

template<class A, class B, class C>
inline B& select(const lambda_functor<placeholder<SECOND> >&, A&, B& b, C&) { 
  return b; 
}
template<class A, class B, class C>
inline B& select(lambda_functor<placeholder<SECOND> >&, A&, B& b, C&) { 
  return b; 
}

template<class A, class B, class C>
inline C& select(const lambda_functor<placeholder<THIRD> >&, A&, B&, C& c) { 
  return c; 
}
template<class A, class B, class C>
inline C& select(lambda_functor<placeholder<THIRD> >&, A&, B&, C& c) { 
  return c; 
}

// Exception placeholder reuses the third argument position
template<class A, class B, class C>
inline C& select(const lambda_functor<placeholder<EXCEPTION> >&, A&, B&, C& c)
{ 
  return c; 
}
template<class A, class B, class C>
inline C& select(lambda_functor<placeholder<EXCEPTION> >&, A&, B&, C& c) { 
  return c; 
}

template<class Arg, class A, class B, class C>
inline typename return_type<lambda_functor<Arg>, open_args<A&, B&, C&> >::type
select ( const lambda_functor<Arg>& op, A& a, B& b, C& c ) { 
  return selector<dig_arity<Arg>::value>::template select<typename return_type<lambda_functor<Arg>, open_args<A&, B&, C&> >::type>(op, a, b, c);
}
template<class Arg, class A, class B, class C>
inline typename return_type<lambda_functor<Arg>, open_args<A&, B&, C&> >::type
select ( lambda_functor<Arg>& op, A& a, B& b, C& c) { 
  return selector<dig_arity<Arg>::value>::template select<typename return_type<lambda_functor<Arg>, open_args<A&, B&, C&> >::type>(op, a, b, c);
}

// ------------------------------------------------------------------------
// selector functions where the return type is explicitly given
// Note: on many functions, this return type is just discarded.
// The select functions are inside a class template, and the return type
// is a class template argument.
// The first implementation used function templates with an explicitly 
// specified template parameter.
// However, this resulted in ambiguous calls (at least with gcc 2.95.2 
// and edg 2.44). Not sure whether the compilers were right or wrong. 
template<class RET> struct ret_selector
{

// TODO: add checks that RET is of correct type
  template<class Any, class A, class B, class C>
  static Any& select(Any& any, A&, B&, C&) { return any; }

  template<class A, class B, class C>
  static A& select(const lambda_functor<placeholder<FIRST> >&, A& a, B&, C&) {
    return a; 
  }
  
  template<class A, class B, class C>
  static A& select(lambda_functor<placeholder<FIRST> >&, A& a, B&, C&) { 
    return a; 
  }

  template<class A, class B, class C>
  static B& select(const lambda_functor<placeholder<SECOND> >&, A&, B& b, C&) {    return b; 
  }

  template<class A, class B, class C>
  static B& select(lambda_functor<placeholder<SECOND> >&, A&, B& b, C&) {
    return b; 
  }

  template<class A, class B, class C>
  static C& select(const lambda_functor<placeholder<THIRD> >&, A&, B&, C& c) {
    return c; 
  }
  
  template<class A, class B, class C>
  static C& select(lambda_functor<placeholder<THIRD> >&, A&, B&, C& c) { 
    return c; 
  }

// Exception placeholder reuses the third argument position
  template<class A, class B, class C>
  static inline C& 
  select(const lambda_functor<placeholder<EXCEPTION> >&, A&, B&, C& c) { 
    return c; 
  }
  template<class A, class B, class C>
  static inline C& 
  select(lambda_functor<placeholder<EXCEPTION> >&, A&, B&, C& c) { 
    return c; 
  }


  template<class Arg, class A, class B, class C> 
  static RET select (const lambda_functor<Arg>& op, A& a, B& b, C& c ) { 
    return selector<dig_arity<Arg>::value>::template select<RET>(op, a, b, c);
  }
  template<class Arg, class A, class B, class C> 
  static RET select (lambda_functor<Arg>& op, A& a, B& b, C& c ) { 
    return selector<dig_arity<Arg>::value>::template select<RET>(op, a, b, c);
  }
};
   
} // namespace detail
} // namespace lambda
} // namespace boost

#endif
