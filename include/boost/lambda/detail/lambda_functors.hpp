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

// -- lambda_functor NONE ------------------------------------------------
template <class Action, class Args>
class lambda_functor<lambda_functor_args<Action, Args, NONE> > 
  : public lambda_functor_base<Action, Args>
{
public:
  typedef lambda_functor_base<Action, Args> inherited;

  explicit lambda_functor(const Args& args) 
    : inherited(args) {} 

  typename 
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
  : public lambda_functor_base<Action, Args>
{ 
public:
  typedef lambda_functor_base<Action, Args> inherited;

  explicit lambda_functor(const Args& args) 
    : inherited(args) {}

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
  lambda_functor<
    lambda_functor_args<
      action<3, curry_action<1> >,
      detail::bind_tuple_mapper<lambda_functor, const A>::type,
      FIRST
    > 
  >
  operator()(A& a) const 
  {
  return 
  lambda_functor<
    lambda_functor_args<
      action<3, curry_action<1> >,
      detail::bind_tuple_mapper<lambda_functor, const A>::type,
      FIRST
    > 
  > ( typename 
        detail::bind_tuple_mapper<lambda_functor, const A>::type(*this, a)
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
class lambda_functor<lambda_functor_args<Action, Args, THIRD> > : public lambda_functor_base<Action, Args>
{ 
public:
  typedef lambda_functor_base<Action, Args> inherited;
 
  explicit lambda_functor(const Args& args) 
    : inherited(args) {}
    
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
  lambda_functor<
    lambda_functor_args<
      action<4, curry_action<2> >,
      detail::bind_tuple_mapper<lambda_functor, const A, const B>::type,
      FIRST
    > 
  >
  operator()(A& a, B& b) const 
  {
    return 
    lambda_functor<
      lambda_functor_args<
        action<4, curry_action<2> >,
        detail::bind_tuple_mapper<lambda_functor, const A, const B>::type,
        FIRST
      > 
    >
    ( typename 
        detail::bind_tuple_mapper<lambda_functor, const A, const B>::type
          (*this, a, b)
    );
  }

  // currying call, two arguments still missing
  template<class A>
  lambda_functor<
    lambda_functor_args<
      action<4, curry_action<1> >,
      detail::bind_tuple_mapper<lambda_functor, const A>::type,
      SECOND
    > 
  >
  operator()(A& a) const 
  {
  return 
  lambda_functor<
    lambda_functor_args<
      action<4, curry_action<1> >,
      detail::bind_tuple_mapper<lambda_functor, const A>::type,
      SECOND
    > 
  > ( typename 
        detail::bind_tuple_mapper<lambda_functor, const A>::type(*this, a)
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

  // No operator() for this, since this lambda_functor can only be used 
  // in a catch_exception or catch_all

  template<class RET, class A, class B, class C>
  RET ret_call(A& a, B& b, C& c) const
  { 
    return inherited::template call<RET>(a, b, c); 
  }

};

// This subclass adds lambda functors the ability to be copied,
// if the functors are 'copy compatible'
// This ability is needed, if lambda functor evaluation results in 
// a lambda functor (e.g. with protect).
template <class Act, class Args, int Code> 
struct lambda_functor_sub<lambda_functor_args<Act, Args, Code> > 
  : public lambda_functor<lambda_functor_args<Act, Args, Code> > {

  // as long as action and arity are the same, lambda functors are convertible
  // if the argument tuples are.
  template <class Args2> lambda_functor_sub
    (const lambda_functor<lambda_functor_args<Act, Args2, Code> >& f)
      : lambda_functor<lambda_functor_args<Act, Args, Code> >(f.args) {}
};

// any lambda functor can turned into const_incorrect_lambda_functor
// The opreator() takes arguments as consts and then casts constness
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
    

  // This is provided just for completeness; no arguments, no constness
  // problems. 
  typename return_type<inherited, 
             open_args<null_type, null_type, null_type> >::type 
  operator()() const
  { 
     return inherited::template ret_call<
       typename return_type<
                  inherited, 
                  open_args<null_type, null_type, null_type> 
                >::type>(); 
  }

  template<class A>
  typename return_type<inherited, open_args<A&, null_type, null_type> >::type 
  operator()(const A& a) const
  { 
     return inherited::template ret_call<
       typename return_type<inherited, open_args<A&, null_type, null_type> 
     >::type>(const_cast<A&>(a)); 
  }
  template<class A, class B>
  typename return_type<inherited, open_args<A&, B&, null_type> >::type 
  operator()(const A& a, const B& b) const
  { 
     return inherited::template ret_call<
       typename return_type<inherited, open_args<A&, B&, null_type> 
     >::type>(const_cast<A&>(a), const_cast<B&>(b)); 
  }
  template<class A, class B, class C>
  typename return_type<inherited, open_args<A&, B&, C&> >::type 
  operator()(const A& a, const B& b, const C& c) const
  { 
     return inherited::template ret_call<
       typename return_type<inherited, open_args<A&, B&, C&> 
     >::type>(const_cast<A&>(a), const_cast<B&>(b), const_cast<C&>(c)); 
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
