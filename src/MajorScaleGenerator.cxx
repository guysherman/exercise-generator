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

// C++ Standard Headers
#include <cstring>
#include <cstdlib>
#include <iostream>
// C Standard Headers
#include <time.h>

// Boost Headers

// 3rd Party Headers


// GTK Headers


// Our Headers
#include "MajorScaleGenerator.hxx"

namespace exgen
{
	MajorScaleGenerator::MajorScaleGenerator()
	{
		uint8_t notes[7] = {0, 2, 4, 5, 7, 9, 11};
		scaleNotes = new uint8_t[7];
		numNotes = 7;
		memcpy(scaleNotes, &notes[0], numNotes);
	}

	MajorScaleGenerator::~MajorScaleGenerator()
	{
		if (scaleNotes)
			delete[] scaleNotes;
		scaleNotes = nullptr;
	}

	std::unique_ptr<uint8_t> MajorScaleGenerator::generateExercise(uint8_t keyNote, uint8_t baseOctave, uint8_t numOctaves, size_t exerciseLength)
	{
		auto exercise = std::unique_ptr<uint8_t>(new uint8_t[exerciseLength]);
		memset(exercise.get(), 0, exerciseLength);

		srand(time(NULL));

		uint8_t midiBaseNote = baseOctave + keyNote;


		for (int i = 0; i < exerciseLength; ++i)
		{
			uint8_t random = rand() % (numNotes * numOctaves);
			uint8_t dividend = random / numNotes;
			uint8_t rem = random % numNotes;
			uint8_t noteOffset = (dividend * 12) + scaleNotes[rem];
			uint8_t note = midiBaseNote + noteOffset;
			exercise.get()[i] = note;
			//std::cout << "midiBaseNote= " << (int)midiBaseNote << ", random=" << (int)random << ", dividend=" << (int)dividend << ", rem=" << (int)rem << ", noteOffset=" << (int)noteOffset << ", note=" << (int)note << std::endl;
		}

		return exercise;
	}
}
