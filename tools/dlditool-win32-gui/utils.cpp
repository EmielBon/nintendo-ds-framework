/***********************************************************************
**
** Module: utils.cpp
**
** Description: Repository for general utility routines.
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
#include <shlobj.h>

#include "utils.h"

// Allocates an empty string of 'size' chars. If 'source' is not NULL, string is
// intialized with source.
char * new_stringA(char *source, int length)
	{
	char *destination = NULL;
	if(!length && source)
		length = strlen(source);

	if(length)
		{
		int alloc = length + 1;
		destination = new char[alloc + 1];
		memset(destination, 0, alloc + 1);
		if(source)
			{
			memcpy(destination, source, strlen(source));
			}
		}

	return destination;
	}

// Returns allocated combination of 'source' and 'other'.
char *combine_stringsA(char *source, char *other)
	{
	long source_len = strlen(source);
	long other_len = strlen(other);
	long size = source_len + other_len + 1;

	char *new_string = new char[size];
	if(new_string)
		{
		memset(new_string, 0, size);
		memcpy(new_string, source, source_len);
		memcpy(new_string + source_len, other, other_len);

		return new_string;
		}

	return NULL;
	}

// Callback function to set the current directory for the folder browser.
int CALLBACK browse_for_folder_init(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
	{
	if(uMsg==BFFM_INITIALIZED)
		{
		SendMessage(hWnd, BFFM_SETSELECTION, TRUE, lpData);

		// Simulate a TAB to make the treeview the current focus.
		// Maybe use SendInput??
		keybd_event(VK_TAB, 0, 0, NULL);
		keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, NULL);
		}

	return 0;
	}

BOOL browse_for_folder(HWND hWnd, char **folder, char *current_dir, char *browse_title)
	{
	typedef HRESULT (CALLBACK* DLLGETVERSIONPROC)(LPVOID);
	DLLGETVERSIONPROC get_ver = NULL;
	
	LPMALLOC lpMalloc;
	BROWSEINFO browse_info;
	LPITEMIDLIST lpItemIDList;
	BOOL ok = FALSE;

	char display_name[MAX_PATH]={0};

	if(::SHGetMalloc(&lpMalloc) == NOERROR)
		{
		// Fill in browse information.
		browse_info.hwndOwner = hWnd;
		browse_info.pidlRoot = NULL; 
		browse_info.pszDisplayName = display_name;
		browse_info.lpszTitle = browse_title;
		browse_info.ulFlags = 0;
		browse_info.lpfn = browse_for_folder_init;
		browse_info.lParam = (LPARAM)(LPCSTR)current_dir;
		
		// Need to check if we can add an edit area.
		HMODULE check_lib = LoadLibrary("shell32.dll");
		if(check_lib)
			{
			get_ver = (DLLGETVERSIONPROC) GetProcAddress(check_lib, "DllGetVersion");
			if(get_ver)
				// Newer version of shell32.dll so we can.
				browse_info.ulFlags |= BIF_EDITBOX;

			FreeLibrary(check_lib);
			}

			if((lpItemIDList=::SHBrowseForFolder(&browse_info)) != NULL)
			// Get the path of the selected folder from the item ID list.
			if(::SHGetPathFromIDList(lpItemIDList, display_name))
				{
				// We got a path back, so check if we've browsed to a different
				// directory. 
				int len = strlen(display_name);
				if(len)
					{
					// Remove trailing slash.
					if(display_name[len-1]=='\\')
						len--;

					*folder = new_stringA(display_name, len);
					ok = TRUE;
					}
				}

		// Deallocate structures.
		lpMalloc->Free(lpItemIDList);
		lpMalloc->Release();
		}
	
	return ok;
	}

char *get_listbox_string(HWND list_box, long index)
	{
	if(index==-1)
		index = SendMessage(list_box, LB_GETCURSEL, 0, 0);

	int alloc = SendMessage(list_box, LB_GETTEXTLEN, index, 0);
	char *string = new_stringA(NULL, alloc);
	SendMessage(list_box, LB_GETTEXT, index, (LPARAM)string);

	return string;
	}