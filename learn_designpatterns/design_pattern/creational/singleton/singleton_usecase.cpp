#include "singleton_usecase.h"

#include <iostream>

namespace learn_design_pattern {

	std::string ImpUseCaseSingleton::Description() const {
		std::string des = "[usecase][singleton]";
		return des;
	}
	void ImpUseCaseSingleton::Run() {
#pragma region 单列的创建
		std::cout << "run " << Description() << " start " << std::endl;



		std::cout << "run " << Description() << " end " << std::endl;
#pragma endregion

	}
} // namespace learn_design_pattern