// Boost Lambda Library -  lambda_functors.hpp -------------------------------

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
// For more information, see http://www.boost.org

// ------------------------------------------------

#ifndef BOOST_LAMBDA_LAMBDA_FUNCTORS_HPP
#define BOOST_LAMBDA_LAMBDA_FUNCTORS_HPP

namespace boost { 
namespace lambda {

// -- lambda_functor --------------------------------------------
// --------------------------------------------------------------

//inline const null_type const_null_type() { return null_type(); }

namespace detail {
namespace {

  static const null_type constant_null_type = null_type();

} // unnamed
} // detail

#define const_null_type() detail::constant_null_type

#if defined BOOST_LAMBDA_LAMBDA_FUNCTOR_ASSIGNMENT
#error "Multiple defines of BOOST_LAMBDA_LAMBDA_FUNCTOR_ASSIGNMENT"
#endif

#define BOOST_LAMBDA_LAMBDA_FUNCTOR_ASSIGNMENT\
  template<class A>\
  const lambda_functor<lambda_functor_args<\
                  action<2, other_action<assignment_action> >,\
                  boost::tuple<lambda_functor, \
                        typename const_copy_argument <const A>::type>,\
                  combine_arities<lambda_functor,A>::value> >\
  operator=(const A& a) const { \
    return lambda_functor<lambda_functor_args<\
                  action<2, other_action<assignment_action> >,\
                  boost::tuple<lambda_functor, \
                        typename const_copy_argument <const A>::type>,\
                  combine_arities<lambda_functor,A>::value> >\
     (  boost::tuple<lambda_functor, \
             typename const_copy_argument <const A>::type>(*this, a) );\
  }\
\

#if defined BOOST_LAMBDA_LAMBDA_FUNCTOR_SUBSCRIPT
#error "Multiple defines of BOOST_LAMBDA_LAMBDA_FUNCTOR_SUBSCRIPT"
#endif

#define BOOST_LAMBDA_LAMBDA_FUNCTOR_SUBSCRIPT\
  template<class A>\
  const lambda_functor<lambda_functor_args<\
                  action<2, other_action<subscript_action> >,\
                  boost::tuple<lambda_functor, \
                        typename const_copy_argument <const A>::type>,\
                  combine_arities<lambda_functor,A>::value> >\
  operator[](const A& a) const { \
    return lambda_functor<lambda_functor_args<\
                  action<2, other_action<subscript_action> >,\
                  boost::tuple<lambda_functor, \
                        typename const_copy_argument <const A>::type>,\
                  combine_arities<lambda_functor,A>::value> >\
     ( boost::tuple<lambda_functor, \
             typename const_copy_argument <const A>::type>(*this, a ) );\
  }\
\


template <int I>
class lambda_functor<placeholder<I> > {
public:
  lambda_functor() {}
  // default constructor (do nothing)
  // bug in gcc 2.95.2 for const template objects.

  
BOOST_LAMBDA_LAMBDA_FUNCTOR_ASSIGNMENT
BOOST_LAMBDA_LAMBDA_FUNCTOR_SUBSCRIPT


};

namespace detail {

  // helpers
template <class T> struct identity { typedef T type; };

  // take the Nth element in the tuple, or null_type if tuple is not 
  // long enough

template <int N, class T>
struct element_or_null_type {
  typedef typename 
    detail::IF_type<
      (N < boost::tuples::length<T>::value),
      boost::tuples::element<N, T>, 
      identity<null_type>
    >::type type; 
};

  // Lambda functors all provide the sig member template for 
  // querying their return type. 
  // these type mappings implement the tools for that deduction

  //type mapping to compute the new lambda functor resulting from a curried
  // call. 
  template<class LF, int Args_expected, class SigArgs>
  struct curry_sig {

    // First arg in SigArgs is the lambda functor type, that's why the -1
    BOOST_STATIC_CONSTANT(int, acount = boost::tuples::length<SigArgs>::value-1);


    // currying is only supported for 2- and 3-ary lambda functors, and
    // must be called by 1 or 2 arguments.
    //    BOOST_STATIC_ASSERT(acount == 1 || acount == 2);
    //    BOOST_STATIC_ASSERT(dig_arity<LF>::value == SECOND || dig_arity<LF>::value == THIRD);
 

