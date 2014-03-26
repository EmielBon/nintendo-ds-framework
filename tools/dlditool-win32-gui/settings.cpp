/***********************************************************************
**
** Module: settings.cpp
**
** Description: Routines to load and save settings.
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

#include <windows.h>

#include "settings.h"
#include "utils.h"

char ini_name[]="\\dlditool32.ini";
char settings[]="Settings";

char *profile_lookup[]=
	{
	"",
	"DLDI Path",
	};

#define PROFILE_DLDIPATH		1

void load_settings(char *path)
	{
	char *ini_path = combine_stringsA(path, ini_name);

	char buffer[MAX_PATH] = {0};

	GetPrivateProfileString(settings, profile_lookup[PROFILE_DLDIPATH], "", buffer, MAX_PATH, ini_path);

	if(strlen(buffer))
		current_settings.dldi_path = new_stringA(buffer);
	else
		current_settings.dldi_path = new_stringA(path);

	delete ini_path;
	}

void save_settings(char *path)
	{
	char *ini_path = combine_stringsA(path, ini_name);

	WritePrivateProfileString(settings, profile_lookup[PROFILE_DLDIPATH], current_settings.dldi_path, ini_path);

	delete ini_path;
	}