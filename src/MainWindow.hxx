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
#ifndef __MAINWINDOW_HXX__
#define __MAINWINDOW_HXX__

// C++ Standard Headers

// C Standard Headers


// Boost Headers

// 3rd Party Headers


// GTK Headers
#include <gtkmm.h>



// Our Headers

namespace exgen
{
	class LS1Columns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		LS1Columns()
		{
			this->add(this->KeyName);
			this->add(this->Id);
		}

		Gtk::TreeModelColumn<Glib::ustring> KeyName;
		Gtk::TreeModelColumn<gint> Id;
	};

	class LS2Columns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		LS2Columns()
		{
			this->add(this->Id);
			this->add(this->ScaleName);
		}

		Gtk::TreeModelColumn<gint> Id;
		Gtk::TreeModelColumn<Glib::ustring> ScaleName;
	};

	class MainWindow
	{
	public:
		MainWindow();
		virtual ~MainWindow();

		Gtk::Window *GetWindow();

	protected:
		// Signal Handlers
		void onButtonClicked();

		// Member Widgets
		Glib::RefPtr<Gtk::Builder> builder;
		LS1Columns ls1Cols;
		LS2Columns ls2Cols;

	};


}

#endif // __MAINWINDOW_HXX__