    typedef typename detail::element_or_null_type<1, SigArgs>::type el_1;
    typedef typename detail::element_or_null_type<2, SigArgs>::type el_2;

    typedef lambda_functor<
      lambda_functor_args<
        action<Args_expected + 1, curry_action<acount> >,
        // remoce_const_refernce takes care that const null_type will 
        // be null_type, that arrays are always stored as const refs,
        // that nonconst refs remain nonconst refs, and everything else goes
        // to const copy.
 
        tuple<
          LF, 
          typename detail::remove_const_reference<el_1>::type,
          typename detail::remove_const_reference<el_2>::type
        >,
	detail::reduce_arity<dig_arity<LF>::value, acount>::value
      >
    > type;
  };

  // enter the normal return type deduction
  template <class LF, class SigArgs>
  struct eval_sig
  {
    typedef typename 
      return_type<
        LF,
        open_args<
          detail::element_or_null_type<1, SigArgs>::type,
          detail::element_or_null_type<2, SigArgs>::type,
          detail::element_or_null_type<3, SigArgs>::type
	> 
      >::type type;
  };

  // either a normal evaluation, or a curried call
  template <class LF, int Args_expected, class SigArgs>
  struct lambda_functor_sig
  {
    typedef typename 
      detail::IF_type<
        (boost::tuples::length<SigArgs>::value - 1 < Args_expected),
        detail::curry_sig<LF, Args_expected, SigArgs>, 
        detail::eval_sig<LF, SigArgs>
      >::type type;
  };

} // end detail

// -- lambda_functor NONE ------------------------------------------------
template <class Action, class Args>
class lambda_functor<lambda_functor_args<Action, Args, NONE> > 
  : public lambda_functor_base<Action, Args>, public has_sig
{
public:
  typedef lambda_functor_base<Action, Args> inherited;

  explicit lambda_functor(const Args& args) 
    : inherited(args) {} 

  // lambda functors can be copied, if arity and action are the same
  // and Args tuples copyable
  template <class Args2> lambda_functor
    (const lambda_functor<lambda_functor_args<Action, Args2, NONE> >& f)
      : inherited(f.args) {}

  template <class SigArgs> struct sig {
    typedef typename 
      detail::lambda_functor_sig<lambda_functor, 0, SigArgs>::type type;
  };

    return_type<
      lambda_functor, 
      open_args<null_type, null_type, null_type> 
    >::type
    operator()() const { 
      return inherited::template 
         call<
           typename return_type<
             lambda_functor, 
             open_args<null_type, null_type, null_type> >::type
         >(const_null_type(), const_null_type(), const_null_type()); 
  }

  template<class RET>
  RET ret_call() const {
    return inherited:: template call<RET>(const_null_type(), 
                                    const_null_type(), 
                                    const_null_type());
  }

  BOOST_LAMBDA_LAMBDA_FUNCTOR_ASSIGNMENT
  BOOST_LAMBDA_LAMBDA_FUNCTOR_SUBSCRIPT

};
 
// -- lambda_functor FIRST -------------------------------------------------
template <class Action, class Args>
class lambda_functor<lambda_functor_args<Action, Args, FIRST> > 
  : public lambda_functor_base<Action, Args>
{ 
public:
  typedef lambda_functor_base<Action, Args> inherited;

  explicit lambda_functor(const Args& args) 
    : inherited(args) {}

  // lambda functors can be copied, if arity and action are the same
  // and Args tuples copyable
  template <class Args2> lambda_functor
    (const lambda_functor<lambda_functor_args<Action, Args2, FIRST> >& f)
      : inherited(f.args) {}

  template <class SigArgs> struct sig {
    typedef typename 
      detail::lambda_functor_sig<lambda_functor, 1, SigArgs>::type type;
  };

  template<class A>
  typename 
    return_type<lambda_functor, open_args<A&, null_type, null_type> >::type
  operator()(A& a) const
  { 
     return inherited::template call<
       typename return_type<
         lambda_functor, open_args<A&, null_type, null_type> 
       >::type
     >(a, const_null_type(), const_null_type());
  }

  template<class RET, class A>
  RET ret_call(A& a) const
  { 
    return inherited:: template call<RET>(a, const_null_type(), const_null_type()); 
  }

  BOOST_LAMBDA_LAMBDA_FUNCTOR_ASSIGNMENT
  BOOST_LAMBDA_LAMBDA_FUNCTOR_SUBSCRIPT

};

// -- lambda_functor SECOND  -------------------------------------------------
template <class Action, class Args>
class lambda_functor<lambda_functor_args<Action, Args, SECOND> > 
  : public lambda_functor_base<Action, Args>, public has_sig
{ 
public:
  typedef lambda_functor_base<Action, Args> inherited;

  explicit lambda_functor(const Args& args) 
    : inherited(args) {}

  // lambda functors can be copied, if arity and action are the same
  // and Args tuples copyable
  template <class Args2> lambda_functor
    (const lambda_functor<lambda_functor_args<Action, Args2, SECOND> >& f)
      : inherited(f.args) {}


  template <class SigArgs> struct sig {
    typedef typename 
      detail::lambda_functor_sig<lambda_functor, 2, SigArgs>::type type;
  };
  
  template<class A, class B>
  typename return_type<lambda_functor, open_args<A&, B&, null_type> >::type
  operator()(A& a, B& b) const 
  { 
     return inherited::template call<
       typename return_type<
         lambda_functor, open_args<A&, B&, null_type> 
       >::type>(a, b, const_null_type()); 
  }

  // currying call: creates another lambda functor
  template<class A>
  sig<tuple<lambda_functor, A&> >::type
//    lambda_functor<
//      lambda_functor_args<
//        action<3, curry_action<1> >,
//        detail::bind_tuple_mapper<lambda_functor, const A>::type,
//        FIRST
//      > 
//    >
  operator()(A& a) const 
  {
  return 
  typename sig<tuple<lambda_functor, A&> >::type
//    lambda_functor<
//      lambda_functor_args<
//        action<3, curry_action<1> >,
//        detail::bind_tuple_mapper<lambda_functor, const A>::type,
//        FIRST
//      >
//    > 
  ( 
      tuple<lambda_functor, 
            typename detail::remove_const_reference<A&>::type>(*this, a)
    );
  }

  template<class RET, class A, class B>
  RET ret_call(A& a, B& b) const { 
     return inherited::template call<RET>(a, b, const_null_type()); 
  }


  BOOST_LAMBDA_LAMBDA_FUNCTOR_ASSIGNMENT
  BOOST_LAMBDA_LAMBDA_FUNCTOR_SUBSCRIPT

};

// -- lambda_functor THIRD -------------------------------------------------
template <class Action, class Args>
class lambda_functor<lambda_functor_args<Action, Args, THIRD> > : public lambda_functor_base<Action, Args>, public has_sig
{ 
public:
  typedef lambda_functor_base<Action, Args> inherited;
 
