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
#ifndef __MIDIEXPORTER_HXX__
#define __MIDIEXPORTER_HXX__

// C++ Standard Headers
#include <memory>
#include <cstdint>
// C Standard Headers

// Boost Headers

// 3rd Party Headers


// GTK Headers


// Our Headers

namespace exgen
{
	class MidiExporter
	{
	public:
		static int ExportExerciseToMidiFile(uint8_t *exercise, size_t exerciseLength, const char *filePath);

	};
}


#endif // __MIDIEXPORTER_HXX__
