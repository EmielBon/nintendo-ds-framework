/*
    dlditool - Dynamically Linked Disk Interface patch tool
    Copyright (C) 2006  Michael Chisholm (Chishm)

	Send all queries to chishm@hotmail.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

	* v1.00 - 2006-12-25 - Chishm
		* Original release

	* v1.01 - 2006-12-30 - Chishm
		* Minor bugfix parsing 3 arguments

	* v1.10 - 2007-01-07 - Chishm
		* Removed assumptions about endianess of computer
			* Word size shouldn't matter now either, except that an int type must be at least 32 bits long
		* Added *.sc.nds and *.gba.nds file extensions
		* Improved command line argument parsing

	* v1.20 - 2007-01-11 - Chishm
		* Changed offset calculation method

	* v1.21 - 2007-01-12 - Chishm
		* Improved error messages
*/

#include <stdio.h>

#include "dlditool.h"
#include "dlditool32.h"

char line[512]={0};

addr_t readAddr (data_t *mem, addr_t offset) {
	return (addr_t)( 
			(mem[offset + 0] << 0) |
			(mem[offset + 1] << 8) |
			(mem[offset + 2] << 16) |
			(mem[offset + 3] << 24)
		);
}

void writeAddr (data_t *mem, addr_t offset, addr_t value) {
	mem[offset + 0] = (data_t)(value >> 0);
	mem[offset + 1] = (data_t)(value >> 8);
	mem[offset + 2] = (data_t)(value >> 16);
	mem[offset + 3] = (data_t)(value >> 24);
}

int stringCaseInsensitiveCompare (const char *str1, const char *str2) {
	while (tolower(*str1) == tolower(*str2)) {
		if (*str1 == '\0') {
			return 0;
		}
		str1++;
		str2++;
	}
	return (tolower(*str1) - tolower(*str2));
}

bool stringEndsWith (const char *str, const char *end) {
	const char* strEnd;
	if (strlen (str) < strlen(end)) {
		return false;
	}
	strEnd = &str[strlen (str) - strlen(end)];
	return (stringCaseInsensitiveCompare (strEnd, end) == 0);			
}

bool stringStartsWith (const char *str, const char *start) {
	return (strstr (str, start) == str);
}

addr_t quickFind (const data_t* data, const data_t* search, size_t dataLen, size_t searchLen) {
	const int* dataChunk = (const int*) data;
	int searchChunk = ((const int*)search)[0];
	addr_t i;
	addr_t dataChunkEnd = (addr_t)(dataLen / sizeof(int));

	for ( i = 0; i < dataChunkEnd; i++) {
		if (dataChunk[i] == searchChunk) {
			if ((i*sizeof(int) + searchLen) > dataLen) {
				return -1;
			}
			if (memcmp (&data[i*sizeof(int)], search, searchLen) == 0) {
				return i*sizeof(int);
			}
		}
	}

	return -1;
}

