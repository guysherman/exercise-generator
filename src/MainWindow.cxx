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
#include <iostream>
#include <utility>

// C Standard Headers


// Boost Headers


// 3rd Party Headers


// GTK Headers


// Our Headers
#include "MainWindow.hxx"
#include "MajorScaleGenerator.hxx"
#include "MinorScaleGenerator.hxx"
#include "MidiExporter.hxx"

namespace grsgtkutil
{
	class LS1Columns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		LS1Columns()
		{
			this->add(this->Key);
			this->add(this->Value);
		}

		Gtk::TreeModelColumn<gint> Key;
		Gtk::TreeModelColumn<Glib::ustring> Value;
	};

	LS1Columns kvpCols;

	std::pair<gint, Glib::ustring> getSelectedValueFromCombo(const char* comboId, Glib::RefPtr<Gtk::Builder> builder)
	{
		std::pair<gint, Glib::ustring> result(-1, "");
		Gtk::ComboBox *combo = nullptr;
		builder->get_widget(comboId, combo);
		if (combo != nullptr)
		{
			Gtk::TreeModel::iterator iter = combo->get_active();
			if (iter != nullptr)
			{
				Gtk::TreeModel::Row row = *iter;
				if (row != nullptr)
				{
					gint key = row[kvpCols.Key];
					Glib::ustring value = row[kvpCols.Value];
					result = std::pair<gint, Glib::ustring>(key, value);
				}
			}
		}

		return result;
	}
}

namespace exgen
{
	MainWindow::MainWindow()
	{
		char filePath[512];
		memset(&filePath[0], 0, 512);
		char *resPrefix = getenv("EXGEN_RES_PREFIX");
		sprintf(&filePath[0], "%s/MainWindow.glade", resPrefix);
		builder = Gtk::Builder::create_from_file(filePath);
		Gtk::Button *button = nullptr;
		builder->get_widget("generateButton", button);

		if (button != nullptr)
		{
			button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onButtonClicked));
		}
	}

	void MainWindow::onButtonClicked()
	{

		auto selectedKey = grsgtkutil::getSelectedValueFromCombo("keyCombo", builder);
		//std::cout << "Selected key is {" << selectedKey.first << ", " << selectedKey.second << "}" << std::endl;


		auto selectedScale = grsgtkutil::getSelectedValueFromCombo("scaleCombo", builder);
		//std::cout << "Selected scale is: {" << selectedScale.first << ", " << selectedScale.second << "}" << std::endl;

		auto selectedOctave = grsgtkutil::getSelectedValueFromCombo("startingOctaveCombo", builder);
		//std::cout << "Selected ocatve is: {" << selectedOctave.first << ", " << selectedOctave.second << "}" << std::endl;

		Gtk::SpinButton *numOctavesSpin = nullptr;
		builder->get_widget("numOctaves", numOctavesSpin);
		auto numOctaves = numOctavesSpin->get_adjustment()->get_value();
		//std::cout << "Selected number of octaves is: " << (int)numOctaves << std::endl;

		ScaleGenerator *gen = nullptr;

		switch (selectedScale.first)
		{
			case 1:
				gen = new MinorScaleGenerator();
				break;
			case 0:
			default:
				gen = new MajorScaleGenerator();
				break;
		}

		std::unique_ptr<uint8_t> exercise = gen->generateExercise((uint8_t)selectedKey.first, (uint8_t)selectedOctave.first, (uint8_t)numOctaves, 96);

		// for (int i = 0; i < 96; ++i)
		// {
		// 	std::cout << (int) exercise.get()[i] << ", ";
		// }
		//
		// std::cout << std::endl;

		Gtk::FileChooserDialog dialog("Please choose an file to save to", Gtk::FILE_CHOOSER_ACTION_SAVE);
		Gtk::Window *window = GetWindow();
		dialog.set_transient_for(*window);

		//Add response buttons the the dialog:
		dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
		dialog.add_button("Select", Gtk::RESPONSE_OK);

		int result = dialog.run();

		//Handle the response:
		switch(result)
		{
			case(Gtk::RESPONSE_OK):
			{
				//std::cout << "File selected: " << dialog.get_filename() << std::endl;
				MidiExporter::ExportExerciseToMidiFile(exercise.get(), 96, dialog.get_filename().c_str());
				break;
			}
			case(Gtk::RESPONSE_CANCEL):
			{
				//std::cout << "Cancel clicked." << std::endl;
				break;
			}
			default:
			{
				//std::cout << "Unexpected button clicked." << std::endl;
				break;
			}
		}

		if (gen != nullptr)
		{
			delete gen;
		}


	}

	MainWindow::~MainWindow() {}

	Gtk::Window *MainWindow::GetWindow()
	{
		Gtk::Window *window = nullptr;
		builder->get_widget("MainWindow", window);
		return window;
	}


}
