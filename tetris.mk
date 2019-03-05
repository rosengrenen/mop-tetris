##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=tetris
ConfigurationName      :=Debug
WorkspacePath          :=C:/dev/projects/codelite/chalmers
ProjectPath            :=C:/dev/projects/codelite/chalmers/mop-tetris
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=rasmus
Date                   :=04/03/2019
CodeLitePath           :=C:/cseapp/CodeLite
LinkerName             :=C:/cseapp/CodeLite/tools/gcc-arm/bin/arm-none-eabi-g++.exe
SharedObjectLinkerName :=C:/cseapp/CodeLite/tools/gcc-arm/arm-none-eabi-g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName).elf
Preprocessors          :=$(PreprocessorSwitch)SIMULATOR 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="tetris.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=
LinkOptions            :=  -T$(ProjectPath)/md407-ram.x -L$(ARM_V6LIB) -L$(ARM_GCC_V6LIB) -nostdlib
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)gcc $(LibrarySwitch)c_nano 
ArLibs                 :=  "gcc" "c_nano" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/cseapp/CodeLite/tools/gcc-arm/bin/arm-none-eabi-ar.exe rcu
CXX      := C:/cseapp/CodeLite/tools/gcc-arm/bin/arm-none-eabi-g++.exe
CC       := C:/cseapp/CodeLite/tools/gcc-arm/bin/arm-none-eabi-gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -mthumb -Wall -march=armv6-m -msoft-float -Wa,-adhln=test.s $(Preprocessors)
ASFLAGS  := 
AS       := C:/cseapp/CodeLite/tools/gcc-arm/bin/arm-none-eabi-as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\cseapp\CodeLite
ARM_V6LIB:=$(GccArmDir)/arm-none-eabi/lib/thumb/v6-m
ARM_GCC_V6LIB:=$(GccArmDir)/lib/gcc/arm-none-eabi/7.2.1/thumb/v6-m
ARM_M4FPLIB:=$(GccArmDir)/arm-none-eabi/lib/thumb/v7e-m/fpv4-sp/hard
ARM_GCC_M4FPLIB:=$(GccArmDir)/lib/gcc/arm-none-eabi/7.2.1/thumb/v7e-m
Objects0=$(IntermediateDirectory)/random.c$(ObjectSuffix) $(IntermediateDirectory)/tetris.c$(ObjectSuffix) $(IntermediateDirectory)/field.c$(ObjectSuffix) $(IntermediateDirectory)/keyboard.c$(ObjectSuffix) $(IntermediateDirectory)/tile.c$(ObjectSuffix) $(IntermediateDirectory)/startup.c$(ObjectSuffix) $(IntermediateDirectory)/delay.c$(ObjectSuffix) $(IntermediateDirectory)/shape.c$(ObjectSuffix) $(IntermediateDirectory)/graphics.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	arm-none-eabi-objcopy -S -O srec  ./Debug/tetris.elf ./Debug/tetris.s19
	arm-none-eabi-objdump -D -S ./Debug/tetris.elf > ./Debug/tetris.dass
	@echo Done

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/random.c$(ObjectSuffix): random.c $(IntermediateDirectory)/random.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/dev/projects/codelite/chalmers/mop-tetris/random.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/random.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/random.c$(DependSuffix): random.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/random.c$(ObjectSuffix) -MF$(IntermediateDirectory)/random.c$(DependSuffix) -MM random.c

$(IntermediateDirectory)/random.c$(PreprocessSuffix): random.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/random.c$(PreprocessSuffix) random.c

$(IntermediateDirectory)/tetris.c$(ObjectSuffix): tetris.c $(IntermediateDirectory)/tetris.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/dev/projects/codelite/chalmers/mop-tetris/tetris.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tetris.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tetris.c$(DependSuffix): tetris.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tetris.c$(ObjectSuffix) -MF$(IntermediateDirectory)/tetris.c$(DependSuffix) -MM tetris.c

