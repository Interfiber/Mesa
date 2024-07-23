#pragma once
#include "MesaScriptlet.h"

namespace Mesa {
	class ProjectScriptlet : public Scriptlet {
	public:
		ProjectScriptlet();

		void onRun(std::shared_ptr<Workspace> workspace, const std::string& value) override;
	};

	class IncludeScriptlet : public Scriptlet {
	public:
		IncludeScriptlet();

		void onRun(std::shared_ptr<Workspace> workspace, const std::string& value) override;
	};

	class CompilerDefineScriptlet : public Scriptlet {
	public:
		CompilerDefineScriptlet();

		void onRun(std::shared_ptr<Workspace> workspace, const std::string& value) override;
	};

	class FileScriptlet : public Scriptlet {
	public:
		FileScriptlet();

		void onRun(std::shared_ptr<Workspace> workspace, const std::string& value) override;
	};

	class ConfigScriptlet : public Scriptlet {
	public:
		ConfigScriptlet();

		void onRun(std::shared_ptr<Workspace> workspace, const std::string& value) override;
	};

	class PackageScriptlet : public Scriptlet {
	public:
		PackageScriptlet();

		void onRun(std::shared_ptr<Workspace> workspace, const std::string& value) override;
	};
}