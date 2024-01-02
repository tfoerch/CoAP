/*
 * BaseUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include <boost/asio/ip/address.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <map>
#include <set>
#include <deque>
#include <iostream>

#define BOOST_TEST_MAIN
#if !defined( WIN32 )
    #define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_MODULE LMP
// #include <BoostTestTargetConfig.h>
// #include <boost/test/included/unit_test.hpp>

typedef std::map<char, int>  ChIntMap;
typedef std::map<char, int>::value_type  ChIntPair;
typedef std::deque<char>  CharQueue;

struct OrderByMappedValueLessThan : public std::binary_function<char, char, bool>
{
  bool operator()(
	char  first,
	char  second) const
  {
	ChIntMap::const_iterator firstIter = m_chIntMap.find(first);
	ChIntMap::const_iterator secondIter = m_chIntMap.find(second);
	return
	  ( firstIter != m_chIntMap.end() &&
	    secondIter != m_chIntMap.end() &&
		firstIter->second < secondIter->second );
  }
  explicit OrderByMappedValueLessThan(
    const ChIntMap&  chIntMap)
  : m_chIntMap(chIntMap) {}
  const ChIntMap&  m_chIntMap;
};
struct ChIntEntry
{
  char  first;
  int   second;
};

struct AdaptChInt2Pair
{
  ChIntPair operator()(
    const ChIntEntry&  entry)
  { return ChIntPair(entry.first, entry.second); }
};

struct MyContainer
{
  typedef int                value_type;
  typedef value_type&        reference;
  typedef const value_type&  const_reference;
  void push_back(const_reference& value)
  {
	  m_queue.push_back(value);
  }
  std::deque<value_type>     m_queue;
};

struct MyIdentity
{
  int operator()(int val) const { return val; }
};

namespace os_iter_range
{
  template <typename P>
  std::ostream& operator<<(
    std::ostream&  os,
    const P&       p)
  {
    for (typename P::first_type iter = p.first;
         iter != p.second;
         ++iter)
    {
      if (iter != p.first)
      {
        std::operator<<(os,  ", ");
      }
      std::operator<<(os, *iter);
    }
    return os;
  }
}

namespace boost
{
  namespace test_tools
  {
    namespace tt_detail
    {
      template<>
      struct print_log_value< std::deque<char> >
      {
        void operator()(
          std::ostream& os,
          const std::deque<char>& queue)
        {
          using namespace os_iter_range;
          os_iter_range::operator <<(os, make_pair(queue.begin(), queue.end()));
        }
      };
//      template<>
//      struct print_log_value<char>
//      {
//        void operator()(
//          std::ostream& os,
//          char          ch)
//        {
//          std::operator<<(os, ch);
//        }
//      };
    }
  }
}
namespace boost
{
  namespace unit_test
  {
    namespace ut_detail
    {
      std::string normalize_test_case_name(const_string name)
      {
        return
          ( name[0] == '&' ?
            std::string(name.begin()+1, name.size()-1) :
            std::string(name.begin(), name.size() ));
      }
    }
  }
}

BOOST_AUTO_TEST_SUITE( util )

BOOST_AUTO_TEST_CASE( test_bind )
{
  ChIntPair p1('a', 23);
  ChIntPair p2('c', 15);
  BOOST_CHECK_EQUAL(bind(&ChIntPair::first, _1)(p1), 'a');
  BOOST_CHECK_EQUAL(bind(&ChIntPair::second, _1)(p1), 23);
  BOOST_CHECK( bind(std::less<char>(),
		            bind(&ChIntPair::first, _1),
				    bind(&ChIntPair::first, _2))(p1, p2));
  BOOST_CHECK(!bind(std::less<char>(),
		            bind(&ChIntPair::first, _1),
				    bind(&ChIntPair::first, _2))(p2, p1));
  BOOST_CHECK(!bind(std::less<int>(),
		            bind(&ChIntPair::second, _1),
				    bind(&ChIntPair::second, _2))(p1, p2));
  BOOST_CHECK( bind(std::less<int>(),
		            bind(&ChIntPair::second, _1),
				    bind(&ChIntPair::second, _2))(p2, p1));

  ChIntMap  myChIntMap;
  {
	const ChIntEntry chIntInput[] = { { 'c', 57 }, { 'b', 23 }, { 'k', 41 } };
    const size_t chIntInptNumElem = sizeof(chIntInput) / sizeof(ChIntEntry);
    std::transform(chIntInput,
    		       chIntInput + chIntInptNumElem,
				   std::inserter(myChIntMap, myChIntMap.begin()),
				   AdaptChInt2Pair());
  }
  BOOST_CHECK_EQUAL(myChIntMap.size(), 3);
  ChIntMap::const_iterator minIter =
    std::min_element(myChIntMap.begin(),
		             myChIntMap.end(),
					 bind(OrderByMappedValueLessThan(myChIntMap),
						  bind(&ChIntPair::first, _1),
						  bind(&ChIntPair::first, _2)));
  BOOST_CHECK(minIter != myChIntMap.end());
  if (minIter != myChIntMap.end())
  {
	BOOST_CHECK_EQUAL(minIter->first, 'b');
	BOOST_CHECK_EQUAL(minIter->second, 23);
  }
  const char expectedOrderInput[] = { 'b', 'k', 'c' };
  std::deque<char>  expectedOrder(expectedOrderInput, expectedOrderInput + sizeof(expectedOrderInput)/sizeof(char));
  OrderByMappedValueLessThan  orderCompFtor(myChIntMap);
  {
    std::deque<char>  orderByMappedValue;
    std::transform(myChIntMap.begin(),
                   myChIntMap.end(),
				   std::inserter(orderByMappedValue, orderByMappedValue.begin()),
				   bind(&ChIntPair::first, _1));
//    BOOST_CHECK_EQUAL(orderByMappedValue, expectedOrder);
    std::sort(orderByMappedValue.begin(), orderByMappedValue.end(), orderCompFtor);
    BOOST_CHECK_EQUAL(orderByMappedValue, expectedOrder);
  }
  {
	std::set<char, OrderByMappedValueLessThan>  orderedByMappedValue(orderCompFtor);
    std::transform(myChIntMap.begin(),
                   myChIntMap.end(),
				   std::inserter(orderedByMappedValue, orderedByMappedValue.begin()),
				   bind(&ChIntPair::first, _1));
	std::deque<char>  queue2CheckOrdering(orderedByMappedValue.begin(), orderedByMappedValue.end());
    BOOST_CHECK_EQUAL(queue2CheckOrdering, expectedOrder);
  }
}

BOOST_AUTO_TEST_CASE( test_back_inserter )
{
  MyContainer  mycontainer;
  const int input[] = { 4, 1, -3, 0, 7 };
  std::transform(input,
		         input + sizeof(input)/sizeof(int),
				 std::back_inserter(mycontainer),
				 MyIdentity());
}

BOOST_AUTO_TEST_SUITE_END()

