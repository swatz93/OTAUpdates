/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_ITERATOR_HPP
#define BOOST_INTRUSIVE_DETAIL_ITERATOR_HPP

#if defined(_MSC_VER)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/iiterator.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<class It>
class reverse_iterator
{
   public:
   typedef typename boost::intrusive::iterator_traits<It>::pointer             pointer;
   typedef typename boost::intrusive::iterator_traits<It>::reference           reference;
   typedef typename boost::intrusive::iterator_traits<It>::difference_type     difference_type;
   typedef typename boost::intrusive::iterator_traits<It>::iterator_category   iterator_category;
   typedef typename boost::intrusive::iterator_traits<It>::value_type          value_type;


   typedef It iterator_type;

   reverse_iterator()
      : m_current()  //Value initialization to achieve "null iterators" (N3644)
      {}

   explicit reverse_iterator(It r)
      : m_current(r)
   {}

   template<class OtherIt>
   reverse_iterator(const reverse_iterator<OtherIt>& r)
      : m_current(r.base())
   {}

   It base() const
   {  return m_current;  }

   reference operator*() const
   {  It temp(m_current);   --temp; return *temp; }

   pointer operator->() const
   {  It temp(m_current);   --temp; return temp.operator->(); }

   reference operator[](difference_type off) const
   {  return this->m_current[-off];  }

   reverse_iterator& operator++()
   {  --m_current;   return *this;   }

   reverse_iterator operator++(int)
   {
      reverse_iterator temp = *this;
      --m_current;
      return temp;
   }

   reverse_iterator& operator--()
   {
      ++m_current;
      return *this;
   }

   reverse_iterator operator--(int)
   {
      reverse_iterator temp(*this);
      ++m_current;
      return temp;
   }

   friend bool operator==(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current == r.m_current;  }

   friend bool operator!=(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current != r.m_current;  }

   friend bool operator<(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current > r.m_current;  }

   friend bool operator<=(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current >= r.m_current;  }

   friend bool operator>(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current < r.m_current;  }

   friend bool operator>=(const reverse_iterator& l, const reverse_iterator& r)
   {  return l.m_current <= r.m_current;  }

   reverse_iterator& operator+=(difference_type off)
   {  m_current -= off; return *this;  }

   friend reverse_iterator operator+(const reverse_iterator & l, difference_type off)
   {
      reverse_iterator tmp(l.m_current);
      tmp.m_current -= off;
      return tmp;
   }

   reverse_iterator& operator-=(difference_type off)
   {  m_current += off; return *this;  }

   friend reverse_iterator operator-(const reverse_iterator & l, difference_type off)
   {
      reverse_iterator tmp(l.m_current);
      tmp.m_current += off;
      return tmp;
   }

   friend difference_type operator-(const reverse_iterator& l, const reverse_iterator& r)
   {  return r.m_current - l.m_current;  }

   private:
   It m_current;   // the wrapped iterator
};

} //namespace detail
} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_DETAIL_ITERATOR_HPP
