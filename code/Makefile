PROJECT_NAME = aRPiGi

#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/ds_rules

export TARGET		:=	$(PROJECT_NAME)
export TOPDIR		:=	$(CURDIR)

GAMEDATA	:= ../gamedata
GRAPHICS    := ../graphics
SOUND       := ../sound
MODELS 		:= $(GRAPHICS)/models
TEXTURES    := $(GRAPHICS)/textures
MAPS        := $(GRAPHICS)/maps
SPRITES     := $(GRAPHICS)/sprites
TILES		:= $(GRAPHICS)/tilesets
SCENES      := $(GRAPHICS)/scenes
FONTS       := $(GRAPHICS)/fonts

.PHONY: $(TARGET).arm7 $(TARGET).arm9

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
all: models textures maps sprites tilesets scenes fonts $(TARGET).nds

#---------------------------------------------------------------------------------
$(TARGET).nds	:	$(TARGET).arm7 $(TARGET).arm9 $(BINMODELS) 
	ndstool	-c $(TARGET).nds -7 $(TARGET).arm7 -9 $(TARGET).arm9 -d $(GAMEDATA)

#---------------------------------------------------------------------------------
$(TARGET).arm7	: arm7/$(TARGET).elf
$(TARGET).arm9	: arm9/$(TARGET).elf

#---------------------------------------------------------------------------------
arm7/$(TARGET).elf:
	$(MAKE) -C arm7
	
#---------------------------------------------------------------------------------
arm9/$(TARGET).elf:
	$(MAKE) -C arm9

#---------------------------------------------------------------------------------
MODELFILES 	:= $(wildcard $(MODELS)/*.obj)
BINMODELS  	:= $(addprefix $(GAMEDATA)/, $(notdir $(MODELFILES:.obj=.bin)))

models : $(BINMODELS)

$(GAMEDATA)/%.bin : $(MODELS)/%.obj
	$(ARPIGI)/tools/Anything2Bin/bin/Debug/Anything2Bin.exe $(ARPIGI)/code/$< $(ARPIGI)/code/$@ -model

cleanmodels :
	rm -f $(BINMODELS)

#---------------------------------------------------------------------------------
TEXTUREFILES := $(wildcard $(TEXTURES)/*.*)
BINTEXTURES  := $(addprefix $(GAMEDATA)/, $(notdir $(TEXTUREFILES:.png=.bin)))

textures : $(BINTEXTURES)

$(GAMEDATA)/%.bin : $(TEXTURES)/%.png
	$(ARPIGI)/tools/Anything2Bin/bin/Debug/Anything2Bin.exe $(ARPIGI)/code/$< $(ARPIGI)/code/$@ -bitmap

cleantextures :
	rm -f $(BINTEXTURES)

#---------------------------------------------------------------------------------
MAPFILES 	:= $(wildcard $(MAPS)/*.bin)
BINMAPS  	:= $(addprefix $(GAMEDATA)/, $(notdir $(MAPFILES:.bin=.bin)))

maps : $(BINMAPS)

$(GAMEDATA)/%.bin : $(MAPS)/%.bin
	cp -f $(ARPIGI)/code/$< $(ARPIGI)/code/$@

cleanmaps :
	rm -f $(BINMAPS)
	
#---------------------------------------------------------------------------------
SPRITEFILES 	:= $(wildcard $(SPRITES)/*.bin)
BINSPRITES  	:= $(addprefix $(GAMEDATA)/, $(notdir $(SPRITEFILES:.bin=.bin)))

sprites : $(BINSPRITES)

$(GAMEDATA)/%.bin : $(SPRITES)/%.bin
	cp -f $(ARPIGI)/code/$< $(ARPIGI)/code/$@

cleansprites :
	rm -f $(BINSPRITES)
	
#---------------------------------------------------------------------------------
TILEFILES 	:= $(wildcard $(TILES)/*.png)
BINTILES  	:= $(addprefix $(GAMEDATA)/, $(notdir $(TILEFILES:.png=.bin)))

tilesets : $(BINTILES)

$(GAMEDATA)/%.bin : $(TILES)/%.png
	$(ARPIGI)/tools/Anything2Bin/bin/Debug/Anything2Bin.exe $(ARPIGI)/code/$< $(ARPIGI)/code/$@ -tileset

cleantilesets :
	rm -f $(BINTILES)

#---------------------------------------------------------------------------------
SCENEFILES 	:= $(wildcard $(SCENES)/*.txt)
BINSCENES  	:= $(addprefix $(GAMEDATA)/, $(notdir $(SCENEFILES:.txt=.bin)))

scenes : $(BINSCENES)

$(GAMEDATA)/%.bin : $(SCENES)/%.txt
	cp -f $(ARPIGI)/code/$< $(ARPIGI)/code/$@

cleanscenes :
	rm -f $(BINSCENES)

#---------------------------------------------------------------------------------
FONTFILES 	:= $(wildcard $(FONTS)/*.png)
BINFONTS  	:= $(addprefix $(GAMEDATA)/, $(notdir $(FONTFILES:.png=.bin)))

fonts : $(BINFONTS)

$(GAMEDATA)/%.bin : $(FONTS)/%.png
	$(ARPIGI)/tools/Anything2Bin/bin/Debug/Anything2Bin.exe $(ARPIGI)/code/$< $(ARPIGI)/code/$@ -tileset

cleanfonts :
	rm -f $(BINFONTS)
	
#---------------------------------------------------------------------------------
clean:
	$(MAKE) -C arm9 clean
	$(MAKE) -C arm7 clean
	rm -f $(TARGET).nds $(TARGET).arm7 $(TARGET).arm9

#---------------------------------------------------------------------------------
rebuild: clean all

#---------------------------------------------------------------------------------	
run: all
	$(ARPIGI)/tools/DeSmuME/DeSmuME.exe $(TARGET).nds