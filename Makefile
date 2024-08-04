# This Makefile was generated by Mesa v2.1
# Generation Date: 1722782772
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
Utils_INCDIRS := $(wildcard include/*.h) $(wildcard include/*.hpp)
Utils_CPPFLAGS := -Iinclude  -O3 -g -std=c++17
Utils_LDFLAGS := -L$(BIN_DIR) 
Utils_STATIC_LIBS := 
Utils_DYN_LIBS := 
Scriptlets_INCDIRS := $(wildcard include/*.h) $(wildcard include/*.hpp)
Scriptlets_CPPFLAGS := -Iinclude  -O3 -g -std=c++17
Scriptlets_LDFLAGS := -L$(BIN_DIR) 
Scriptlets_STATIC_LIBS := $(BIN_DIR)/MesaUtils.a 
Scriptlets_DYN_LIBS := 
Mesa_Base_INCDIRS := $(wildcard include/*.h) $(wildcard include/*.hpp)$(wildcard SDL/include/*.h) $(wildcard SDL/include/*.hpp)
Mesa_Base_CPPFLAGS := -DBUILD_DATE=Sun\ Aug\ \ 4\ 10:46:11\ 2024 -DBUILD_UNIX=1722782771 -Iinclude -ISDL/include  -O3 -g -std=c++17
Mesa_Base_LDFLAGS := -L$(BIN_DIR) 
Mesa_Base_STATIC_LIBS := $(BIN_DIR)/MesaScriptlets.a $(BIN_DIR)/MesaUtils.a 
Mesa_Base_DYN_LIBS := $(BIN_DIR)/libSDL3.so.0.1.2 

################### PROJECTS ###################

all: Utils Scriptlets Mesa_Base 

clean:
	@echo $(COLOR_BLUE)[RM]$(COLOR_NORM) Purging contents of $(STYLE_ULINE)$(BIN_DIR)/objs/$(STYLE_NORM)
	@rm -rf $(BIN_DIR)/objs/*

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

$(OBJ_DIR)/Utils/src_MesaUtils.cpp.o: src/MesaUtils.cpp $(Utils_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) src/MesaUtils.cpp
	@$(CXX) $(CPPFLAGS) $(Utils_CPPFLAGS) $(I_CPPFLAGS) -c src/MesaUtils.cpp -o $(OBJ_DIR)/Utils/src_MesaUtils.cpp.o

Utils: Prep $(OBJ_DIR)/Utils/src_MesaUtils.cpp.o 
	@echo $(COLOR_GREEN)[LIB]$(COLOR_NORM) Linking Utils \> $(STYLE_ULINE)$(BIN_DIR)/MesaUtils.a$(STYLE_NORM)
	@ar rcs $(BIN_DIR)/MesaUtils.a $(OBJ_DIR)/Utils/src_MesaUtils.cpp.o 
$(OBJ_DIR)/Scriptlets/src_ProjectScriptlets.cpp.o: src/ProjectScriptlets.cpp $(Scriptlets_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) src/ProjectScriptlets.cpp
	@$(CXX) $(CPPFLAGS) $(Scriptlets_CPPFLAGS) $(I_CPPFLAGS) -c src/ProjectScriptlets.cpp -o $(OBJ_DIR)/Scriptlets/src_ProjectScriptlets.cpp.o

$(OBJ_DIR)/Scriptlets/src_StdScriptlets.cpp.o: src/StdScriptlets.cpp $(Scriptlets_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) src/StdScriptlets.cpp
	@$(CXX) $(CPPFLAGS) $(Scriptlets_CPPFLAGS) $(I_CPPFLAGS) -c src/StdScriptlets.cpp -o $(OBJ_DIR)/Scriptlets/src_StdScriptlets.cpp.o

$(OBJ_DIR)/Scriptlets/src_WorkspaceScriptlets.cpp.o: src/WorkspaceScriptlets.cpp $(Scriptlets_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) src/WorkspaceScriptlets.cpp
	@$(CXX) $(CPPFLAGS) $(Scriptlets_CPPFLAGS) $(I_CPPFLAGS) -c src/WorkspaceScriptlets.cpp -o $(OBJ_DIR)/Scriptlets/src_WorkspaceScriptlets.cpp.o

$(OBJ_DIR)/Scriptlets/src_CMakeScriptlets.cpp.o: src/CMakeScriptlets.cpp $(Scriptlets_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) src/CMakeScriptlets.cpp
	@$(CXX) $(CPPFLAGS) $(Scriptlets_CPPFLAGS) $(I_CPPFLAGS) -c src/CMakeScriptlets.cpp -o $(OBJ_DIR)/Scriptlets/src_CMakeScriptlets.cpp.o

Scriptlets: Prep $(OBJ_DIR)/Scriptlets/src_ProjectScriptlets.cpp.o $(OBJ_DIR)/Scriptlets/src_StdScriptlets.cpp.o $(OBJ_DIR)/Scriptlets/src_WorkspaceScriptlets.cpp.o $(OBJ_DIR)/Scriptlets/src_CMakeScriptlets.cpp.o 
	@echo $(COLOR_GREEN)[LIB]$(COLOR_NORM) Linking Scriptlets \> $(STYLE_ULINE)$(BIN_DIR)/MesaScriptlets.a$(STYLE_NORM)
	@ar rcs $(BIN_DIR)/MesaScriptlets.a $(OBJ_DIR)/Scriptlets/src_ProjectScriptlets.cpp.o $(OBJ_DIR)/Scriptlets/src_StdScriptlets.cpp.o $(OBJ_DIR)/Scriptlets/src_WorkspaceScriptlets.cpp.o $(OBJ_DIR)/Scriptlets/src_CMakeScriptlets.cpp.o 
$(OBJ_DIR)/Mesa_Base/src_Mesa.cpp.o: src/Mesa.cpp $(Mesa_Base_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) src/Mesa.cpp
	@$(CXX) $(CPPFLAGS) $(Mesa_Base_CPPFLAGS) $(I_CPPFLAGS) -c src/Mesa.cpp -o $(OBJ_DIR)/Mesa_Base/src_Mesa.cpp.o

$(OBJ_DIR)/Mesa_Base/src_MesaParser.cpp.o: src/MesaParser.cpp $(Mesa_Base_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) src/MesaParser.cpp
	@$(CXX) $(CPPFLAGS) $(Mesa_Base_CPPFLAGS) $(I_CPPFLAGS) -c src/MesaParser.cpp -o $(OBJ_DIR)/Mesa_Base/src_MesaParser.cpp.o

$(OBJ_DIR)/Mesa_Base/src_MesaMakefileGenerator.cpp.o: src/MesaMakefileGenerator.cpp $(Mesa_Base_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) src/MesaMakefileGenerator.cpp
	@$(CXX) $(CPPFLAGS) $(Mesa_Base_CPPFLAGS) $(I_CPPFLAGS) -c src/MesaMakefileGenerator.cpp -o $(OBJ_DIR)/Mesa_Base/src_MesaMakefileGenerator.cpp.o

$(OBJ_DIR)/Mesa_Base/src_MesaProcessor.cpp.o: src/MesaProcessor.cpp $(Mesa_Base_INCDIRS)
	@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) src/MesaProcessor.cpp
	@$(CXX) $(CPPFLAGS) $(Mesa_Base_CPPFLAGS) $(I_CPPFLAGS) -c src/MesaProcessor.cpp -o $(OBJ_DIR)/Mesa_Base/src_MesaProcessor.cpp.o

Mesa_Base: Prep $(OBJ_DIR)/Mesa_Base/src_Mesa.cpp.o $(OBJ_DIR)/Mesa_Base/src_MesaParser.cpp.o $(OBJ_DIR)/Mesa_Base/src_MesaMakefileGenerator.cpp.o $(OBJ_DIR)/Mesa_Base/src_MesaProcessor.cpp.o 
	@echo $(COLOR_GREEN)[EXE]$(COLOR_NORM) Linking Mesa Base \> $(STYLE_ULINE)$(BIN_DIR)/Mesa$(STYLE_NORM)
	@$(CXX) -o $(BIN_DIR)/Mesa $(OBJ_DIR)/Mesa_Base/src_Mesa.cpp.o $(OBJ_DIR)/Mesa_Base/src_MesaParser.cpp.o $(OBJ_DIR)/Mesa_Base/src_MesaMakefileGenerator.cpp.o $(OBJ_DIR)/Mesa_Base/src_MesaProcessor.cpp.o  $(Mesa_Base_LDFLAGS) $(Mesa_Base_STATIC_LIBS) -Wl,-rpath $(BIN_DIR) $(Mesa_Base_DYN_LIBS)


tasks:
	@echo "### Task List: ###"

.ONESHELL:
compdb:
	make --always-make --dry-run \
	| grep -wE 'clang|clang\+\+' \
	| grep -w '\-c' \
	| jq -nR '[inputs|{directory:".", command:., file: match(" [^ ]+$$").string[1:]}]' > compile_commands.json
.PHONY: clean compdb 
