/*
 * BaseUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include "neighbor/Neighbor.hpp"

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


BOOST_AUTO_TEST_SUITE( neighbor )

BOOST_AUTO_TEST_CASE( neighbor_methods )
{
  lmp::neighbor::Neighbor  neighbor(123);
  BOOST_CHECK_EQUAL(neighbor.getNodeId(), 123UL);
}

BOOST_AUTO_TEST_SUITE_END()

