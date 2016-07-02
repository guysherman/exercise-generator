/*
  Copyright (C) 2016 Guy Sherman

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#ifndef __HEADERNAME_HXX__
#define __HEADERNAME_HXX__



// C++ Standard Headers
#include <vector>
#include <cstdint>
#include <cstring>

// C Standard Headers
#include <stddef.h>

// Boost Headers

// 3rd Party Headers


// GTK Headers


// Our Headers

namespace grs
{
	namespace util
	{
		class ByteBuffer
		{
		public:
			ByteBuffer() {}
			virtual ~ByteBuffer() {}

			void Write(const char *cstr, size_t length)
			{
				guaranteeCapacity(length);
				auto it = buffer.end();
				char *destination = &(*it);
				buffer.resize(buffer.size() + length, 0x00);
				memcpy(destination, cstr, length);
			}

			template<typename TNumeric>
			void Write(TNumeric value)
			{
				size_t valueSize = sizeof(TNumeric);
				guaranteeCapacity(valueSize);
				auto it = buffer.end();
				char *destination = &(*it);
				buffer.resize(buffer.size() + valueSize, 0x00);
				memcpy(destination, &value, valueSize);
			}

			char *Data()
			{
				return buffer.data();
			}

			size_t Size()
			{
				return buffer.size();
			}

		private:
			void guaranteeCapacity(size_t size)
			{
				size_t requiredCapcity = buffer.size() + size;
				if (buffer.capacity() < requiredCapcity)
				{
					buffer.reserve(requiredCapcity);
				}
			}

			//void setCapacity(size_t capacity);
			//size_t GetCapacity();
			std::vector<char> buffer;
		};
	}
}

#endif // __HEADERNAME_HXX__