int patch(char *dldiFileName, char *appFileName)
	{
	addr_t memOffset = 0;		// Position of the loaded binary after loading into memory
	addr_t fileOffset = 0;		// Position of the loaded binary within the file
	addr_t patchOffset;			// Position of patch destination in the file
	addr_t relocationOffset;	// Value added to all offsets within the patch to fix it properly
	addr_t ddmemOffset;			// Original offset used in the DLDI file
	addr_t ddmemStart;			// Start of range that offsets can be in the DLDI file
	addr_t ddmemEnd;			// End of range that offsets can be in the DLDI file
	addr_t ddmemSize;			// Size of range that offsets can be in the DLDI file

	addr_t addrIter;

	FILE* dldiFile;
	FILE* appFile;

	data_t *pDH;
	data_t *pAH;

	data_t *appFileData = NULL;
	size_t appFileSize = 0;
	data_t *dldiFileData = NULL;
	size_t dldiFileSize = 0;
	
	if (!(dldiFile = fopen (dldiFileName, "rb"))) {
		wsprintf (line, "Cannot open \"%s\" - %s\r\n", dldiFileName, strerror(errno));
		log_line_to_window(line);
		if (!stringEndsWith (dldiFileName, dldiFileExtension)) {
			strcat (dldiFileName, dldiFileExtension);
			wsprintf (line, "Trying \"%s\"\r\n", dldiFileName);
			log_line_to_window(line);
			if (!(dldiFile = fopen (dldiFileName, "rb"))) {
				wsprintf (line, "Cannot open \"%s\" - %s\r\n", dldiFileName, strerror(errno));
				log_line_to_window(line);
				return -1;
			}
		} else {
			return -1;
		}
	}

	if (!(appFile = fopen (appFileName, "rb+"))) {
		wsprintf (line, "Cannot open \"%s\" - %s\n", appFileName, strerror(errno));
		log_line_to_window(line);
		return -1;
	}

	// Load the app file and the DLDI patch file
	fseek (appFile, 0, SEEK_END);
	appFileSize = ftell(appFile);
	appFileData = (data_t*) malloc (appFileSize);
	fseek (appFile, 0, SEEK_SET);

	fseek (dldiFile, 0, SEEK_END);
	dldiFileSize = ftell(dldiFile);
	dldiFileData = (data_t*) malloc (dldiFileSize);
	fseek (dldiFile, 0, SEEK_SET);

	if (!appFileData || !dldiFileData) {
		fclose (appFile);
		fclose (dldiFile);
		if (appFileData) free (appFileData);
		if (dldiFileData) free (dldiFileData);
		wsprintf (line, "Out of memory\r\n");
		log_line_to_window(line);
		return -1;
	}

	fread (appFileData, 1, appFileSize, appFile);
	fread (dldiFileData, 1, dldiFileSize, dldiFile);
	fclose (dldiFile);

	// Find the DSDI reserved space in the file
	patchOffset = quickFind (appFileData, dldiMagicString, appFileSize, sizeof(dldiMagicString)/sizeof(char));

	if (patchOffset < 0) {
		wsprintf (line, "%s does not have a DLDI section\r\n", appFileName);
		log_line_to_window(line);
		return -1;
	}

	pDH = dldiFileData;
	pAH = &appFileData[patchOffset];

	// Make sure the DLDI file is valid and usable
	if (strcmp ((char *)dldiMagicString, (char*)&pDH[DO_magicString]) != 0) {
		wsprintf (line, "Invalid DLDI file\r\n");
		log_line_to_window(line);
		return -1;
	}
	if (pDH[DO_version] != DLDI_VERSION) {
		wsprintf (line, "Incorrect DLDI file version. Expected %d, found %d.\r\n", DLDI_VERSION, pDH[DO_version]);
		log_line_to_window(line);
		return -1;
	}
	if (pDH[DO_driverSize] > pAH[DO_allocatedSpace]) {
		wsprintf (line, "Not enough space for patch. Available %d bytes, need %d bytes\r\n", ( 1 << pAH[DO_allocatedSpace]), ( 1 << pDH[DO_driverSize]) );
		log_line_to_window(line);
		return -1;
	}

	memOffset = readAddr (pAH, DO_text_start);
	if (memOffset == 0) {
			memOffset = readAddr (pAH, DO_startup) - DO_code;
	}

	ddmemOffset = readAddr (pDH, DO_text_start);
	relocationOffset = memOffset - ddmemOffset;

	wsprintf (line, "Old driver:          %s\r\n", &pAH[DO_friendlyName]);
	log_line_to_window(line);
	wsprintf (line, "New driver:          %s\r\n", &pDH[DO_friendlyName]);
	log_line_to_window(line);
	wsprintf (line, "\r\n");
	log_line_to_window(line);
	wsprintf (line, "Position in file:    0x%08X\r\n", patchOffset);
	log_line_to_window(line);
	wsprintf (line, "Position in memory:  0x%08X\r\n", memOffset);
	log_line_to_window(line);
	wsprintf (line, "Patch base address:  0x%08X\r\n", ddmemOffset);
	log_line_to_window(line);
	wsprintf (line, "Relocation offset:   0x%08X\r\n", relocationOffset);
	log_line_to_window(line);
	wsprintf (line, "\r\n");
	log_line_to_window(line);

	ddmemStart = readAddr (pDH, DO_text_start);
	ddmemSize = (1 << pDH[DO_driverSize]);
	ddmemEnd = ddmemStart + ddmemSize;

	// Remember how much space is actually reserved
	pDH[DO_allocatedSpace] = pAH[DO_allocatedSpace];
	// Copy the DLDI patch into the application
	memcpy (pAH, pDH, dldiFileSize);

	// Fix the section pointers in the header
	writeAddr (pAH, DO_text_start, readAddr (pAH, DO_text_start) + relocationOffset);
	writeAddr (pAH, DO_data_end, readAddr (pAH, DO_data_end) + relocationOffset);
	writeAddr (pAH, DO_glue_start, readAddr (pAH, DO_glue_start) + relocationOffset);
	writeAddr (pAH, DO_glue_end, readAddr (pAH, DO_glue_end) + relocationOffset);
	writeAddr (pAH, DO_got_start, readAddr (pAH, DO_got_start) + relocationOffset);
	writeAddr (pAH, DO_got_end, readAddr (pAH, DO_got_end) + relocationOffset);
	writeAddr (pAH, DO_bss_start, readAddr (pAH, DO_bss_start) + relocationOffset);
	writeAddr (pAH, DO_bss_end, readAddr (pAH, DO_bss_end) + relocationOffset);
	// Fix the function pointers in the header
	writeAddr (pAH, DO_startup, readAddr (pAH, DO_startup) + relocationOffset);
	writeAddr (pAH, DO_isInserted, readAddr (pAH, DO_isInserted) + relocationOffset);
	writeAddr (pAH, DO_readSectors, readAddr (pAH, DO_readSectors) + relocationOffset);
	writeAddr (pAH, DO_writeSectors, readAddr (pAH, DO_writeSectors) + relocationOffset);
	writeAddr (pAH, DO_clearStatus, readAddr (pAH, DO_clearStatus) + relocationOffset);
	writeAddr (pAH, DO_shutdown, readAddr (pAH, DO_shutdown) + relocationOffset);

	if (pDH[DO_fixSections] & FIX_ALL) { 
		// Search through and fix pointers within the data section of the file
		for (addrIter = (readAddr(pDH, DO_text_start) - ddmemStart); addrIter < (readAddr(pDH, DO_data_end) - ddmemStart); addrIter++) {
			if ((ddmemStart <= readAddr(pAH, addrIter)) && (readAddr(pAH, addrIter) < ddmemEnd)) {
				writeAddr (pAH, addrIter, readAddr(pAH, addrIter) + relocationOffset);
			}
		}
	}

	if (pDH[DO_fixSections] & FIX_GLUE) { 
		// Search through and fix pointers within the glue section of the file
		for (addrIter = (readAddr(pDH, DO_glue_start) - ddmemStart); addrIter < (readAddr(pDH, DO_glue_end) - ddmemStart); addrIter++) {
			if ((ddmemStart <= readAddr(pAH, addrIter)) && (readAddr(pAH, addrIter) < ddmemEnd)) {
				writeAddr (pAH, addrIter, readAddr(pAH, addrIter) + relocationOffset);
			}
		}
	}

	if (pDH[DO_fixSections] & FIX_GOT) { 
		// Search through and fix pointers within the Global Offset Table section of the file
		for (addrIter = (readAddr(pDH, DO_got_start) - ddmemStart); addrIter < (readAddr(pDH, DO_got_end) - ddmemStart); addrIter++) {
			if ((ddmemStart <= readAddr(pAH, addrIter)) && (readAddr(pAH, addrIter) < ddmemEnd)) {
				writeAddr (pAH, addrIter, readAddr(pAH, addrIter) + relocationOffset);
			}
		}
	}

	if (pDH[DO_fixSections] & FIX_BSS) { 
		// Initialise the BSS to 0
		memset (&pAH[readAddr(pDH, DO_bss_start) - ddmemStart] , 0, readAddr(pDH, DO_bss_end) - readAddr(pDH, DO_bss_start));
	}

	// Write the patch back to the file
	fseek (appFile, patchOffset, SEEK_SET);
	fwrite (pAH, 1, ddmemSize, appFile);
	fclose (appFile);

	free (appFileData);
	free (dldiFileData);

	wsprintf (line, "Patched successfully\r\n");
	log_line_to_window(line);

	return 0;
	}

