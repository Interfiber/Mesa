project(Mesa)

include_directories(.)

add_executable(Mesa Mesa.cpp MesaMakefileGenerator.cpp MesaParser.cpp MesaProcessor.cpp MesaUtils.cpp ProjectScriptlets.cpp StdScriptlets.cpp WorkspaceScriptlets.cpp)