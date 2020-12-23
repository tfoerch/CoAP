/*
 * BaseUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include <boost/hana/functional/fix.hpp>
#include <boost/hana/functional/overload.hpp>

#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <variant>
#include <memory>

#define BOOST_TEST_MAIN
#if !defined( WIN32 )
    #define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_MODULE COAP

namespace hana = boost::hana;

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

// Y_Combinator https://stackoverflow.com/questions/2067988/recursive-lambda-functions-in-c11
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


template<typename InputIterator,
         typename UnaryOperation,
         typename CharT = char,
         typename Traits = std::char_traits<CharT>>
std::basic_ostream<CharT, Traits>&
printOutCB(InputIterator                                 first,
           InputIterator                                 last,
           std::basic_ostream<CharT, Traits>&            oStream,
           const CharT*                                  delim,
           UnaryOperation                                unary_op)
{
  bool firstWritten = false;
  for (; first != last; ++first)
  {
    if (firstWritten)
    {
      if (delim)
      {
        oStream << delim;
      }
    }
    else
    {
      firstWritten = true;
    }
    unary_op(oStream, *first);
  }
  return oStream;
}


template<typename InputIterator,
         typename CharT = char,
         typename Traits = std::char_traits<CharT>>
std::basic_ostream<CharT, Traits>&
printOut(InputIterator                                 first,
         InputIterator                                 last,
         std::basic_ostream<CharT, Traits>&            oStream,
         const CharT*                                  delim)
{
  return
    printOutCB(first, last,
               oStream,
               delim,
               [](
                 std::basic_ostream<CharT, Traits>&  os,
                 const auto&                         entry)
               { os << entry; });
}

namespace recursive_variant_unique_ptr
{
  template <typename T>
  class RecursiveWrapper
  {
  public:
    RecursiveWrapper()
    : m_data(std::make_unique<T>())
    {}
    explicit RecursiveWrapper(
      const T&  entity)
    : m_data(std::make_unique<T>(entity))
    {}
    explicit RecursiveWrapper(
      T&&  entity)
    : m_data(std::make_unique<T>(entity))
    {}
    RecursiveWrapper(
      const RecursiveWrapper&  other)
    : m_data(new T(other.get()))
    {}
    RecursiveWrapper(
      RecursiveWrapper&&  other) = default;
    RecursiveWrapper& operator=(
      const T&  entity)
    {
      m_data = std::make_unique<T>(entity);
      return *this;
    }
    RecursiveWrapper& operator=(
      T&&  entity)
    {
      m_data = std::move(entity);
      return *this;
    }
    RecursiveWrapper& operator=(
      const RecursiveWrapper&  other)
    {
      m_data = std::make_unique<T>(other.get());
      return *this;
    }
    RecursiveWrapper& operator=(
      RecursiveWrapper&&  other) = default;

    auto get() const noexcept -> std::add_const_t<std::add_lvalue_reference_t<T>>
    {
      return *m_data.get();
    }
    auto get() noexcept -> std::add_lvalue_reference_t<T>
    {
      return *m_data.get();
    }
    void swap(
      RecursiveWrapper&  other)
    {
      m_data.swap(other.m_data);
    }

    template<typename F, typename... Args>
    decltype(auto) invoke(F func, Args&&... args) {
      return (get().*func)(std::forward<Args>(args)...);
    }

  private:
    std::unique_ptr<T>  m_data;
  };

  template <typename T>
  std::ostream& operator<<(
    std::ostream&               os,
    const RecursiveWrapper<T>&  value)
  {
    os << value.get();
    return os;
  }

}

// grammar https://en.wikipedia.org/wiki/LR_parser
//rule0: Expression → Sums eof
//rule1: Sums → Sums + Products
//rule2: Sums → Products
//rule3: Products → Products * Value
//rule4: Products → Value
//rule5: Value → int
//rule6: Value → id

// states
struct StartState {};
struct SumsParsedState {};
struct SumsAndPlusParsedState {};
struct ProductsParsedPotentialShiftRule1State {};
struct ProductsParsedPotentialShiftRule2State {};
struct ProductsAndMultiplicationParsedState {};
struct ValueParsedShiftRule3State {};
struct ValueParsedShiftRule4State {};
struct IntParsedShiftRule5State {};
struct IdParsedShiftRule6State {};

using StateVariantType =
  std::variant<StartState,
               SumsParsedState,
               SumsAndPlusParsedState,
               ProductsParsedPotentialShiftRule1State,
               ProductsParsedPotentialShiftRule2State,
               ProductsAndMultiplicationParsedState,
               ValueParsedShiftRule3State,
               ValueParsedShiftRule4State,
               IntParsedShiftRule5State,
               IdParsedShiftRule6State>;


// terminal symbols
using IdType = std::string;
using IntType = unsigned int;
struct PlusSign {};
struct MultiplicationSign {};
struct EOFSymbol {};

using TerminalVariantType =
  std::variant<IdType,
               IntType,
               PlusSign,
               MultiplicationSign,
               EOFSymbol>;

std::ostream& operator<<(
  std::ostream&               os,
  const TerminalVariantType&  symbol)
{
  auto printout = [&os](
    const TerminalVariantType&  symbol) -> void
  {
    return
      std::visit(
        hana::overload
         (
           [&os](const IdType& id){ os << id; },
           [&os](const IntType& value){ os << value; },
           [&os](const PlusSign& plus){ os << '+'; },
           [&os](const MultiplicationSign& mult){ os << '*'; },
           [&os](const EOFSymbol& eof){ os << "eof"; }
         ),
         symbol);
  };
  printout(symbol);
  return os;
}

using SymbolTable =
  std::map<IdType, IntType>;


// non terminal symbols

namespace recursive_variant_forward_declaration
{
  namespace impl
  {
    struct symbol_wrapper;
    using symbol_arr = std::vector<symbol_wrapper>;
  }

  using impl::symbol_arr;

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

  auto evaluate = [](
    const SymbolVariantType&  symbol,
    const SymbolTable&        symbolTable) -> IntType
  {
    auto do_evaluate = hana::fix([&symbolTable](
      auto                      self,
      const SymbolVariantType&  symbol) -> IntType
    {
      return
        std::visit(
          hana::overload
           (
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
             }
           ),
           symbol);
    });
    return
      do_evaluate(symbol);
  };

  std::ostream& operator<<(
    std::ostream&             os,
    const SymbolVariantType&  symbol)
  {
    auto printout = hana::fix([&os](
      auto                      self,
      const SymbolVariantType&  symbol) -> void
    {
      auto printSeq = [&self](
        std::ostream&      os,
        const symbol_arr&  symbols) -> void
      {
        os << "{ ";
        printOutCB(symbols.begin(), symbols.end(),
                   os,
                   ", ",
                   [&self](
                     std::ostream&  os,
                     const auto&    symbolWrapper)
                     { impl::visit_recursively(self, symbolWrapper); });
        os << " }";
      };
      return
        std::visit(
          hana::overload
           (
             [&os](const IdType& id){ os << id; },
             [&os](const IntType& value){ os << value; },
             [&os](const PlusSign& plus){ os << '+'; },
             [&os](const MultiplicationSign& mult){ os << '*'; },
             [&os](const EOFSymbol& eof){ os << "eof"; },
             [&printSeq, &os](const Expression&  expr){ printSeq(os, expr.m_symbols); },
             [&printSeq, &os](const Sums&  sums){ printSeq(os, sums.m_symbols); },
             [&printSeq, &os](const Products&  products){ printSeq(os, products.m_symbols); },
             [&printSeq, &os](const Value&  value){ printSeq(os, value.m_symbols); }
           ),
           symbol);
    });
    printout(symbol);
    return os;
  }
}


namespace recursive_variant_unique_ptr
{
  class Value
  {
  public:
    using ValueType =
      std::variant<IdType, IntType>;
    explicit Value(
      const IdType&   id) // r6
    : m_data(id)
    {}
    explicit Value(
      const IntType&  value) // r5
    : m_data(value)
    {}
    auto evaluate(
      const SymbolTable&  symbolTable) const -> IntType
    {
      return
        std::visit(
          hana::overload(
             [&symbolTable](const IdType& id)
             {
               IntType result = 0;
               SymbolTable::const_iterator iter = symbolTable.find(id);
               if (iter != symbolTable.end())
               {
                 result = iter->second;
               }
               return result;
             },
             [](const IntType& value)
             { return value; }
           ), m_data);

    }
    std::ostream& printout(
      std::ostream&   os) const
    {
      return
        std::visit(
          hana::overload
           (
             [&os](const IdType& id) -> std::ostream&
             { os << "{ " << id << " }"; return os; },
             [&os](const IntType& value) -> std::ostream&
             { os << "{ " << value << " }"; return os; }
           ), m_data);
    }
  private:
    ValueType  m_data;
  };

  inline std::ostream& operator<<(
    std::ostream&  os,
    const Value&   value)
  { return value.printout(os); }

  class Products
  {
  public:
    using ProductsWrapper =
      RecursiveWrapper<Products>;
    using Rule3Tuple =
      std::tuple<ProductsWrapper, MultiplicationSign, Value>;
    using ProductsType =
      std::variant<Value, Rule3Tuple>;
    explicit Products(
      const Value&               value) // r4
    : m_data(value)
    {}
    Products(
      const Products&            products,
      const MultiplicationSign&  mult,
      const Value&               value) // r3
    : m_data(Rule3Tuple(ProductsWrapper(products), mult, value))
    {}
    auto evaluate(
      const SymbolTable&  symbolTable) const -> IntType
    {
      return
        std::visit(
          hana::overload(
             [&symbolTable](const Value& value)
             { return value.evaluate(symbolTable); },
             [&symbolTable](const Rule3Tuple& tuple)
             {
               return
                 ( std::get<0>(tuple).get().evaluate(symbolTable) *
                   std::get<2>(tuple).evaluate(symbolTable) );
             }
           ), m_data);

    }
    std::ostream& printout(
      std::ostream&   os) const
    {
      return
        std::visit(
          hana::overload
           (
             [&os](const Value& value) -> std::ostream&
             { os << "{ " << value << " }"; return os; },
             [&os](const Rule3Tuple& tuple) -> std::ostream&
             {
               os << "{ " << std::get<0>(tuple) << ", "
                  << std::get<1>(tuple) << ", "
                  << std::get<2>(tuple) << " }";
               return os;
             }
           ), m_data);
    }
  private:
    ProductsType  m_data;
  };

  inline std::ostream& operator<<(
    std::ostream&    os,
    const Products&  products)
  { return products.printout(os); }


  class Sums
  {
  public:
    using SumsWrapper =
      RecursiveWrapper<Sums>;
    using Rule1Tuple =
      std::tuple<SumsWrapper, PlusSign, Products>;
    using SumsType =
      std::variant<Products, Rule1Tuple>;
    explicit Sums(
      const Products&  products) // r2
    : m_data(products)
    {}
    Sums(
      const Sums&      sums,
      const PlusSign&  plus,
      const Products&  products) // r1
    : m_data(Rule1Tuple(SumsWrapper(sums), plus, products))
    {}
    auto evaluate(
      const SymbolTable&  symbolTable) const -> IntType
    {
      return
        std::visit(
          hana::overload(
             [&symbolTable](const Products& products)
             { return products.evaluate(symbolTable); },
             [&symbolTable](const Rule1Tuple& tuple)
             {
               return
                 ( std::get<0>(tuple).get().evaluate(symbolTable) +
                   std::get<2>(tuple).evaluate(symbolTable) );
             }
           ), m_data);

    }
    std::ostream& printout(
      std::ostream&   os) const
    {
      return
        std::visit(
          hana::overload
           (
             [&os](const Products& products) -> std::ostream&
             { os << "{ " << products << " }"; return os; },
             [&os](const Rule1Tuple& tuple) -> std::ostream&
             {
               os << "{ " << std::get<0>(tuple) << ", "
                  << std::get<1>(tuple) << ", "
                  << std::get<2>(tuple) << " }";
               return os;
             }
           ), m_data);
    }
  private:
    SumsType  m_data;
  };

  inline std::ostream& operator<<(
    std::ostream&  os,
    const Sums&    sums)
  { return sums.printout(os); }

  class Expression
  {
  public:
    using ExpressionType =
      std::pair<Sums, EOFSymbol>;
    Expression(
      const Sums&       sums,
      const EOFSymbol&  eof)
    : m_data(sums, eof)
    {}
    auto evaluate(
      const SymbolTable&  symbolTable) const -> IntType
    {
      return
        m_data.first.evaluate(symbolTable);
    }
    std::ostream& printout(
      std::ostream&   os) const
    {
      os << "{ " << m_data.first << ", " << m_data.second << " }";
      return os;
    }
  private:
    ExpressionType  m_data;
  };

  inline std::ostream& operator<<(
    std::ostream&      os,
    const Expression&  expression)
  { return expression.printout(os); }

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

  auto evaluate = [](
    const SymbolVariantType&  symbol,
    const SymbolTable&        symbolTable) -> IntType
  {
    return
      std::visit(
        hana::overload(
          [&symbolTable](const Expression& expression)
          { return expression.evaluate(symbolTable); },
          [&symbolTable](const Sums& sums)
          { return sums.evaluate(symbolTable); },
          [&symbolTable](const Products& products)
          { return products.evaluate(symbolTable); },
          [&symbolTable](const Value& value)
          { return value.evaluate(symbolTable); },
          [&symbolTable](const IdType& id)
          {
            IntType result = 0;
            SymbolTable::const_iterator iter = symbolTable.find(id);
            if (iter != symbolTable.end())
            {
              result = iter->second;
            }
            return result;
          },
          [](const IntType& value)
          { return value; },
          [](const PlusSign& plus) -> IntType
          { return 0; },
          [](const MultiplicationSign& mult) -> IntType
          { return 0; },
          [](const EOFSymbol& eof) -> IntType
          { return 0; }
        ), symbol);
  };

  std::ostream& operator<<(
    std::ostream&             os,
    const SymbolVariantType&  symbol)
  {
    return
      std::visit(
        hana::overload(
          [&os](const Expression& expression) -> std::ostream&
          { os << expression; return os; },
          [&os](const Sums& sums) -> std::ostream&
          { os << sums; return os; },
          [&os](const Products& products) -> std::ostream&
          { os << products; return os; },
          [&os](const Value& value) -> std::ostream&
          { os << value; return os; },
          [&os](const IdType& id) -> std::ostream&
          { os << id; return os; },
          [&os](const IntType& value) -> std::ostream&
          { os << value; return os; },
          [&os](const PlusSign& plus) -> std::ostream&
          { os << '+'; return os; },
          [&os](const MultiplicationSign& mult) -> std::ostream&
          { os << '*'; return os; },
          [&os](const EOFSymbol& eof) -> std::ostream&
          { os << "eof"; return os; }
        ), symbol);
  }
}


BOOST_AUTO_TEST_SUITE( util )

BOOST_AUTO_TEST_CASE( print_not_recursive_variant )
{
  using TerminalInitList =
    std::initializer_list<TerminalVariantType>;
  const TerminalInitList input =
    { IdType{"a"}, MultiplicationSign{}, IntType{2}, PlusSign{}, IntType{1}, EOFSymbol{} };// a*2 + 1
  std::ostringstream oss;
  oss << "{ ";
  printOut(input.begin(), input.end(), oss, ", ");
  oss << " }";
  BOOST_CHECK_EQUAL(oss.str(), "{ a, *, 2, +, 1, eof }");
}

BOOST_AUTO_TEST_CASE( test_recursive_variant_unique_ptr )
{
  using namespace recursive_variant_unique_ptr;
  {
    using ProductsWrapper =
      RecursiveWrapper<Products>;
    ProductsWrapper  productsWrapper{Products{Value{IntType{87}}}};
    SymbolTable        symbolTable;
    BOOST_CHECK_EQUAL(productsWrapper.invoke(&Products::evaluate, symbolTable), 87);
    BOOST_CHECK_EQUAL(productsWrapper.get().evaluate(symbolTable), 87);
  }
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

BOOST_AUTO_TEST_CASE( test_recursive_variant_forward_declaration )
{
  using namespace recursive_variant_forward_declaration;
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