//
#include "settings.h"
#include "resource.h"
#include "version.h"
#include "utils.h"

char classname[] = "DLDIWnd";
char exe_path[MAX_PATH] = {0};

BOOL register_window_classes(HINSTANCE instance_handle);
BOOL init_instance(HINSTANCE hInstance, int nCmdShow, LPSTR command_line);
LRESULT CALLBACK main_dialog_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND main_hwnd = NULL, dialog_hwnd = NULL;
int tidying = 0;
settings current_settings;
char *folder_buffer = NULL;
char *files_buffer = NULL;
BOOL allocated_buffers = FALSE;
int total_size = 0;

void log_line_to_window(char *line)
	{
	int length = SendDlgItemMessage(dialog_hwnd, IDC_LOG_EDIT, WM_GETTEXTLENGTH, 0, 0);
	SendDlgItemMessage(dialog_hwnd, IDC_LOG_EDIT, EM_SETSEL, length, length);
	SendDlgItemMessage(dialog_hwnd, IDC_LOG_EDIT, EM_REPLACESEL, FALSE, (LPARAM)line);
	}

void tidy_dldi_combo(HWND hDlg)
	{
	HWND combo = GetDlgItem(hDlg, IDC_DLDI_COMBO);
	int items = SendMessage(combo, CB_GETCOUNT, 0, 0);

	if(!items)
		return;

	for(int remove = 0; remove < items; remove++)
		{
		dldi_combo *entry = (dldi_combo *)SendMessage(combo, CB_GETITEMDATA, remove, 0);

		delete entry->desc;
		delete entry->path;
		delete entry;
		}
	}

