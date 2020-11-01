/*
 * BaseUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <variant>
#include <iterator>

#define BOOST_TEST_MAIN
#if !defined( WIN32 )
    #define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_MODULE COAP

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template <class F>
struct Y_Combinator
{
  F f; // the lambda will be stored here

  // a forwarding operator():
  template <typename... Args>
  decltype(auto)  operator()(Args&&... args) const
  {
    // we pass ourselves to f, then the arguments.
    // [edit: Barry] pass in std::ref(*this) instead of *this
    return f(std::ref(*this), std::forward<Args>(args)...);
  }
  template <typename... Args>
  decltype(auto) operator()(Args&&... args)
  {
    // we pass ourselves to f, then the arguments.
    // [edit: Barry] pass in std::ref(*this) instead of *this
    return f(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class F> Y_Combinator(F) -> Y_Combinator<F>;


namespace impl
{
  struct symbol_wrapper;
  using symbol_arr = std::vector<symbol_wrapper>;
}

using impl::symbol_arr;

//r0: Expression → Sums eof
//r1: Sums → Sums + Products
//r2: Sums → Products
//r3: Products → Products * Value
//r4: Products → Value
//r5: Value → int
//r6: Value → id

// terminal symbols
using IdType = std::string;
using IntType = unsigned int;
struct PlusSign {};
struct MultiplicationSign {};
struct EOFSymbol {};

// non terminal symbols
struct Value
{
  explicit Value(
    const IdType&   id); // r6
  explicit Value(
    const IntType&  value); // r5
  symbol_arr  m_symbols;
};

struct Products
{
  explicit Products(
    const Value&               value); // r4
  Products(
    const Products&            products,
    const MultiplicationSign&  mult,
    const Value&               value); // r3
  symbol_arr  m_symbols;
};

struct Sums
{
  explicit Sums(
    const Products&  products); // r2
  Sums(
    const Sums&      sums,
    const PlusSign&  plus,
    const Products&  products); // r1
  symbol_arr  m_symbols;
};

struct Expression
{
  Expression(
    const Sums&       sums,
    const EOFSymbol&  eof);
  symbol_arr  m_symbols;
};

using SymbolVariantType =
  std::variant<Expression,
               Sums,
               Products,
               Value,
               IdType,
               IntType,
               PlusSign,
               MultiplicationSign,
               EOFSymbol>;

using TerminalVariantType =
  std::variant<IdType,
               IntType,
               PlusSign,
               MultiplicationSign,
               EOFSymbol>;

using SymbolTable =
  std::map<IdType, IntType>;

namespace impl
{
  struct symbol_wrapper
  {
    SymbolVariantType  m_data;

    template <typename... Ts>
    symbol_wrapper(Ts&&... xs)
      : m_data{std::forward<Ts>(xs)...}
    {}
  };
  template <typename TVisitor, typename TVariant>
  decltype(auto) visit_recursively(
    TVisitor&&  visitor,
    TVariant&&  variant)
  {
    return
      std::visit(
        std::forward<TVisitor>(visitor),
        std::forward<TVariant>(variant).m_data);
  }
}

using impl::symbol_wrapper;

Value::Value(
  const IdType&   id)
: m_symbols()
{
  m_symbols.push_back(symbol_wrapper(SymbolVariantType(id)));
}

Value::Value(
  const IntType&  value)
: m_symbols()
{
  m_symbols.push_back(symbol_wrapper(SymbolVariantType(value)));
}

Products::Products(
  const Value&               value) // r4
: m_symbols()
{
  m_symbols.push_back(symbol_wrapper(SymbolVariantType(value)));
}

Products::Products(
  const Products&            products,
  const MultiplicationSign&  mult,
  const Value&               value) // r3
: m_symbols()
{
  m_symbols.push_back(symbol_wrapper(SymbolVariantType(products)));
  m_symbols.push_back(symbol_wrapper(SymbolVariantType(mult)));
  m_symbols.push_back(symbol_wrapper(SymbolVariantType(value)));
}

Sums::Sums(
  const Products&  products) // r2
: m_symbols()
{
  m_symbols.push_back(symbol_wrapper(SymbolVariantType(products)));
}

Sums::Sums(
  const Sums&      sums,
  const PlusSign&  plus,
  const Products&  products) // r1
: m_symbols()
{
  m_symbols.push_back(symbol_wrapper(SymbolVariantType(sums)));
  m_symbols.push_back(symbol_wrapper(SymbolVariantType(plus)));
  m_symbols.push_back(symbol_wrapper(SymbolVariantType(products)));
}

Expression::Expression(
  const Sums&       sums,
  const EOFSymbol&  eof)
: m_symbols()
{
  m_symbols.push_back(symbol_wrapper(SymbolVariantType(sums)));
  m_symbols.push_back(symbol_wrapper(SymbolVariantType(eof)));
}

using SymbolTable =
  std::map<IdType, IntType>;


auto evaluate = [](
  const SymbolVariantType&  symbol,
  const SymbolTable&        symbolTable) -> IntType
{
  auto do_evaluate = Y_Combinator{[&symbolTable](
    auto                      self,
    const SymbolVariantType&  symbol) -> IntType
  {
    return
      std::visit(
        overloaded
         {
           [&symbolTable](const IdType& id) -> IntType
           {
             IntType result = 0;
             SymbolTable::const_iterator iter = symbolTable.find(id);
             if (iter != symbolTable.end())
             {
               result = iter->second;
             }
             return result;
           },
           [](const IntType& value) -> IntType
           { return value; },
           [](const PlusSign& plus) -> IntType
           { return 0; },
           [](const MultiplicationSign& mult) -> IntType
           { return 0; },
           [](const EOFSymbol& eof) -> IntType
           { return 0; },
           [&self](const Expression&  expr) -> IntType
           {
             return
               ( expr.m_symbols.empty() ?
                 0 :
                 impl::visit_recursively(self, expr.m_symbols[0]) );
           },
           [&self](const Sums&  sums) -> IntType
           {
             return
               ( sums.m_symbols.empty() ?
                 0 :
                 ( sums.m_symbols.size() == 3 ?
                   ( impl::visit_recursively(self, sums.m_symbols[0]) +
                     impl::visit_recursively(self, sums.m_symbols[2]) ) :
                   impl::visit_recursively(self, sums.m_symbols[0]) ) );
           },
           [&self](const Products&  products) -> IntType
           {
             return
               ( products.m_symbols.empty() ?
                 0 :
                 ( products.m_symbols.size() == 3 ?
                   ( impl::visit_recursively(self, products.m_symbols[0]) *
                     impl::visit_recursively(self, products.m_symbols[2]) ) :
                   impl::visit_recursively(self, products.m_symbols[0]) ) );
           },
           [&self](const Value&  value) -> IntType
           {
             return
               ( value.m_symbols.empty() ?
                 0 :
                 impl::visit_recursively(self, value.m_symbols[0]) );
           },
         },
         symbol);
  }};
  return
    do_evaluate(symbol);
};
auto printout = [](
  std::ostream&             os,
  const SymbolVariantType&  symbol) -> std::ostream&
{
  auto do_printout = Y_Combinator{[&os](
    auto                      self,
    const SymbolVariantType&  symbol) -> void
  {
    auto printSeq = [&self](
      std::ostream&      os,
      const symbol_arr&  symbols) -> void
    {
      os << "{ ";
      bool firstWritten = false;
      for(const auto& symbol : symbols)
      {
        if (firstWritten)
        {
          os << ", ";
        }
        else
        {
          firstWritten = true;
        }
        impl::visit_recursively(self, symbol);
      }
      os << " }";
    };
    return
      std::visit(
        overloaded
         {
           [&os](const IdType& id){ os << id; },
           [&os](const IntType& value){ os << value; },
           [&os](const PlusSign& plus){ os << '+'; },
           [&os](const MultiplicationSign& mult){ os << '*'; },
           [&os](const EOFSymbol& eof){ os << "eof"; },
           [&printSeq, &os](const Expression&  expr){ printSeq(os, expr.m_symbols); },
           [&printSeq, &os](const Sums&  sums){ printSeq(os, sums.m_symbols); },
           [&printSeq, &os](const Products&  products){ printSeq(os, products.m_symbols); },
           [&printSeq, &os](const Value&  value){ printSeq(os, value.m_symbols); },
         },
         symbol);
  }};
  do_printout(symbol);
  return os;
};

std::ostream& operator<<(
  std::ostream&             os,
  const SymbolVariantType&  symbol)
{
//  std::visit([&os](auto&& arg){os << arg;}, symbol);
  printout(os, symbol);
  return os;
}

BOOST_AUTO_TEST_SUITE( util )

BOOST_AUTO_TEST_CASE( print_recursive_variant )
{
  {
    SymbolVariantType svt = IdType{"a"};
    std::ostringstream oss;
    oss << svt;
    BOOST_CHECK_EQUAL(oss.str(), "a");
    SymbolTable        symbolTable;
    symbolTable[IdType{"a"}] = 27;
    BOOST_CHECK_EQUAL(evaluate(svt, symbolTable), 27);
  }
  {
    SymbolVariantType svt = IntType{143};
    std::ostringstream oss;
    oss << svt;
    BOOST_CHECK_EQUAL(oss.str(), "143");
    SymbolTable        symbolTable;
    BOOST_CHECK_EQUAL(evaluate(svt, symbolTable), 143);
  }
  {
    SymbolVariantType svt = PlusSign{};
    std::ostringstream oss;
    oss << svt;
    BOOST_CHECK_EQUAL(oss.str(), "+");
  }
  {
    SymbolVariantType svt = MultiplicationSign{};
    std::ostringstream oss;
    oss << svt;
    BOOST_CHECK_EQUAL(oss.str(), "*");
  }
  {
    SymbolVariantType svt = EOFSymbol{};
    std::ostringstream oss;
    oss << svt;
    BOOST_CHECK_EQUAL(oss.str(), "eof");
  }
  {
    SymbolVariantType svt = Value{IdType{"b"}};
    std::ostringstream oss;
    oss << svt;
    BOOST_CHECK_EQUAL(oss.str(), "{ b }");
    SymbolTable        symbolTable;
    symbolTable[IdType{"b"}] = 103;
    BOOST_CHECK_EQUAL(evaluate(svt, symbolTable), 103);
  }
  {
    SymbolVariantType svt = Value{IntType{87}};
    std::ostringstream oss;
    oss << svt;
    BOOST_CHECK_EQUAL(oss.str(), "{ 87 }");
  }
  {
    SymbolVariantType svt = Products{Value{IntType{45}}};
    std::ostringstream oss;
    oss << svt;
    BOOST_CHECK_EQUAL(oss.str(), "{ { 45 } }");
    SymbolTable        symbolTable;
    BOOST_CHECK_EQUAL(evaluate(svt, symbolTable), 45);
  }
  {
    SymbolVariantType svt =
        Products{Products{Value{IntType{52}}},
                 MultiplicationSign{},
                 Value{IntType{17}}};
    std::ostringstream oss;
    oss << svt;
    BOOST_CHECK_EQUAL(oss.str(), "{ { { 52 } }, *, { 17 } }");
    SymbolTable        symbolTable;
    BOOST_CHECK_EQUAL(evaluate(svt, symbolTable), 884);
  }
  {
    SymbolVariantType svt = Sums{Products{Value{IntType{45}}}};
    std::ostringstream oss;
    oss << svt;
    BOOST_CHECK_EQUAL(oss.str(), "{ { { 45 } } }");
    SymbolTable        symbolTable;
    BOOST_CHECK_EQUAL(evaluate(svt, symbolTable), 45);
  }
  {
    SymbolVariantType svt =
        Sums{Sums{Products{Products{Value{IntType{52}}},
                           MultiplicationSign{},
                           Value{IntType{17}}}},
             PlusSign{},
             Products{Products{Value{IntType{52}}},
                      MultiplicationSign{},
                      Value{IntType{17}}}};
    std::ostringstream oss;
    oss << svt;
    BOOST_CHECK_EQUAL(oss.str(), "{ { { { { 52 } }, *, { 17 } } }, +, { { { 52 } }, *, { 17 } } }");
    SymbolTable        symbolTable;
    BOOST_CHECK_EQUAL(evaluate(svt, symbolTable), 1768);
  }
  {
    SymbolVariantType svt =
        Expression{Sums{Products{Value{IntType{45}}}},
                   EOFSymbol{}};
    std::ostringstream oss;
    oss << svt;
    BOOST_CHECK_EQUAL(oss.str(), "{ { { { 45 } } }, eof }");
    SymbolTable        symbolTable;
    BOOST_CHECK_EQUAL(evaluate(svt, symbolTable), 45);
  }
}

BOOST_AUTO_TEST_SUITE_END()

