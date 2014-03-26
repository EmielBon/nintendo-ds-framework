/***********************************************************************
**
** Module: utils.h
**
** Description: Functions and structure defines for utils.cpp.
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

#ifndef UTILS_H
#define UTILS_H

// Prototypes.
char * new_stringA(char *source, int length = 0);
char *combine_stringsA(char *source, char *other);
BOOL browse_for_folder(HWND hWnd, char **folder, char *current_dir, char *browse_title);
char *get_listbox_string(HWND list_box, long index);

#endif