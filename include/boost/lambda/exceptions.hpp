// -- Boost Lambda Library -- exceptions.hpp ----------------
//
// Copyright (C) 2000 Gary Powell (gwpowell@hotmail.com)
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

// -----------------------------------------------------

#if !defined(BOOST_LAMBDA_EXCEPTIONS_HPP)
#define BOOST_LAMBDA_EXCEPTIONS_HPP

namespace boost { 
namespace lambda {

typedef lambda_functor<placeholder<EXCEPTION> > freeE_type;

namespace {
  boost::lambda::freeE_type freeE;
  boost::lambda::freeE_type& _E = freeE;        
}

// -- try_catch arity_deduction --------------------------------
// maps the arity_code from catch parts correctly
// eg:
// try_catch ( bind(f), catch_exception<int>( cout << free1 << free2 ))(a, b);
// should now work

namespace detail {

template <class A1 = null_type, class A2 = null_type, class A3 = null_type, 
          class A4 = null_type, class A5 = null_type, class A6 = null_type, 
          class A7 = null_type, class A8 = null_type, class A9 = null_type, 
          class A10 = null_type> 
struct combine_try_catch_arities {

  // the try lambda_functor (A1) is taken as it is, 
  // EXCEPTION and RETHROW bits are masked away
  // from the catch lambda_functors (A2 and greater )
  // (eventually, EXCEPTION and RETHROW bits in try part lead to an error)
    static const int ored_value = 
      dig_arity<A1>::value |
        (
          ( 
             dig_arity<A2>::value | 
             dig_arity<A3>::value | 
             dig_arity<A4>::value | 
             dig_arity<A5>::value | 
             dig_arity<A6>::value | 
             dig_arity<A7>::value | 
             dig_arity<A8>::value | 
             dig_arity<A9>::value | 
             dig_arity<A10>::value
          ) 
          & 
          (FIRST | SECOND | THIRD)
        );