  explicit lambda_functor(const Args& args) 
    : inherited(args) {}
    
  // lambda functors can be copied, if arity and action are the same
  // and Args tuples copyable
  template <class Args2> lambda_functor
    (const lambda_functor<lambda_functor_args<Action, Args2, THIRD> >& f)
      : inherited(f.args) {}

  template <class SigArgs> struct sig {
    typedef typename 
      detail::lambda_functor_sig<lambda_functor, 3, SigArgs>::type type;
  };

  template<class A, class B, class C>
  typename return_type<lambda_functor, open_args<A&, B&, C&> >::type 
  operator()(A& a, B& b, C& c) const
  { 
     return inherited::template call<
       typename return_type<lambda_functor, open_args<A&, B&, C&> 
     >::type>(a, b, c); 
  }
  template<class RET, class A, class B, class C>
  RET ret_call(A& a, B& b, C& c) const { 
     return inherited::template call<RET>(a, b, c); 
  }

  // currying call, one argument still missing
  template<class A, class B>
  sig<tuple<lambda_functor, A&, B&> >::type
//    lambda_functor<
//      lambda_functor_args<
//        action<4, curry_action<2> >,
//        detail::bind_tuple_mapper<lambda_functor, const A, const B>::type,
//        FIRST
//      > 
//    >
  operator()(A& a, B& b) const 
  {
    return 
    typename sig<tuple<lambda_functor, A&, B&> >::type
//      lambda_functor<
//        lambda_functor_args<
//          action<4, curry_action<2> >,
//          detail::bind_tuple_mapper<lambda_functor, const A, const B>::type,
//          FIRST
//        > 
//      >
    (   tuple<
          lambda_functor, 
          typename detail::remove_const_reference<A&>::type,
          typename detail::remove_const_reference<B&>::type
        > (*this, a, b)
    );
  }