void tidy_up()
	{
	if(tidying)
		return;
	else
		tidying = 1;

	save_settings(exe_path);

	tidy_dldi_combo(dialog_hwnd);

	delete current_settings.dldi_path;
	delete folder_buffer;
	delete files_buffer;

	// Stop drag and dropping.
	DragAcceptFiles(main_hwnd, FALSE);

	DestroyWindow(dialog_hwnd);

	tidying = 0;
	}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
	MSG message;

	if(!hPrevInstance)
		// Register the window class.
		if(!register_window_classes(hInstance))
			return FALSE;
	
	// Create the window and display it.
	if(!init_instance(hInstance, nCmdShow, lpCmdLine))
		return FALSE;

	// Message handling loop.
	while(GetMessage(&message, NULL, 0, 0))
		{
		if(dialog_hwnd && !IsDialogMessage(dialog_hwnd, &message))
			{
			TranslateMessage(&message);
			DispatchMessage(&message);
			}
		}

	return(message.wParam);
	}

BOOL register_window_classes(HINSTANCE instance_handle)
	{
	WNDCLASSEX window_class;
	
	// Fill in the window class struct.
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.cbSize = sizeof(WNDCLASSEX);
	window_class.lpfnWndProc = (WNDPROC)window_proc;
	window_class.cbClsExtra = 0;
	window_class.cbWndExtra = 0;
	window_class.hInstance = instance_handle;
	window_class.hIcon = LoadIcon(instance_handle, MAKEINTRESOURCE(IDI_ICON));
	window_class.hIconSm = NULL;
	window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	window_class.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;
	window_class.lpszMenuName = NULL;//MAKEINTRESOURCE(IDR_MENU);
	window_class.lpszClassName = classname;
	
	// Register the main window class.
	return(RegisterClassEx(&window_class));
	}

