#include "MesaGenerator.h"
#include "MesaParser.h"
#include "MesaProcessor.h"
#include <fstream>
#include <string>
#include <vector>


#define STRING(x) #x
#define RSTRING(x) STRING(x)

void showHelp() {
  printf("Mesa v2.1, IBAtechSoftware Build System\n"); // TODO
  printf("Author: Interfiber <webmaster@interfiber.dev>\n");
  printf("Commands:\n");
  printf(" build - Build the current working directory using build.msa\n");
  printf(" iiiii - Airports suck... 7/21/2024\n");
  printf("\nThis program is part of the Fusion game engine, but can be "
         "distributed separately\n");

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
    showHelp();
  }

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