  // leave the highest placeholder bit on, set the lower off
  // EXCEPTION and RETHROW bits are retained as they are
  static const int value = (ored_value & THIRD
	          ? THIRD 
                  : (ored_value & SECOND
                       ? SECOND 
                       : ored_value)) | ( (EXCEPTION | RETHROW) & ored_value);

};

} // namespace detail

// -- exception related actions -------------------

// catch actions.
template <class Catch1, class Catch2 = null_type, class Catch3 = null_type, 
          class Catch4 = null_type, class Catch5 = null_type, 
          class Catch6 = null_type, class Catch7 = null_type, 
          class Catch8 = null_type, class Catch9 = null_type, 
          class Catch10 = null_type>
struct catch_action {};

struct catch_all_action {};

template<class CatchActions>
struct return_try_catch_action {};

template<class CatchActions>
struct try_catch_action {};

// rethrow actions
struct throw_new_action {};
struct rethrow_action {};

template<class ThrowType> class throw_action;

template<>
struct throw_action<rethrow_action> {
  template<class RET>
  static RET apply() {
    throw;
  }
};

template<> struct throw_action<throw_new_action> {
  template<class RET, class T>
  static RET apply(T& t) {
    throw t;
  }
};

// return types for throw_actions --------------------------------------------
template<class Open>
struct 
return_type<
  lambda_functor_args<
    action<0, throw_action<rethrow_action> >, 
    null_type, 
    RETHROW
  >, 
  Open
> 
{
 typedef void type;
};

template<class Args, int Code, class Open>
struct 
return_type<
  lambda_functor_args<
    action<1, throw_action<throw_new_action> >, 
    Args, 
    Code
  >, 
  Open> 
{
  typedef void type;
};

// return types deductions -------------------------------------------------

// the return type of try_catch is the return type of the try lambda_functor
// (the return types of try and catch parts must match unless try returns void
// or the catch part throws for sure)

template<class CatchActionList, class Args, int Code, class Open>
struct 
return_type<
  lambda_functor_args<
action<2, try_catch_action<CatchActionList> >, Args, Code
  >, 
  Open
> 
{
  typedef 
    typename return_type<typename detail::tuple_element_as_reference<0, Args>::type, Open>::type type;
};

template<class CatchActionList, class Args, int Code, class Open>
struct 
  return_type<
    lambda_functor_args<action<3, try_catch_action<CatchActionList> >, Args, Code>,
    Open
  > 
{
  typedef 
     typename return_type<
       typename detail::tuple_element_as_reference<0, Args>::type, Open
     >::type type;
};

template<int I, class CatchActionList, class Args, int Code, class Open>
struct 
return_type<
  lambda_functor_args<action<I, try_catch_action<CatchActionList> >, Args, Code>, 
  Open
> 
{
  typedef 
     typename return_type<
       typename detail::tuple_element_as_reference<0, Args>::type, Open
     >::type type;
};

// NOTE, the exception placeholder deduction rule is defined 
// in return_type_traits.hpp



// defined in control_constructs
class ifthenelse_action;

namespace detail {

// Templates for deducing, wether a lambda_functor throws inevitably of not -
// This mechanism is needed to make the compiler happy about
// return types of try and catch parts. 

// a lambda_functor throws for sure if:
//  - it is a throw expression
//  - it is a comma expression, and one of its arguments throws for sure
//  - it is an if_then_else expression and either the if statement or both 
//  the then and  else throw.
// (there are other cases as well, but we do not cover them)
// e.g. free1 + (rethrow(), 3) does throw for sure but this is not checked
// This implies, that in such a case, the return types of try and catch parts 
// must match if the try part returns other than void.
// (Such checks could be done though)

template <class Arg> 
struct throws_for_sure_phase2 {
  static const bool value = false;
};

template <int N, class ThrowType, class Args, int Code> 
struct throws_for_sure_phase2<
  lambda_functor< 
    lambda_functor_args<action<N, throw_action<ThrowType> >, Args, Code> 
  > 
>
{
  static const bool value = true;
};

// Both then and else or the if throw of an if_then_else.
template <class Args, int Code> 
struct throws_for_sure_phase2<
  lambda_functor<
    lambda_functor_args<
      action<3, return_void_action<ifthenelse_action> >, Args, Code
    > 
  > 
>
{
  static const bool value =
    throws_for_sure_phase2<
      typename boost::tuples::element<0, Args>::type>::value
    ||  
    (
       throws_for_sure_phase2<
         typename boost::tuples::element<1, Args>::type
       >::value
       && 
       throws_for_sure_phase2<
         typename boost::tuples::element<2, Args>::type
       >::value
    );
};

template <class Args, int Code> 
struct throws_for_sure_phase2<
  lambda_functor< 
    lambda_functor_args< action<2, other_action<comma_action> >, Args, Code> 
  > 
>
{
  static const bool value =
    throws_for_sure_phase2<
      typename boost::tuples::element<0, Args>::type
    >::value
    || 
    throws_for_sure_phase2<
      typename boost::tuples::element<1, Args>::type
    >::value;
};