BOOL init_instance(HINSTANCE hInstance, int nCmdShow, LPSTR command_line)
	{
	RECT dialog_rect={0,0,0,0};
	int bottom = 0;

//	InitCommonControls();

	// Create the window.
	main_hwnd = CreateWindow(classname, "", WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX, 
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if(!main_hwnd)
		{
		// No window so bail out.
		return FALSE;
		}

	// We want to use drag and drop for this window.
	DragAcceptFiles(main_hwnd, TRUE);

	GetModuleFileName(hInstance, exe_path, MAX_PATH);
	char *slash = strrchr(exe_path, 0x5c);
	*slash = 0;

	load_settings(exe_path);

	dialog_hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN), main_hwnd, (DLGPROC)main_dialog_proc);
	if(dialog_hwnd)
		{

		// Size parent window around our dialog.
		GetWindowRect(dialog_hwnd, &dialog_rect);

		bottom = dialog_rect.bottom - dialog_rect.top + GetSystemMetrics(SM_CYCAPTION);

		SetWindowPos(main_hwnd, NULL, 0, 0, dialog_rect.right - dialog_rect.left, bottom, SWP_NOMOVE);

		SetWindowText(main_hwnd, WINDOW_TITLE);

		ShowWindow(main_hwnd, nCmdShow);

		return TRUE;
		}

	return FALSE;
	}

void populate_dldi_combo(HWND hDlg)
	{
	HWND combo = GetDlgItem(hDlg, IDC_DLDI_COMBO);
	WIN32_FIND_DATA find_data;
	int added = 0;
	char *search_path = combine_stringsA(current_settings.dldi_path, "\\*.dldi");
	int path_length = strlen(current_settings.dldi_path);

	tidy_dldi_combo(hDlg);

	SendMessage(combo, CB_RESETCONTENT, 0, 0);

	HANDLE file = FindFirstFile(search_path, &find_data);
	if(file!=INVALID_HANDLE_VALUE)
		{
		BOOL add = TRUE;
		while(add)
			{
			if(find_data.cFileName[0]!=0x2e)
				{
				if(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
					}
				else
					{
					int alloc = path_length + strlen(find_data.cFileName) + 1;
					char *full_path = new_stringA(current_settings.dldi_path, alloc);
					full_path[path_length]=0x5c;
					strcat(full_path, find_data.cFileName);

					HANDLE file = CreateFile(full_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

					if(file!=INVALID_HANDLE_VALUE)
						{
						DWORD read  = 0;
						DWORD size = 0;
						size = GetFileSize(file, NULL);

						unsigned char *buffer = new unsigned char[size];
						if(buffer)
							{
							if(ReadFile(file, buffer, size, &read, NULL))
								{
								dldi_combo *entry = new dldi_combo;
								entry->desc = new_stringA((char *)&buffer[DO_friendlyName]);
								entry->path = new_stringA(full_path);

								long index = SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)entry->desc);
								SendMessage(combo, CB_SETITEMDATA, index, (LPARAM)entry);

								added++;
								}

							delete buffer;
							}
						CloseHandle(file);
						}

					delete full_path;
					}
				}

			add = FindNextFile(file, &find_data);
			}
		FindClose(file);
		}

	EnableWindow(GetDlgItem(hDlg, IDC_PATCH), added ? TRUE : FALSE);
	SendMessage(combo, CB_SETCURSEL, 0, 0);

	delete search_path;
	}

LRESULT CALLBACK about_dialog_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
	switch(message)
		{
		case WM_INITDIALOG:
			{
			SetDlgItemText(hDlg, IDC_ABOUT4, VERSION_NUMBER_STRING);
			SetDlgItemText(hDlg, IDC_ABOUT6, VERSION);
			return TRUE;
			}
			break;

		case WM_COMMAND:
			{
			switch(LOWORD(wParam))
				{
				case IDOK:
					{
					EndDialog(hDlg, TRUE);
					}
					break;
				}
			}
			break;
		}

	return 0;
	}