$(IntermediateDirectory)/tetris.c$(PreprocessSuffix): tetris.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tetris.c$(PreprocessSuffix) tetris.c

$(IntermediateDirectory)/field.c$(ObjectSuffix): field.c $(IntermediateDirectory)/field.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/dev/projects/codelite/chalmers/mop-tetris/field.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/field.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/field.c$(DependSuffix): field.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/field.c$(ObjectSuffix) -MF$(IntermediateDirectory)/field.c$(DependSuffix) -MM field.c

$(IntermediateDirectory)/field.c$(PreprocessSuffix): field.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/field.c$(PreprocessSuffix) field.c

$(IntermediateDirectory)/keyboard.c$(ObjectSuffix): keyboard.c $(IntermediateDirectory)/keyboard.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/dev/projects/codelite/chalmers/mop-tetris/keyboard.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/keyboard.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/keyboard.c$(DependSuffix): keyboard.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/keyboard.c$(ObjectSuffix) -MF$(IntermediateDirectory)/keyboard.c$(DependSuffix) -MM keyboard.c

$(IntermediateDirectory)/keyboard.c$(PreprocessSuffix): keyboard.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/keyboard.c$(PreprocessSuffix) keyboard.c

$(IntermediateDirectory)/tile.c$(ObjectSuffix): tile.c $(IntermediateDirectory)/tile.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/dev/projects/codelite/chalmers/mop-tetris/tile.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tile.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tile.c$(DependSuffix): tile.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tile.c$(ObjectSuffix) -MF$(IntermediateDirectory)/tile.c$(DependSuffix) -MM tile.c

$(IntermediateDirectory)/tile.c$(PreprocessSuffix): tile.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tile.c$(PreprocessSuffix) tile.c

$(IntermediateDirectory)/startup.c$(ObjectSuffix): startup.c $(IntermediateDirectory)/startup.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/dev/projects/codelite/chalmers/mop-tetris/startup.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/startup.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/startup.c$(DependSuffix): startup.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/startup.c$(ObjectSuffix) -MF$(IntermediateDirectory)/startup.c$(DependSuffix) -MM startup.c

$(IntermediateDirectory)/startup.c$(PreprocessSuffix): startup.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/startup.c$(PreprocessSuffix) startup.c

$(IntermediateDirectory)/delay.c$(ObjectSuffix): delay.c $(IntermediateDirectory)/delay.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/dev/projects/codelite/chalmers/mop-tetris/delay.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/delay.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/delay.c$(DependSuffix): delay.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/delay.c$(ObjectSuffix) -MF$(IntermediateDirectory)/delay.c$(DependSuffix) -MM delay.c

$(IntermediateDirectory)/delay.c$(PreprocessSuffix): delay.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/delay.c$(PreprocessSuffix) delay.c

$(IntermediateDirectory)/shape.c$(ObjectSuffix): shape.c $(IntermediateDirectory)/shape.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/dev/projects/codelite/chalmers/mop-tetris/shape.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/shape.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shape.c$(DependSuffix): shape.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shape.c$(ObjectSuffix) -MF$(IntermediateDirectory)/shape.c$(DependSuffix) -MM shape.c

$(IntermediateDirectory)/shape.c$(PreprocessSuffix): shape.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shape.c$(PreprocessSuffix) shape.c

$(IntermediateDirectory)/graphics.c$(ObjectSuffix): graphics.c $(IntermediateDirectory)/graphics.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/dev/projects/codelite/chalmers/mop-tetris/graphics.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/graphics.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/graphics.c$(DependSuffix): graphics.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/graphics.c$(ObjectSuffix) -MF$(IntermediateDirectory)/graphics.c$(DependSuffix) -MM graphics.c

$(IntermediateDirectory)/graphics.c$(PreprocessSuffix): graphics.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/graphics.c$(PreprocessSuffix) graphics.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


