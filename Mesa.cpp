#include "MesaGenerator.h"
#include "MesaParser.h"
#include "MesaProcessor.h"
#include <fstream>
#include <string>
#include <vector>


#define STRING(x) #x
#define RSTRING(x) STRING(x)

void Mesa_RunBuild() {
    std::string data;
    std::string line;

    std::ifstream ifs("Build.msa");

    while (std::getline(ifs, line)) {
        data += line + "\n";
    }

    Mesa::Parser parser(data);

    Mesa::Processor processor(parser.parse());
    std::shared_ptr<Mesa::Workspace> workspace = processor.buildWorkspace();

    Mesa::MakefileGenerator gen;

    std::ofstream ofs("Makefile");
    ofs << gen.generate(workspace);

    ofs.close();
}

void Mesa_ShowHelp() {
    printf("Mesa v2.1, C++ build system\n");// TODO
    printf("Author: Interfiber <webmaster@interfiber.dev>\n");
    printf("Commands:\n");
    printf(" build  - Build the current working directory using build.msa\n");
    printf(" compdb - Generate compile_commands.json from the current workspace\n");
    printf("----------------------------------------------------------------------------\n");

#if defined(BUILD_DATE)
    printf("Built on: %s\n", std::string(RSTRING(BUILD_DATE)).c_str());
#endif
}

int main(int argc, char **argv) {
    std::vector<std::string> args;
    args.reserve(argc);

    for (int i = 0; i < argc; i++)
        args.push_back(argv[i]);

    if (args.size() == 1) {
        Mesa_ShowHelp();

        std::exit(EXIT_FAILURE);
    }

    if (args.size() == 2) {
        if (args[1] == "build") {
            Mesa_RunBuild();
        }
    }
}