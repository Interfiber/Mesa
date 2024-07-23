#pragma once
#include <string>
#include <memory>
#include "Mesa.h"

namespace Mesa {
	class Scriptlet {
	public:
		Scriptlet() = default;

		std::string name;
		bool isProjectIsolated = false;

		virtual void onRun(std::shared_ptr<Workspace> workspace, const std::string &scriptValue) = 0;
	};
};