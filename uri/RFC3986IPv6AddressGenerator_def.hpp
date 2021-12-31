#ifndef COAP_RFC3986IPv6Address_GENERATOR_DEF_HPP_
#define COAP_RFC3986IPv6Address_GENERATOR_DEF_HPP_
/*
 * RFC3986IPv6AddressGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "RFC3986IPv6AddressGenerator.hpp"
//#if defined(BOOST_ASIO_HAS_STD_ARRAY)
#include <boost/fusion/adapted/std_array.hpp>
//#else // defined(BOOST_ASIO_HAS_STD_ARRAY)
//#include <boost/fusion/adapted/boost_array.hpp>
//#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)
#include <boost/icl/closed_interval.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

namespace boost { namespace spirit { namespace traits {
    template <typename T, size_t N>
        struct is_container<std::array<T, N>, void> : mpl::false_ { };
} } }


namespace rfc3986
{
  namespace generator
  {
    namespace fusion = boost::fusion;
    namespace phoenix = boost::phoenix;

    struct isInLongestZeroInterval
    {
      template<typename> struct result { typedef bool /*boost::optional<icl::discrete_interval<size_t> >*/ type; };
      bool /*boost::optional<icl::discrete_interval<size_t> >*/ operator()(
        const std::vector<std::uint16_t>&  value,
        size_t                               index) const
      {
        std::optional<icl::discrete_interval<size_t> > result;
        std::optional<icl::discrete_interval<size_t> > cur_interval;
        for (size_t index = 0; index < value.size(); ++index)
        {
          if (value[index] == 0)
          {
            if (!cur_interval)
            {
              cur_interval = icl::construct<icl::discrete_interval<size_t> >(index, index, icl::interval_bounds::closed());
            }
            else if (cur_interval->upper() == (index - 1))
            {
              cur_interval = icl::construct<icl::discrete_interval<size_t> >(cur_interval->lower(), index, icl::interval_bounds::closed());
            }
          }
          else if (cur_interval)
          {
            if (!result ||
                ((cur_interval->upper() - cur_interval->lower()) >= (result->upper() - result->lower())))
            {
              result = cur_interval;
            }
            cur_interval.reset();
          }
        }
        if (cur_interval)
        {
          if (!result ||
              ((cur_interval->upper() - cur_interval->lower()) >= (result->upper() - result->lower())))
          {
            result = cur_interval;
          }
          cur_interval.reset();
        }
        //std::cout << result << ", " << index << std::endl;
        return
          ( result &&
            icl::contains(*result, index) );
      }
    };

    template <typename OutputIterator>
    ipv6_address_grammar<OutputIterator>::ipv6_address_grammar()
    : ipv6_address_grammar::base_type(ipv6_address_rule, "ipv6_address")
    {
      using karma::eps;
      using karma::_1;
      using karma::_val;
      using karma::omit;
      using phoenix::at_c;
      using phoenix::push_back;

      boost::phoenix::function<isInLongestZeroInterval>  phx_is_in_longest_zero_interval;

      ipv6_address_rule =
//             eps [ karma::_a = phoenix::begin(_val) ]
//          << karma::repeat(7) [
//                karma::uint_generator<std::uint16_t, 16>() [ _1 = (256 * *karma::_a++) + *karma::_a++ ]
//             << ':' ]
//         << karma::uint_generator<std::uint16_t, 16>() [ _1 = (256 * *karma::_a++) + *karma::_a++ ]
//         << ':'
//         << karma::uint_generator<std::uint16_t, 16>() [ _1 = (256 * *karma::_a++) + *karma::_a++ ]
//         << ':'
//         << karma::uint_generator<std::uint16_t, 16>() [ _1 = (256 * *karma::_a++) + *karma::_a++ ]
//         << ':'
//         << karma::uint_generator<std::uint16_t, 16>() [ _1 = (256 * *karma::_a++) + *karma::_a++ ]
//         << ':'
//         << karma::uint_generator<std::uint16_t, 16>() [ _1 = (256 * *karma::_a++) + *karma::_a++ ]
//         << ':'
//         << karma::uint_generator<std::uint16_t, 16>() [ _1 = (256 * *karma::_a++) + *karma::_a++ ]
//         << ':'
//         << karma::uint_generator<std::uint16_t, 16>() [ _1 = (256 * *karma::_a++) + *karma::_a++ ]
//         << ':'
//         << karma::uint_generator<std::uint16_t, 16>() [ _1 = (256 * *karma::_a++) + *karma::_a++ ]
         shortIntSeq_rule [ karma::_a = phoenix::begin(_val),
                            push_back(_1, (256 * *karma::_a++) + *karma::_a++), push_back(_1, (256 * *karma::_a++) + *karma::_a++),
                            push_back(_1, (256 * *karma::_a++) + *karma::_a++), push_back(_1, (256 * *karma::_a++) + *karma::_a++),
                            push_back(_1, (256 * *karma::_a++) + *karma::_a++), push_back(_1, (256 * *karma::_a++) + *karma::_a++),
                            push_back(_1, (256 * *karma::_a++) + *karma::_a++), push_back(_1, (256 * *karma::_a++) + *karma::_a++) ]
         ;

      shortIntSeq_rule %=
//         eps [ karma::_a = 0 ]
//         << (    eps(!phx_is_in_longest_zero_interval(_val, karma::_a))
//              << omit[karma::uint_generator<std::uint16_t, 16>()]
//              << "::"
//              << +(    ':'
//                    << karma::uint_generator<std::uint16_t, 16>() ) ) |
//            ( karma::uint_generator<std::uint16_t, 16>()
//              << +(    ':'
//                    << karma::uint_generator<std::uint16_t, 16>() ) )
         karma::uint_generator<std::uint16_t, 16>()
         << karma::repeat(7) [
               ':'
            << karma::uint_generator<std::uint16_t, 16>() ]
         ;

      ipv6_address_rule.name("ipv6_address");
    }
  } // namespace generator
} // namespace rfc3986

#endif /* COAP_RFC3986IPv6Address_GENERATOR_DEF_HPP_ */
