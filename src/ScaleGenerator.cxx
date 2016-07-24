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
// C Standard Headers


// Boost Headers

// 3rd Party Headers


// GTK Headers


// Our Headers
#include "ScaleGenerator.hxx"

namespace exgen
{
	ScaleGenerator::ScaleGenerator(uint8_t *scaleNotes, uint8_t numNotes)
	{
		this->scaleNotes = new uint8_t[numNotes];
		memset(&this->scaleNotes[0], 0, numNotes);
		memcpy(&this->scaleNotes[0], &scaleNotes[0], numNotes);
		this->numNotes = numNotes;
	}

	ScaleGenerator::~ScaleGenerator()
	{
		if (scaleNotes)
			delete[] scaleNotes;
		scaleNotes = nullptr;
	}

	std::unique_ptr<uint8_t> ScaleGenerator::generateExercise(uint8_t keyNote, uint8_t baseOctave, uint8_t numOctaves, size_t exerciseLength)
	{
		auto exercise = std::unique_ptr<uint8_t>(new uint8_t[exerciseLength]);
		memset(exercise.get(), 0, exerciseLength);

		srand(time(NULL));

		uint8_t midiBaseNote = baseOctave + keyNote;


		for (size_t i = 0; i < exerciseLength; ++i)
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