  // get rid of any qualifiers and references
  // lambda_functors should be stored like that, so this is to be extra sure 
template <class Arg> 
struct throws_for_sure {
  static const bool value 
    = throws_for_sure_phase2<
        typename detail::remove_reference_and_cv<Arg>::type
      >::value;
};


// -- return_or_throw templates -----------------------------

// false case, catch and try return types are incompatible
// Now the catch part must throw for sure, otherwise a compile time error
// occurs.
template<bool is_conversion>
struct return_or_throw_phase2 {
  template<class RET, class Arg, class A, class B, class C>
  static RET call(Arg& arg, A& a, B& b, C& c) {
    BOOST_STATIC_ASSERT(throws_for_sure<Arg>::value);
    detail::select(arg, a, b, c); // this line throws
    throw 1; // this line is never performed, hence 1 is just a dummy
             // The line is needed to make compiler happy and not require
             // a matching return type
  }
};

// the try and catch return types are compatible
template<>
struct return_or_throw_phase2<true> {
  template<class RET, class Arg, class A, class B, class C>
  static RET call(Arg& arg, A& a, B& b, C& c) {
    return detail::select(arg, a, b, c);
  }
};


// the non-void case. Try part returns a value, so catch parts must 
// return a value of the same type or throw
template<class RET, class ARG>
struct return_or_throw {
  // Arg should be equal to ARG except that ARG may be a reference
  // to be sure, that there are no suprises for peculiarly defined return types
  // ARG is passed explicitely
  template<class Arg, class A, class B, class C>
  static RET call(Arg& arg, A& a, B& b, C& c)
  {        
    typedef typename return_type<ARG, open_args<A&, B&, C&> >::type RT;        

    return 
      return_or_throw_phase2<
        ::boost::is_convertible<RT, RET>::value
      >::template call<RET>(arg, a, b, c);
  }
};

// if try part returns void, we do not return the catch parts either
template<class ARG>
struct return_or_throw<void, ARG> {
  template<class Arg, class A, class B, class C>
  static void call(Arg& arg, A& a, B& b, C& c) { detail::select(arg, a, b, c); }
};

} // end detail

// Throwing exceptions ---------------------------------------------

namespace detail {

template <class T> struct catch_block {}; 
struct catch_all_block {};

template <class T> struct exception_catch_tag {};

// normal catch block is represented as
// tagged_lambda_functor<exception_catch_tag<catch_type<T> > >, LambdaFunctor>
  
// the default catch all block as:
// tagged_lambda_functor<exception_catch_tag<catch_all_block> >, LambdaFunctor>


}; // end detail

// the code is RETHROW, this ensures that a compile time error results, 
// if this lambda_functor is used outside a delayed catch_expression
inline const 
lambda_functor< 
  lambda_functor_args< 
    action<0, throw_action<rethrow_action> >, 
    null_type, 
    RETHROW
  > 
>
rethrow() { 
  return 
    lambda_functor< 
      lambda_functor_args< 
        action<0, throw_action<rethrow_action> >, 
        null_type, 
        RETHROW
      > 
    >
    ( null_type() );
}

template <class Arg1>
inline const 
lambda_functor<
  lambda_functor_args< 
    action<1, throw_action<throw_new_action> >, 
    tuple<typename const_copy_argument<const Arg1>::type>, 
    combine_arities<Arg1>::value
  > 
>
throw_exception(const Arg1& a1) { 
  return 
    lambda_functor< 
      lambda_functor_args< 
        action<1, throw_action<throw_new_action> >, 
        tuple<typename const_copy_argument<const Arg1>::type>, 
        combine_arities<Arg1>::value
      > 
    >
    ( tuple<typename const_copy_argument<const Arg1>::type>(a1));
}

// create catch blocks
template <class CatchType, class Arg>
inline const 
tagged_lambda_functor<
  detail::exception_catch_tag<detail::catch_block<CatchType> >, 
  lambda_functor<Arg> 
> 
catch_exception(const lambda_functor<Arg>& a) { 
  // the third placeholder cannot be used in catch_exception
  BOOST_STATIC_ASSERT((dig_arity<Arg>::value & THIRD) == 0);
  return 
    tagged_lambda_functor<
      detail::exception_catch_tag<detail::catch_block<CatchType> >, 
      lambda_functor<Arg> 
    > (a);
}

// catch and do nothing case.
template <class CatchType, class Arg>
inline const 
tagged_lambda_functor<
  detail::exception_catch_tag<detail::catch_block<CatchType> >, 
  lambda_functor<
    lambda_functor_args<
      action<0, return_void_action<do_nothing_action> >,
      null_type, 
      NONE
    > 
  >
>
catch_exception() { 
  return 
    tagged_lambda_functor<
      detail::exception_catch_tag<detail::catch_block<CatchType> >, 
      lambda_functor<
        lambda_functor_args<
          action<0, return_void_action<do_nothing_action> >,
          null_type, 
          NONE
        > 
      >
    > (null_type());
}

// create catch(...) blocks
template <class Arg>
inline const 
tagged_lambda_functor<
  detail::exception_catch_tag<detail::catch_all_block>, 
  lambda_functor<Arg> 
> 
catch_all(const lambda_functor<Arg>& a) { 
  // the third placeholder cannot be used in catch_exception
  BOOST_STATIC_ASSERT((dig_arity<Arg>::value & THIRD) == 0);
  return 
    tagged_lambda_functor<
      detail::exception_catch_tag<detail::catch_all_block>, 
      lambda_functor<Arg> 
    > (a);
}

// catch(...) and do nothing case.
template <class CatchType, class Arg>
inline const 
tagged_lambda_functor<
  detail::exception_catch_tag<detail::catch_all_block>, 
  lambda_functor<
    lambda_functor_args<
      action<0, return_void_action<do_nothing_action> >,
      null_type, 
      NONE
    > 
  >
>
catch_all() { 
  return 
    tagged_lambda_functor<
      detail::exception_catch_tag<detail::catch_all_block>, 
      lambda_functor<
        lambda_functor_args<
          action<0, return_void_action<do_nothing_action> >,
          null_type, 
          NONE
        > 
      > 
    > (null_type());
}

// try_catch functions --------------------------------
// The second -> N argument(s) are must be catch lambda_functors 
template <class TryArg, class Catch1, class LF1>
inline const 
lambda_functor< 
  lambda_functor_args< 
    action<2, try_catch_action<catch_action<Catch1> > >, 
    tuple<lambda_functor<TryArg>, LF1>, 
    detail::combine_try_catch_arities<TryArg, LF1>::value
  > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<Catch1>, LF1>& a2) 
{ 
  return lambda_functor< 
    lambda_functor_args< 
      action<2, try_catch_action<catch_action<Catch1> > >, 
      tuple<lambda_functor<TryArg>, LF1>, 
      detail::combine_try_catch_arities<TryArg, LF1>::value
    > 
  > ( tuple< lambda_functor<TryArg>, LF1>(a1, a2));
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2>
inline const 
  lambda_functor< 
    lambda_functor_args< 
      action<3, try_catch_action<catch_action<detail::catch_block<Catch1>, Catch2> > >, 
      tuple<lambda_functor<TryArg>, LF1, LF2>, 
      detail::combine_try_catch_arities<TryArg, LF1, LF2>::value
    > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch2>, LF2>& a3) 
{ 
  return lambda_functor< 
    lambda_functor_args<
      action<3, try_catch_action<catch_action<detail::catch_block<Catch1>, Catch2> > >, 
      tuple<lambda_functor<TryArg>, LF1, LF2>, 
      detail::combine_try_catch_arities<TryArg, LF1, LF2>::value
    > 
  >
  ( tuple<lambda_functor<TryArg>, LF1, LF2>(a1, a2, a3));
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2, 
			class Catch3, class LF3>
inline const lambda_functor< 
  lambda_functor_args< 
    action<4, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, Catch3> > >, 
    tuple<lambda_functor<TryArg>, LF1, LF2, LF3>, 
    detail::combine_try_catch_arities<TryArg, LF1, LF2, LF3>::value
  > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch2> >, LF2>& a3,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch3>, LF3>& a4) 
{ 
  return 
    lambda_functor< 
      lambda_functor_args< 
        action<4, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, Catch3> > >, 
        tuple<lambda_functor<TryArg>, LF1, LF2, LF3>, 
	detail::combine_try_catch_arities<TryArg, LF1, LF2, LF3>::value
      > 
    >
    ( tuple<lambda_functor<TryArg>, LF1, LF2, LF3>(a1, a2, a3, a4));
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2, 
			class Catch3, class LF3, 
			class Catch4, class LF4>
inline const 
lambda_functor< 
  lambda_functor_args< 
    action<
      5, 
      try_catch_action<
        catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, Catch4> 
      > 
    >, 
    tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4>, 
    detail::combine_try_catch_arities<TryArg, LF1, LF2, LF3, LF4>::value
  > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch2> >, LF2>& a3,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch3> >, LF3>& a4,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch4>, LF4>& a5) 
{ 
  return 
    lambda_functor< 
      lambda_functor_args< 
        action<
          5, 
          try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, Catch4> > 
        >, 
        tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4>, 
	detail::combine_try_catch_arities<TryArg, LF1, LF2, LF3, LF4>::value
      > 
    >
    ( tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4>(a1, a2, a3, a4, a5));
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2, 
			class Catch3, class LF3, 
			class Catch4, class LF4, 
			class Catch5, class LF5>
inline const 
lambda_functor< 
  lambda_functor_args< 
    action<
      6, 
      try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, Catch5> >
    >, 
    tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5>, 
    detail::combine_try_catch_arities<TryArg, LF1, LF2, LF3, LF4, LF5>::value
  > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch2> >, LF2>& a3,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch3> >, LF3>& a4,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch4> >, LF4>& a5,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch5>, LF5>& a6) 
{ 
  return 
    lambda_functor< 
      lambda_functor_args< 
         action<
           6, 
           try_catch_action<
             catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, Catch5> 
           > 
         >, 
         tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5>, 
	 detail::combine_try_catch_arities<
            TryArg, LF1, LF2, LF3, LF4, LF5
         >::value
      > 
    >
    ( tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5>
        (a1, a2, a3, a4, a5, a6)
    );
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2, 
			class Catch3, class LF3, 
			class Catch4, class LF4, 
			class Catch5, class LF5, 
			class Catch6, class LF6>
inline const 
lambda_functor< 
  lambda_functor_args< 
    action<
      7, 
      try_catch_action<
        catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, Catch6> 
      > 
    >, 
    tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6>, 
    detail::combine_try_catch_arities<
       TryArg, LF1, LF2, LF3, LF4, LF5, LF6
    >::value
  > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch2> >, LF2>& a3,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch3> >, LF3>& a4,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch4> >, LF4>& a5,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch5> >, LF5>& a6,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch6>, LF6>& a7) 
{ 
  return 
    lambda_functor< 
      lambda_functor_args< 
        action<
          7, 
          try_catch_action<
            catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>,Catch6> 
          > 
        >, 
        tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6>, 
	detail::combine_try_catch_arities<
          TryArg, LF1, LF2, LF3, LF4, LF5, LF6
        >::value
      > 
    >
    ( tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6>
        (a1, a2, a3, a4, a5, a6, a7));
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2, 
			class Catch3, class LF3, 
			class Catch4, class LF4, 
			class Catch5, class LF5, 
			class Catch6, class LF6,
                        class Catch7, class LF7>
inline const 
lambda_functor< 
  lambda_functor_args< 
    action<
      8, 
      try_catch_action<
        catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>, Catch7> 
      > 
    >, 
    tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7>, 
    detail::combine_try_catch_arities<
       TryArg, LF1, LF2, LF3, LF4, LF5, LF6, LF7
    >::value
  > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch2> >, LF2>& a3,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch3> >, LF3>& a4,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch4> >, LF4>& a5,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch5> >, LF5>& a6,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch6> >, LF6>& a7,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch7>, LF7>& a8) 
{ 
  return 
    lambda_functor< 
      lambda_functor_args< 
        action<
          8, 
          try_catch_action<
            catch_action<
              detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>, Catch7
            > 
          > 
        >, 
        tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7>, 
	detail::combine_try_catch_arities<
          TryArg, LF1, LF2, LF3, LF4, LF5, LF6, LF7
        >::value
      > 
    >
    ( tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7>
        (a1, a2, a3, a4, a5, a6, a7, a8));
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2, 
			class Catch3, class LF3, 
			class Catch4, class LF4, 
			class Catch5, class LF5, 
			class Catch6, class LF6, 
			class Catch7, class LF7, 
			class Catch8, class LF8>
inline const 
lambda_functor< 
  lambda_functor_args< 
    action<
      9, 
      try_catch_action<
        catch_action<
          detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>, detail::catch_block<Catch7>, Catch8
        > 
      > 
    >, 
    tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8>, 
    detail::combine_try_catch_arities<
      TryArg, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8
    >::value
  > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch2> >, LF2>& a3,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch3> >, LF3>& a4,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch4> >, LF4>& a5,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch5> >, LF5>& a6,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch6> >, LF6>& a7,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch7> >, LF7>& a8,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch8>, LF8>& a9) 
{ 
  return 
    lambda_functor< 
      lambda_functor_args< 
        action<
          9,
          try_catch_action<
            catch_action<
              detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>, detail::catch_block<Catch7>, Catch8
            > 
          > 
        >, 
        tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8>, 
	detail::combine_try_catch_arities<
          TryArg, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8
        >::value
      > 
    >
    ( tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8>
        (a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2, 
			class Catch3, class LF3, 
                        class Catch4, class LF4, 
			class Catch5, class LF5, 
			class Catch6, class LF6, 
			class Catch7, class LF7, 
			class Catch8, class LF8, 
			class Catch9, class LF9>
inline const 
  lambda_functor< 
    lambda_functor_args< 
      action< 
        10, 
        try_catch_action<
          catch_action<
             detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>, detail::catch_block<Catch7>, detail::catch_block<Catch8>, 
             Catch9
          > 
        > 
      >, 
      tuple<
        lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8, LF9
      >, 
      detail::combine_try_catch_arities<
        TryArg, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8, LF9
      >::value
    > 
  >
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch2> >, LF2>& a3,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch3> >, LF3>& a4,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch4> >, LF4>& a5,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch5> >, LF5>& a6,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch6> >, LF6>& a7,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch7> >, LF7>& a8,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch8> >, LF8>& a9,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch9>, LF9>& a10) 
{ 
  return 
    lambda_functor< 
      lambda_functor_args< 
        action<
          10, 
          try_catch_action< 
            catch_action<
              detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>, detail::catch_block<Catch7>, detail::catch_block<Catch8>, 
              Catch9
            > 
          > 
        >, 
        tuple<
          lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8, LF9
        >, 
	detail::combine_try_catch_arities<
          TryArg, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8, LF9
        >::value
      > 
    >
    ( tuple<
        lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8, LF9
      >(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10));
}


// ---------------------------------------------------------------------------
// Specializations for lambda_functor_base of try_catch ----------------------

// 1 catch type case

template<class Args, class Catch1>
class lambda_functor_base<
  action<2, try_catch_action<catch_action<detail::catch_block<Catch1> > > >, 
  Args
> 
{
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);
    }
    catch (Catch1& e)
    {                
      return 
       detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
  }
};



template<class Args>
class lambda_functor_base<action<2, try_catch_action<catch_action<detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (...)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, c);
    }
  }
};


