/***********************************************************************
**
** Module: dlditool32.h
**
** Description: Functions and structure defines for dldiool32.cpp.
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

#ifndef DLDITOOL32_H
#define DLDITOOL32_H

#include <windows.h>
#include <shellapi.h>

struct dldi_combo
	{
	char *desc;
	char *path;
	};

void log_line_to_window(char *line);

#endif