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


// C Standard Headers


// Boost Headers


// 3rd Party Headers


// GTK Headers


// Our Headers
#include "MainWindow.hxx"


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
		Gtk::ComboBox *keyCombo = nullptr;
		builder->get_widget("keyCombo", keyCombo);
		if (keyCombo != nullptr)
		{
			Gtk::TreeModel::iterator iter = keyCombo->get_active();
			if (iter != nullptr)
			{
				Gtk::TreeModel::Row row = *iter;
				if (row != nullptr)
				{
					gint id = row[ls1Cols.Id];
					Glib::ustring keyName = row[ls1Cols.KeyName];
					std::cout << "Selected key is: {" << id << ", " << keyName << "}" << std::endl;
				}
			}
		}

		Gtk::ComboBox *scaleCombo = nullptr;
		builder->get_widget("scaleCombo", scaleCombo);
		if (scaleCombo != nullptr)
		{
			auto iter = scaleCombo->get_active();
			if (iter != nullptr)
			{
				auto row = *iter;
				if (row != nullptr)
				{
					gint id = row[ls2Cols.Id];
					Glib::ustring scaleName = row[ls2Cols.ScaleName];
					std::cout << "Selected scale is: {" << id << ", " << scaleName << "}" << std::endl;
				}
			}
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