// 2 catch types case
template<class Args, class Catch1, class Catch2>
class lambda_functor_base<action<3, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    { 
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (Catch2& e)
    {          
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);
    }
  }
};

template<class Args, class Catch1>
class lambda_functor_base<action<3, try_catch_action<catch_action<detail::catch_block<Catch1>,detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (...)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, c);
    }
  }
};

// 3 catch types case
template<class Args, class Catch1, class Catch2, class Catch3>
class lambda_functor_base<action<4, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);

    }
    catch (Catch2& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);

    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), a, b, e);
    }
  }
};

template<class Args, class Catch1, class Catch2>
class lambda_functor_base<action<4, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>,detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (Catch2& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);
    }
    catch (...)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), a, b, c);
    }
  }
};

// 4 catch types case
template<class Args, class Catch1, class Catch2, class Catch3, class Catch4>
class lambda_functor_base<action<5, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), a, b, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), a, b, e);
    }
  }
};

template<class Args, class Catch1, class Catch2, class Catch3>
class lambda_functor_base<action<5, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>,detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), a, b, e);
    }
    catch (...)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), a, b, c);
    }
  }
};

// 5 catch types case
template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5>
class lambda_functor_base<action<6, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), a, b, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), a, b, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<5>(args), a, b, e);
    }
  }
};

