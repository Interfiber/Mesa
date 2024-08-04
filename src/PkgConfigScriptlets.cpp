#include "PkgConfigScriptlets.h"
#include "MesaUtils.h"

Mesa::PackagePkgConfigScriptlet::PackagePkgConfigScriptlet() {
	name = "PackagePkgConfig";
	isProjectIsolated = true;
}

void Mesa::PackagePkgConfigScriptlet::onRun(std::shared_ptr<Workspace> workspace,
                   const std::string &value) {
	#if defined(_WIN32)
		LOG("PackagePkgConfig is not supported on Windows!\n");

		std::exit(EXIT_FAILURE);
	#endif

	int found = std::system(("pkg-config " + value).c_str());

	if (found == 1) {
		LOG("Pkg-Config failed to find package: %s\n", value.c_str());

		std::exit(EXIT_FAILURE);
	}

	FILE* cflags = popen(("pkg-config --cflags " + value).c_str(), "r");
	FILE* libs = popen(("pkg-config --libs " + value).c_str(), "r");


	std::shared_ptr<Mesa::Project> project = workspace->projects[workspace->currentProject];


	pclose(cflags);
	pclose(libs);
}