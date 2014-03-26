/***********************************************************************
**
** Module: settings.h
**
** Description: Functions and structure defines for settings.cpp.
**
** Author: Adam Hodson - bob fossil
**
** Created: 25/12/2006
**
** Modified: -
**
** Copyright (C) 2006 Adam Hodson
** All Rights Reserved
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
** 
** The author can be contacted via Email at 
**
***********************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

void load_settings(char *path);
void save_settings(char *path);

struct settings
	{
	char *dldi_path;
	};

extern settings current_settings;

#endif