  // currying call, two arguments still missing
  template<class A>
  sig<tuple<lambda_functor, A&> >::type
//    lambda_functor<
//      lambda_functor_args<
//        action<4, curry_action<1> >,
//        detail::bind_tuple_mapper<lambda_functor, const A>::type,
//        SECOND
//      > 
//  >
  operator()(A& a) const 
  {
  return 
    typename sig<tuple<lambda_functor, A&> >::type
//    lambda_functor<
//      lambda_functor_args<
//        action<4, curry_action<1> >,
//        detail::bind_tuple_mapper<lambda_functor, const A>::type,
//        SECOND
//      > 
//    > 
  ( 
        tuple<lambda_functor, typename detail::remove_const_reference<A&>::type>(*this, a)
    );
  }


  BOOST_LAMBDA_LAMBDA_FUNCTOR_ASSIGNMENT
  BOOST_LAMBDA_LAMBDA_FUNCTOR_SUBSCRIPT

};

// -- lambda_functor (Arbitrary Code) ---------------------------------------
//  matches any arity code with EXCEPTION or RETHROW bits on

//  This specialisation is only instantiated if delayed exception 
//  handling is used. See exceptions.hpp.
// ----------------------------------------------------------
template <class Action, class Args, int Code>
class lambda_functor<lambda_functor_args<Action, Args, Code> > 
  : public lambda_functor_base<Action, Args>
{ 
public:
  typedef lambda_functor_base<Action, Args> inherited;

  explicit lambda_functor(const Args& args) 
    : inherited(args) {}

  // lambda functors can be copied, if arity and action are the same
  // and Args tuples copyable
  template <class Args2> lambda_functor
    (const lambda_functor<lambda_functor_args<Action, Args2, Code> >& f)
      : inherited(f.args) {}


  // No operator() for this, since this lambda_functor can only be used 
  // in a catch_exception or catch_all

  template<class RET, class A, class B, class C>
  RET ret_call(A& a, B& b, C& c) const
  { 
    return inherited::template call<RET>(a, b, c); 
  }

};


// any lambda functor can be turned into a const_incorrect_lambda_functor
// The operator() takes arguments as consts and then casts constness
// away. So this breaks const correctness!!! but is a necessary workaround
// in some cases due to language limitations.
// Note, that this is not a lambda_functor anymore, so it can not be used
// as a sub lambda expression.

template <class Arg> 
struct const_incorrect_lambda_functor 
  : private lambda_functor<Arg> {
public:
  BOOST_STATIC_ASSERT(dig_arity<Arg>::value <= THIRD); 
  // only allowed for normal lambda functions, not EXCEPTION ones

  typedef lambda_functor<Arg> inherited;
 
  explicit const_incorrect_lambda_functor(const lambda_functor<Arg>& lf) 
    : inherited(lf.args) {}
    

  template <class SigArgs> struct sig {
    typedef typename 
      lambda_functor<Arg>::template sig<SigArgs>::type type;
  };

  sig<tuple<lambda_functor<Arg> > >::type  
  operator()() const {
    return inherited::template ret_call<typename sig<tuple<lambda_functor<Arg> > >::type>(); 
  }

  template<class A>
  sig<tuple<lambda_functor<Arg>, A&> >::type 
  operator()(const A& a) const {
    return inherited::template ret_call<typename sig<tuple<lambda_functor<Arg>, A&> >::type >(const_cast<A&>(a)); 
  }

  template<class A, class B>
  sig<tuple<lambda_functor<Arg>, A&, B&> >::type 
  operator()(const A& a, const B& b) const {
    return inherited::template ret_call<typename sig<tuple<lambda_functor<Arg>, A&, B&> >::type >(const_cast<A&>(a), const_cast<B&>(b)); 
  }

  template<class A, class B, class C>
  sig<tuple<lambda_functor<Arg>, A&, B&, C&> >::type 
  operator()(const A& a, const B& b, const C& c) const {
    return inherited::template ret_call<typename sig<tuple<lambda_functor<Arg>, A&, B&, C&> >::type>(const_cast<A&>(a), const_cast<B&>(b), const_cast<C&>(c)); 
  }
};

// ------------------------------------------------------------------------
// any lambda functor can be turned into a const_parameter_lambda_functor
// The operator() takes arguments as const.
// This is useful if lambda functors are called with non-const rvalues.
// Note, that this is not a lambda_functor anymore, so it can not be used
// as a sub lambda expression.

template <class Arg> 
struct const_parameter_lambda_functor 
  : private lambda_functor<Arg> {
public:
  BOOST_STATIC_ASSERT(dig_arity<Arg>::value <= THIRD); 
  // only allowed for normal lambda functions, not EXCEPTION ones

  typedef lambda_functor<Arg> inherited;
 
  explicit const_parameter_lambda_functor(const lambda_functor<Arg>& lf) 
    : inherited(lf.args) {}
    

  template <class SigArgs> struct sig {
    typedef typename 
      lambda_functor<Arg>::template sig<SigArgs>::type type;
  };

  // This is provided just for completeness; no arguments, no constness
  // problems. 

  sig<tuple<lambda_functor<Arg> > >::type  
  operator()() const {
    return inherited::template ret_call<typename sig<tuple<lambda_functor<Arg> > >::type>(); 
  }

  template<class A>
  sig<tuple<lambda_functor<Arg>, const A&> >::type 
  operator()(const A& a) const {
    return inherited::template ret_call<typename sig<tuple<lambda_functor<Arg>, const A&> >::type >(a); 
  }

  template<class A, class B>
  sig<tuple<lambda_functor<Arg>, const A&, const B&> >::type 
  operator()(const A& a, const B& b) const {
    return inherited::template ret_call<typename sig<tuple<lambda_functor<Arg>, const A&, const B&> >::type >(a, b); 
  }

  template<class A, class B, class C>
  sig<tuple<lambda_functor<Arg>, const A&, const B&, const C&> >::type 
  operator()(const A& a, const B& b, const C& c) const {
    return inherited::template ret_call<typename sig<tuple<lambda_functor<Arg>, const A&, const B&, const C&> >::type>(a, b, c); 
  }
};


// -- free variables types -------------------------------------------------- 
   
template <int I> class placeholder {};
   
typedef const lambda_functor<placeholder<FIRST> >  free1_type;
typedef const lambda_functor<placeholder<SECOND> > free2_type;
typedef const lambda_functor<placeholder<THIRD> >  free3_type;
   
// free variables are lambda_functors. This is to allow uniform handling with 
// other lambda_functors.
// -------------------------------------------------------------------
	 
   
  // Tagged lambda_functor -------------
  // This is a generic class for special types of lambda functors, 
  // e.g. certain parameters of switch_statement must be case_statements,
  // rather than arbitrary lambda functors


template<class Tag, class LambdaFunctor>
class tagged_lambda_functor;

template<class Tag, class Args>
class tagged_lambda_functor<Tag, lambda_functor<Args> > 
  : public lambda_functor<Args> 
{
public:
  template<class T>
  tagged_lambda_functor(const lambda_functor<T>& a) 
    : lambda_functor<Args>(a) {}

  // only works for the no body case.
  explicit tagged_lambda_functor() : lambda_functor<Args>( null_type() ) {}
};

#undef BOOST_LAMBDA_LAMBDA_FUNCTOR_ASSIGNMENT
#undef BOOST_LAMBDA_LAMBDA_FUNCTOR_ADDRESSOF
#undef BOOST_LAMBDA_LAMBDA_FUNCTOR_SUBSCRIPT


} // namespace lambda
} // namespace boost

#endif