UINT_PTR CALLBACK OFNHookProc(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
	{
	switch(uiMsg)
		{
		case WM_NOTIFY:
			{
			OFNOTIFY *notify = (OFNOTIFY *)lParam;
			switch(notify->hdr.code)
				{
				case CDN_SELCHANGE:
					{
					TCHAR buffer = {0};
					HWND parent = notify->hdr.hwndFrom;
					// Get the current sizes for the folder and files.
					int files_size = CommDlg_OpenSave_GetSpec(parent, &buffer, 1);
					int folder_size = CommDlg_OpenSave_GetFolderPath(parent, &buffer ,1);
					total_size = files_size + folder_size;

					if(total_size > (int)notify->lpOFN->nMaxFile)
						{
						// Allocate larger buffers to accomodate files.
						delete folder_buffer;
						folder_buffer = new_stringA(NULL, folder_size);
						CommDlg_OpenSave_GetFolderPath(parent, folder_buffer, folder_size);

						delete files_buffer;
						files_buffer = new_stringA(NULL, files_size);
						CommDlg_OpenSave_GetSpec(parent, files_buffer, files_size);

						allocated_buffers = TRUE;
						}
					else
						{
						// Remove buffers as the files fit in the existing buffers.
						delete folder_buffer;
						folder_buffer = NULL;
						delete files_buffer;
						files_buffer = NULL;

						allocated_buffers = FALSE;
						}
					}
					break;
				}
			}
			break;
		}
	return 0;
	}

void add_files_to_list(HWND hDlg, char *path, int offset)
	{
	if(offset > (int)strlen(path))
		{
		// Multiple files selected.
		// If the files fitted in the MAX_PATH buffer, format will be:
		// "path\0name 1\0name 2\0\0"
		// otherwise it will be
		// "path\0"name 1" "name 2"\0\0"
		char *path_end = path + strlen(path);
		char *next = NULL, *current = path_end + 1; 

		// The path might not end in a slash, we can overwrite the null with no adverse effects.
		if(*(path_end-1)!='\\')
			*path_end++='\\';

		while(*current!= '\0')
			{
			if(*current==0x22)	// '"'
				{
				// Skip '"'.
				char *start = current + 1;
				// Find the end '"'.
				char *end = strchr(start, 0x22);
				if(end)
					{
					current = start;
					// Terminate string.
					*end = 0;
					end++;
					if(*end)
						next = end + 1;
					}

				}
			else
				next = current + strlen(current) + 1;

			// Append string to the path.
			strcpy(path_end, current);
			SendDlgItemMessage(hDlg, IDC_BINARY_LIST, LB_ADDSTRING, 0, (LPARAM)path);
			current = next;
			}
		}
	else
		// Just a single file.
		SendDlgItemMessage(hDlg, IDC_BINARY_LIST, LB_ADDSTRING, 0, (LPARAM)path);
	}

LRESULT CALLBACK main_dialog_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
	switch(message)
		{
		case WM_INITDIALOG:
			{
			populate_dldi_combo(hDlg);

			return TRUE;
			}
			break;

		case WM_NOTIFY:
			{
			}
			break;

		case WM_COMMAND:
			{
			switch(LOWORD(wParam))
				{
				case IDC_DLDI_BROWSE:
					{
					char *folder = NULL;
					if(browse_for_folder(hDlg, &folder, current_settings.dldi_path, "Select DLDI directory"))
						{
						delete current_settings.dldi_path;
						current_settings.dldi_path = folder;
						populate_dldi_combo(hDlg);
						}
					}
					break;

				case IDC_BINARY_BROWSE:
					{
					allocated_buffers = FALSE;

					char *path = new_stringA(NULL, MAX_PATH);
					OPENFILENAME openfilename;
					memset(&openfilename, 0, sizeof(OPENFILENAME));

					openfilename.lStructSize = sizeof(OPENFILENAME);
					openfilename.hwndOwner = hDlg;
					openfilename.lpstrFile = path;
					openfilename.nMaxFile = MAX_PATH;
					openfilename.lpstrTitle = "Open binary file";
					openfilename.Flags |= OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_ENABLEHOOK;
					openfilename.lpstrFilter = "Nintendo DS binaries (*.nds;*.ds.gba)\0*.nds;*.ds.gba\0All files (*.*)\0*.*\0";
					openfilename.lpfnHook = OFNHookProc;

					if(GetOpenFileName(&openfilename))
						{
						add_files_to_list(hDlg, path, openfilename.nFileOffset);
						}
					else
						{
						DWORD error = CommDlgExtendedError();
						if(error == FNERR_BUFFERTOOSMALL && allocated_buffers)
							{
							// Combine folder and file buffers into one buffer.
							char *new_path = new_stringA(folder_buffer, total_size);

							int folder_length = strlen(folder_buffer); 
							memcpy(new_path + (folder_length + 1), files_buffer, total_size - (folder_length + 1));

							add_files_to_list(hDlg, new_path, total_size);

							delete new_path;
							}
						}

					delete path;
					}
					break;

				case IDC_CLEAR:
					{
					SendDlgItemMessage(hDlg, IDC_BINARY_LIST, LB_RESETCONTENT, 0, 0);
					}
					break;

				case IDC_ABOUT:
					{
					HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE);
					DialogBox(hInstance,MAKEINTRESOURCE(IDD_ABOUT), hDlg, (DLGPROC)about_dialog_proc);
					}
					break;

				case IDC_PATCH:
					{
					// See which .dldi file we're using.
					HWND combo = GetDlgItem(hDlg, IDC_DLDI_COMBO);
					long index = SendMessage(combo, CB_GETCURSEL, 0, 0);
					if(index==CB_ERR)
						break;

					dldi_combo *entry = (dldi_combo *)SendMessage(combo, CB_GETITEMDATA, index, 0);
					if(!entry)
						break;

					char *ddi_path = entry->path;

					HWND list = GetDlgItem(hDlg, IDC_BINARY_LIST);
					int items = SendMessage(list, LB_GETCOUNT, 0, 0);

					for(int apply = 0; apply < items; apply++)
						{
						char *app_path = get_listbox_string(list, apply);
						if(app_path)
							{				
							if(items > 1)
								{
								wsprintf(line, "\r\nProcessing '%s'\r\n\r\n", app_path);
								log_line_to_window(line);
								}
							}

						patch(ddi_path, app_path);

						delete app_path;
						}

					}
					break;
				}
			}
			break;

		}

	return 0;
	}

