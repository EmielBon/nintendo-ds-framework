===============================================================================
                         ensata NITRO Software Emulator
                             1.3c
                                                              Created: 12/03/2004
                                                    Copyright (C) 2004 Nintendo
===============================================================================

Introduction
    ensata NITRO Software Emulator (ensata) was developed as a debug target for
    development of NITRO applications.

Operating Environment
    Windows XP/2000 (SP4 + IE6)
    Runtime of DirectX 8 or higher (DirectX 9 or higher when using Direct3D)

File Structure
   [ensata]
      |-[dlls]
      |   |-StrRes_eng.dll
      |   |-uimain.dll
      |
      |-[ext_dlls]
      |   |-est_is_chara.dll
      |   |-est_nitro_viewer.dll
      |
      |-[Help]
      |   |-ensata.chm
      |   |-ensata_jp.chm
      |
      |-[Release]
      |   |-ensata.exe
      |
      |-[skins]
      |   |-default_skin.bmp
      |
      |-[unreg]
      |   |-unreg.exe
      |
      |-Readme.txt
      |-Readme_jp.txt


Installation
* For new installation:
    If installing for the first time, copy the above folder structure to an
    appropriate location.

* For minor updates:
    When a previous version has already been installed and activated, copy 
    the above folder structure to the install folder. The initialization file 
    and activation information can continue to be used.

*For major updates:
    When a previous version has already been installed, copy the files into 
    the install folder. The initialization file can continue to be used. 
    The activation information cannot be used; be sure to reactivate the 
    software.

Uninstall
    Delete manually. Be sure to follow the order shown below.
    (1) Delete the registry key
        Delete the registry key used by ensata.
        Run the deletion tool "unreg/unreg.exe" in the ensata installation 
        folder.
    (2) Delete the files
        Manually delete the folder where the files were copied during 
        installation.

Activation
    Before running ensata for the first time, it must be activated. See the 
    "Startup" page in "Help/ensata.chm" for details.

    This version will expire on December 31, 2004, or 180 days after activation,
    whichever comes first. To continue use after expiration, access the
    SDSG website (www.warioworld.com) and download the new version or 
    re-activate the program.

[Supplemental Information: Sub Processor Implementation]
    On ensata, the implementation of the Sub Processor is by a software patch 
    compatible with the NitroSDK or NitroSystem (the development environment).
    Consequently, it will not operate properly on versions of the development 
    environment that do not support it. Confirm the supported development
    environment version by selecting [About ensata] from [Setting] on the ensata menu.