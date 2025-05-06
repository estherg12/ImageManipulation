##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=first-assignment
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=C:/LabDDSS/GitHub/PL1
ProjectPath            :=C:/LabDDSS/GitHub/PL1/first-assignment
IntermediateDirectory  :=../build-$(WorkspaceConfiguration)/first-assignment
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Esther
Date                   :=11/12/2024
CodeLitePath           :="C:/Program Files/CodeLite"
MakeDirCommand         :=mkdir
LinkerName             :=C:/msys64/mingw64/bin/g++.exe
SharedObjectLinkerName :=C:/msys64/mingw64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=C:/LabDDSS/GitHub/PL1/build-$(WorkspaceConfiguration)/bin
OutputFile             :=..\build-$(WorkspaceConfiguration)\bin\$(ProjectName).exe
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=C:/msys64/mingw64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := C:/msys64/mingw64/bin/ar.exe -r
CXX      := C:/msys64/mingw64/bin/g++.exe
CC       := C:/msys64/mingw64/bin/gcc.exe
CXXFLAGS :=  -gdwarf-2 -O0 -Wall $(Preprocessors)
CFLAGS   :=  -gdwarf-2 -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/msys64/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/StackOperations.cpp$(ObjectSuffix) $(IntermediateDirectory)/ElementQueue.cpp$(ObjectSuffix) $(IntermediateDirectory)/Pixel.cpp$(ObjectSuffix) $(IntermediateDirectory)/Image.cpp$(ObjectSuffix) $(IntermediateDirectory)/ElementDoubleList.cpp$(ObjectSuffix) $(IntermediateDirectory)/Core.cpp$(ObjectSuffix) $(IntermediateDirectory)/QueuePixel.cpp$(ObjectSuffix) $(IntermediateDirectory)/ElementList.cpp$(ObjectSuffix) $(IntermediateDirectory)/ListPixel.cpp$(ObjectSuffix) $(IntermediateDirectory)/InputOutput.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/DoubleListPixel.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/ElementStack.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"
	@if not exist "$(OutputDirectory)" $(MakeDirCommand) "$(OutputDirectory)"

$(IntermediateDirectory)/.d:
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/StackOperations.cpp$(ObjectSuffix): StackOperations.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/LabDDSS/GitHub/PL1/first-assignment/StackOperations.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StackOperations.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StackOperations.cpp$(PreprocessSuffix): StackOperations.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StackOperations.cpp$(PreprocessSuffix) StackOperations.cpp

$(IntermediateDirectory)/ElementQueue.cpp$(ObjectSuffix): ElementQueue.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/LabDDSS/GitHub/PL1/first-assignment/ElementQueue.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ElementQueue.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ElementQueue.cpp$(PreprocessSuffix): ElementQueue.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ElementQueue.cpp$(PreprocessSuffix) ElementQueue.cpp

$(IntermediateDirectory)/Pixel.cpp$(ObjectSuffix): Pixel.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/LabDDSS/GitHub/PL1/first-assignment/Pixel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Pixel.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Pixel.cpp$(PreprocessSuffix): Pixel.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Pixel.cpp$(PreprocessSuffix) Pixel.cpp

$(IntermediateDirectory)/Image.cpp$(ObjectSuffix): Image.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/LabDDSS/GitHub/PL1/first-assignment/Image.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Image.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Image.cpp$(PreprocessSuffix): Image.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Image.cpp$(PreprocessSuffix) Image.cpp

$(IntermediateDirectory)/ElementDoubleList.cpp$(ObjectSuffix): ElementDoubleList.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/LabDDSS/GitHub/PL1/first-assignment/ElementDoubleList.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ElementDoubleList.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ElementDoubleList.cpp$(PreprocessSuffix): ElementDoubleList.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ElementDoubleList.cpp$(PreprocessSuffix) ElementDoubleList.cpp

$(IntermediateDirectory)/Core.cpp$(ObjectSuffix): Core.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/LabDDSS/GitHub/PL1/first-assignment/Core.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Core.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Core.cpp$(PreprocessSuffix): Core.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Core.cpp$(PreprocessSuffix) Core.cpp

$(IntermediateDirectory)/QueuePixel.cpp$(ObjectSuffix): QueuePixel.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/LabDDSS/GitHub/PL1/first-assignment/QueuePixel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/QueuePixel.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/QueuePixel.cpp$(PreprocessSuffix): QueuePixel.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/QueuePixel.cpp$(PreprocessSuffix) QueuePixel.cpp

$(IntermediateDirectory)/ElementList.cpp$(ObjectSuffix): ElementList.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/LabDDSS/GitHub/PL1/first-assignment/ElementList.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ElementList.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ElementList.cpp$(PreprocessSuffix): ElementList.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ElementList.cpp$(PreprocessSuffix) ElementList.cpp

$(IntermediateDirectory)/ListPixel.cpp$(ObjectSuffix): ListPixel.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/LabDDSS/GitHub/PL1/first-assignment/ListPixel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ListPixel.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ListPixel.cpp$(PreprocessSuffix): ListPixel.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ListPixel.cpp$(PreprocessSuffix) ListPixel.cpp

$(IntermediateDirectory)/InputOutput.cpp$(ObjectSuffix): InputOutput.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/LabDDSS/GitHub/PL1/first-assignment/InputOutput.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/InputOutput.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/InputOutput.cpp$(PreprocessSuffix): InputOutput.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/InputOutput.cpp$(PreprocessSuffix) InputOutput.cpp

$(IntermediateDirectory)/DoubleListPixel.cpp$(ObjectSuffix): DoubleListPixel.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/LabDDSS/GitHub/PL1/first-assignment/DoubleListPixel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DoubleListPixel.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DoubleListPixel.cpp$(PreprocessSuffix): DoubleListPixel.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DoubleListPixel.cpp$(PreprocessSuffix) DoubleListPixel.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/LabDDSS/GitHub/PL1/first-assignment/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/ElementStack.cpp$(ObjectSuffix): ElementStack.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/LabDDSS/GitHub/PL1/first-assignment/ElementStack.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ElementStack.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ElementStack.cpp$(PreprocessSuffix): ElementStack.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ElementStack.cpp$(PreprocessSuffix) ElementStack.cpp

##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