template<class Args, class Catch1, class Catch2, class Catch3, class Catch4>
class lambda_functor_base<action<6, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>,detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), a, b, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), a, b, e);
    }
    catch (...)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), a, b, c);
    }
  }
};

// 6 catch types case
template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5, class Catch6>
class lambda_functor_base<action<7, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), a, b, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), a, b, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), a, b, e);
    }
    catch (Catch6& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), a, b, e);
    }
  }
};

template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5>
class lambda_functor_base<action<7, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>,detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), a, b, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), a, b, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), a, b, e);
    }
    catch (...)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), a, b, c);
    }
  }
};

// 7 catch types case
template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5, class Catch6,
                     class Catch7>
class lambda_functor_base<action<8, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>, detail::catch_block<Catch7> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), a, b, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), a, b, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), a, b, e);
    }
    catch (Catch6& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), a, b, e);
    }
    catch (Catch7& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<7, Args>::type>
               ::call(::boost::tuples::get<7>(args), a, b, e);
    }
  }
};

template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5, class Catch6>
class lambda_functor_base<action<8, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>,
                                                               detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), a, b, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), a, b, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), a, b, e);
    }
    catch (Catch6& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), a, b, e);
    }
    catch (...)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<7, Args>::type>
               ::call(::boost::tuples::get<7>(args), a, b, c);
    }
  }
};

