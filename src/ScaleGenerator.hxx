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
#ifndef __SCALEGENERATOR_HXX__
#define __SCALEGENERATOR_HXX__

#include "../build/config.h"

// C++ Standard Headers
#include <cstdint>
#include <memory>
// C Standard Headers
#ifdef HAVE_TIMEH
#include <time.h>
#endif

#ifdef __APPLE__
#include <stdlib.h>
#endif

// Boost Headers


// 3rd Party Headers


// GTK Headers


// Our Headers

namespace exgen
{
	class ScaleGenerator
	{
	public:
		ScaleGenerator(uint8_t *scaleNotes, uint8_t numNotes);
		virtual ~ScaleGenerator();

		std::unique_ptr<uint8_t> generateExercise(uint8_t key, uint8_t baseOctave, uint8_t numOctaves, size_t exerciseLength);

	protected:
		uint8_t numNotes;
		uint8_t *scaleNotes;
	};
}


#endif // __SCALEGENERATOR_HXX__
