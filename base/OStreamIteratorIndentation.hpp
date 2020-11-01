#ifndef COAP_BASE_OSTREAM_ITER_INDENT_HPP_
#define COAP_BASE_OSTREAM_ITER_INDENT_HPP_
/*
 * OStreamIteratorIndentation.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <iterator>
#include <iostream>
#include <string>

namespace coap
{
  namespace base
  {
    template<typename T, typename _CharT = char,
              typename _Traits = std::char_traits<_CharT> >
    class OStreamIteratorIndentation : public std::iterator<std::output_iterator_tag, void, void, void, void>
    {
    public:
      using difference_type = ptrdiff_t;
      typedef _CharT                         char_type;
      typedef _Traits                        traits_type;
      typedef std::basic_ostream<_CharT, _Traits> ostream_type;

    private:
      ostream_type*  m_stream;
      std::string    m_delimiter;
      bool           m_firstWritten;

    public:
      OStreamIteratorIndentation(
        ostream_type&       stream,
        const std::string&  delimiter)
      : m_stream(std::addressof(stream)),
        m_delimiter(delimiter),
        m_firstWritten(false)
      {}

      OStreamIteratorIndentation() = delete;
      OStreamIteratorIndentation(const OStreamIteratorIndentation& other) = default;
      OStreamIteratorIndentation& operator=(const OStreamIteratorIndentation& other) = default;
      ~OStreamIteratorIndentation() = default;

      OStreamIteratorIndentation& operator=(const T& value)
      {
        if (m_stream)
        {
          if (m_firstWritten)
          {
            *m_stream << m_delimiter << value;
          }
          else
          {
            *m_stream << value;
            m_firstWritten = true;
          }
        }
        return *this;
      }

      OStreamIteratorIndentation& operator*()
      { return *this; }

      OStreamIteratorIndentation& operator++()
      { return *this; }

      OStreamIteratorIndentation& operator++(int)
      { return *this; }

      void reset()
      {
        m_firstWritten = false;
      }
    };
  } // namespace base
} // namespace coap

#endif /* COAP_BASE_OSTREAM_ITER_INDENT_HPP_ */