// 8 catch types case
template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5, class Catch6,
                     class Catch7, class Catch8>
class lambda_functor_base<action<9, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>,
    detail::catch_block<Catch7>, detail::catch_block<Catch8> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), a, b, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), a, b, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), a, b, e);
    }
    catch (Catch6& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), a, b, e);
    }
    catch (Catch7& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<7, Args>::type>
               ::call(::boost::tuples::get<7>(args), a, b, e);
    }
    catch (Catch8& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<8, Args>::type>
               ::call(::boost::tuples::get<8>(args), a, b, e);
    }
  }
};

template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5, class Catch6,
                     class Catch7>
class lambda_functor_base<action<9, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>,
    detail::catch_block<Catch7>,detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), a, b, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), a, b, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), a, b, e);
    }
    catch (Catch6& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), a, b, e);
    }
    catch (Catch7& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<7, Args>::type>
               ::call(::boost::tuples::get<7>(args), a, b, e);
    }
    catch (...)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<8, Args>::type>
               ::call(::boost::tuples::get<8>(args), a, b, c);
    }
  }
};

// 9 catch types case
template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5, class Catch6,
                     class Catch7, class Catch8, class Catch9>
class lambda_functor_base<action<10, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>,
    detail::catch_block<Catch7>, detail::catch_block<Catch8>, detail::catch_block<Catch9> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), a, b, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), a, b, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), a, b, e);
    }
    catch (Catch6& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), a, b, e);
    }
    catch (Catch7& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<7, Args>::type>
               ::call(::boost::tuples::get<7>(args), a, b, e);
    }
    catch (Catch8& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<8, Args>::type>
               ::call(::boost::tuples::get<8>(args), a, b, e);
    }
    catch (Catch9& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<9, Args>::type>
               ::call(::boost::tuples::get<9>(args), a, b, e);
    }
  }
};

template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5, class Catch6,
                     class Catch7, class Catch8>
class lambda_functor_base<action<10, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>,
    detail::catch_block<Catch7>, detail::catch_block<Catch8>,detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, class A, class B, class C>
  RET call(A& a, B& b, C& c) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), a, b, c);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), a, b, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), a, b, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), a, b, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), a, b, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), a, b, e);
    }
    catch (Catch6& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), a, b, e);
    }
    catch (Catch7& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<7, Args>::type>
               ::call(::boost::tuples::get<7>(args), a, b, e);
    }
    catch (Catch8& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<8, Args>::type>
               ::call(::boost::tuples::get<8>(args), a, b, e);
    }
    catch (...)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<9, Args>::type>
               ::call(::boost::tuples::get<9>(args), a, b, c);
    }
  }
};




} // namespace lambda 
} // namespace boost


#endif
