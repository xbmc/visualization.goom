/*
 *      Copyright (C) 2019 Team Kodi
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <algorithm>
#include <vector>

int const silence_threshold = 8;

template <typename T>
class circular_buffer
{
public:
  circular_buffer( unsigned p_size ) : readptr( 0 ), writeptr( 0 ), size( p_size ), used( 0 )
  {
    buffer.resize( p_size );
  }
  unsigned data_available() { return used; }
  unsigned free_space() { return size - used; }
  bool write( const T * src, unsigned count )
  {
    if ( count > free_space() ) return false;
    while( count )
    {
      unsigned delta = size - writeptr;
      if ( delta > count ) delta = count;
      std::copy( src, src + delta, buffer.begin() + writeptr );
      used += delta;
      writeptr = ( writeptr + delta ) % size;
      src += delta;
      count -= delta;
    }
    return true;
  }
  unsigned read( T * dst, unsigned count )
  {
    unsigned done = 0;
    for(;;)
    {
      unsigned delta = size - readptr;
      if ( delta > used ) delta = used;
      if ( delta > count ) delta = count;
      if ( !delta ) break;

      std::copy( buffer.begin() + readptr, buffer.begin() + readptr + delta, dst );
      dst += delta;
      done += delta;
      readptr = ( readptr + delta ) % size;
      count -= delta;
      used -= delta;
    }
    return done;
  }
  void reset()
  {
    readptr = writeptr = used = 0;
  }
  void resize(unsigned p_size)
  {
    size = p_size;
    buffer.resize( p_size );
    reset();
  }
  bool test_silence() const
  {
    T* begin = (T*) &buffer[0];
    T first = *begin;
    *begin = silence_threshold * 2;
    T* p = begin + size;
    while ( (unsigned) ( *--p + silence_threshold ) <= (unsigned) silence_threshold * 2 ) { }
    *begin = first;
    return p == begin && ( (unsigned) ( first + silence_threshold ) <= (unsigned) silence_threshold * 2 );
  }

private:
  std::vector<T> buffer;
  unsigned readptr, writeptr, used, size;
};