// Window procedure for the main window.
LRESULT CALLBACK window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
	switch(message)
		{
		case WM_DROPFILES:
			{
			HDROP drop_handle = (HDROP)wParam;
			// We got a handle from the drag and drop, so find out how many
			// files there are.

			int dropped_files = DragQueryFile(drop_handle, 0xFFFFFFFF, NULL, 0);
			if(dropped_files)
				{
				// Loop through the files and add them.
				for(int add = 0; add < dropped_files; add++)
					{
					int buffer_size = DragQueryFile(drop_handle, add, NULL, 0);
					char *buffer = new_stringA(NULL, buffer_size);
					DragQueryFile(drop_handle, add, buffer, buffer_size +1);
					if(strlen(buffer))
						{
						SendDlgItemMessage(dialog_hwnd, IDC_BINARY_LIST, LB_ADDSTRING, 0, (LPARAM)buffer);
						}
					delete buffer;
					}
				DragFinish(drop_handle);
				}
			}
			break;

		case WM_SETFOCUS:
			SetFocus(dialog_hwnd);
			break;

		case WM_DESTROY:
			{
			// Tidy up here.
			tidy_up();

			PostQuitMessage(0);
			break;
			}

		default:	
			return(DefWindowProc(hWnd, message, wParam, lParam));
		}

	return 0;
	}

