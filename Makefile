# This Makefile was generated by Mesa v2.1
# Generation Date: 1722475277
# DO NOT EDIT THIS FILE AS IT WILL BE RE-GENERATED

################### VARIABLES ###################

COLOR_RED := $(shell echo -e "\033[31m")
COLOR_GREEN := $(shell echo -e "\033[33m")
COLOR_BLUE := $(shell echo -e "\033[34m")
COLOR_CYAN := $(shell echo -e "\033[36m")
COLOR_NORM := $(shell echo -e "\033[0\;39m")

STYLE_ITALIC := $(shell echo -e "\033[3m")
STYLE_ULINE := $(shell echo -e "\033[4m")
STYLE_NORM := $(shell echo -e "\033[0m")
CXX := /usr/bin/clang++
I_CPPFLAGS := -DMESA_BUILD
BIN_DIR := bin
OBJ_DIR := $(BIN_DIR)/objs
Utils_INCDIRS := 
Utils_CPPFLAGS :=  -O3 -std=c++17
Utils_LDFLAGS := -L$(BIN_DIR)
Utils_STATIC_LIBS := 
Scriptlets_INCDIRS := 
Scriptlets_CPPFLAGS :=  -O3 -std=c++17
Scriptlets_LDFLAGS := -L$(BIN_DIR)
Scriptlets_STATIC_LIBS := $(BIN_DIR)/MesaUtils.a 
Mesa_Base_INCDIRS := $(wildcard ./*.h) $(wildcard ./*.hpp)$(wildcard Libraries/Include/*.h) $(wildcard Libraries/Include/*.hpp)
Mesa_Base_CPPFLAGS := -DBUILD_DATE=Wed\ Jul\ 31\ 21:21:17\ 2024 -DBUILD_UNIX=1722475277 -I. -ILibraries/Include  -O3 -std=c++17
Mesa_Base_LDFLAGS := -L$(BIN_DIR)
Mesa_Base_STATIC_LIBS := $(BIN_DIR)/MesaScriptlets.a $(BIN_DIR)/MesaUtils.a 

################### PROJECTS ###################

all: Utils Scriptlets Mesa_Base 

clean:
	@echo $(COLOR_BLUE)[RM]$(COLOR_NORM) Purging contents of $(STYLE_ULINE)$(BIN_DIR)$(STYLE_NORM)
	@rm -rf $(BIN_DIR)/*

Prep:
	@echo $(COLOR_BLUE)[MKDIR]$(COLOR_NORM) Creating $(STYLE_ULINE)$(OBJ_DIR)$(STYLE_NORM)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/Utils
	@mkdir -p $(OBJ_DIR)/Scriptlets
	@mkdir -p $(OBJ_DIR)/Mesa_Base

projects:
	@echo "### Project List ###"
	@echo "	* [LIB] 'Utils' > $(BIN_DIR)/MesaUtils"
	@echo "	* [LIB] 'Scriptlets' > $(BIN_DIR)/MesaScriptlets"
	@echo "		* Requires: $(STYLE_ITALIC)'Utils'$(STYLE_NORM)"
	@echo "	* [EXE] 'Mesa Base' > $(BIN_DIR)/Mesa"
	@echo "		* Requires: $(STYLE_ITALIC)'Scriptlets'$(STYLE_NORM)"
	@echo "		* Requires: $(STYLE_ITALIC)'Utils'$(STYLE_NORM)"

$(OBJ_DIR)/Utils/MesaUtils.cpp.o: MesaUtils.cpp $(Utils_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) MesaUtils.cpp
	@$(CXX) $(CPPFLAGS) $(Utils_CPPFLAGS) $(I_CPPFLAGS) -c MesaUtils.cpp -o $(OBJ_DIR)/Utils/MesaUtils.cpp.o

Utils: Prep $(OBJ_DIR)/Utils/MesaUtils.cpp.o 
	@echo $(COLOR_GREEN)[LIB]$(COLOR_NORM) Linking Utils \> $(STYLE_ULINE)$(BIN_DIR)/MesaUtils.a$(STYLE_NORM)
	@ar rcs $(BIN_DIR)/MesaUtils.a $(OBJ_DIR)/Utils/MesaUtils.cpp.o 
$(OBJ_DIR)/Scriptlets/ProjectScriptlets.cpp.o: ProjectScriptlets.cpp $(Scriptlets_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) ProjectScriptlets.cpp
	@$(CXX) $(CPPFLAGS) $(Scriptlets_CPPFLAGS) $(I_CPPFLAGS) -c ProjectScriptlets.cpp -o $(OBJ_DIR)/Scriptlets/ProjectScriptlets.cpp.o

$(OBJ_DIR)/Scriptlets/StdScriptlets.cpp.o: StdScriptlets.cpp $(Scriptlets_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) StdScriptlets.cpp
	@$(CXX) $(CPPFLAGS) $(Scriptlets_CPPFLAGS) $(I_CPPFLAGS) -c StdScriptlets.cpp -o $(OBJ_DIR)/Scriptlets/StdScriptlets.cpp.o

$(OBJ_DIR)/Scriptlets/WorkspaceScriptlets.cpp.o: WorkspaceScriptlets.cpp $(Scriptlets_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) WorkspaceScriptlets.cpp
	@$(CXX) $(CPPFLAGS) $(Scriptlets_CPPFLAGS) $(I_CPPFLAGS) -c WorkspaceScriptlets.cpp -o $(OBJ_DIR)/Scriptlets/WorkspaceScriptlets.cpp.o

Scriptlets: Prep $(OBJ_DIR)/Scriptlets/ProjectScriptlets.cpp.o $(OBJ_DIR)/Scriptlets/StdScriptlets.cpp.o $(OBJ_DIR)/Scriptlets/WorkspaceScriptlets.cpp.o 
	@echo $(COLOR_GREEN)[LIB]$(COLOR_NORM) Linking Scriptlets \> $(STYLE_ULINE)$(BIN_DIR)/MesaScriptlets.a$(STYLE_NORM)
	@ar rcs $(BIN_DIR)/MesaScriptlets.a $(OBJ_DIR)/Scriptlets/ProjectScriptlets.cpp.o $(OBJ_DIR)/Scriptlets/StdScriptlets.cpp.o $(OBJ_DIR)/Scriptlets/WorkspaceScriptlets.cpp.o 
$(OBJ_DIR)/Mesa_Base/Mesa.cpp.o: Mesa.cpp $(Mesa_Base_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) Mesa.cpp
	@$(CXX) $(CPPFLAGS) $(Mesa_Base_CPPFLAGS) $(I_CPPFLAGS) -c Mesa.cpp -o $(OBJ_DIR)/Mesa_Base/Mesa.cpp.o

$(OBJ_DIR)/Mesa_Base/MesaParser.cpp.o: MesaParser.cpp $(Mesa_Base_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) MesaParser.cpp
	@$(CXX) $(CPPFLAGS) $(Mesa_Base_CPPFLAGS) $(I_CPPFLAGS) -c MesaParser.cpp -o $(OBJ_DIR)/Mesa_Base/MesaParser.cpp.o

$(OBJ_DIR)/Mesa_Base/MesaGenerator.cpp.o: MesaGenerator.cpp $(Mesa_Base_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) MesaGenerator.cpp
	@$(CXX) $(CPPFLAGS) $(Mesa_Base_CPPFLAGS) $(I_CPPFLAGS) -c MesaGenerator.cpp -o $(OBJ_DIR)/Mesa_Base/MesaGenerator.cpp.o

$(OBJ_DIR)/Mesa_Base/MesaProcessor.cpp.o: MesaProcessor.cpp $(Mesa_Base_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) MesaProcessor.cpp
	@$(CXX) $(CPPFLAGS) $(Mesa_Base_CPPFLAGS) $(I_CPPFLAGS) -c MesaProcessor.cpp -o $(OBJ_DIR)/Mesa_Base/MesaProcessor.cpp.o

Mesa_Base: Prep $(OBJ_DIR)/Mesa_Base/Mesa.cpp.o $(OBJ_DIR)/Mesa_Base/MesaParser.cpp.o $(OBJ_DIR)/Mesa_Base/MesaGenerator.cpp.o $(OBJ_DIR)/Mesa_Base/MesaProcessor.cpp.o 
	@echo $(COLOR_GREEN)[EXE]$(COLOR_NORM) Linking Mesa Base \> $(STYLE_ULINE)$(BIN_DIR)/Mesa$(STYLE_NORM)
	@$(CXX) -o $(BIN_DIR)/Mesa $(OBJ_DIR)/Mesa_Base/Mesa.cpp.o $(OBJ_DIR)/Mesa_Base/MesaParser.cpp.o $(OBJ_DIR)/Mesa_Base/MesaGenerator.cpp.o $(OBJ_DIR)/Mesa_Base/MesaProcessor.cpp.o  $(Mesa_Base_LDFLAGS) $(Mesa_Base_STATIC_LIBS)


task\:run:
	@echo "[TASK] Running task 'run'"
	@$(shell ./build/FusionRuntime/fusionEngineRuntime -game projects/FusionSandbox -fpslimit 120 -developer)

tasks:
	@echo "### Task List: ###"
	@echo "	* run"

.PHONY: clean run 
