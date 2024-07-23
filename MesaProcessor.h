#pragma once
#include "MesaParser.h"
#include "MesaScriptlet.h"

namespace Mesa {
	class Processor {
	public:
		Processor(const ParsedFile& file);

		std::shared_ptr<Workspace> buildWorkspace();
		void buildProject(std::shared_ptr<Workspace> workspace);

		template<class T>
		inline void addScriptlet() {
			m_scriptlets.push_back(std::make_shared<T>());
		}

	private:
		ParsedFile m_file;
		std::vector<std::shared_ptr<Scriptlet>> m_scriptlets;
	};
}