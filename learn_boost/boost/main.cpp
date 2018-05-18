#include <iostream>

#include "index.h"

int main() {

	std::cout << "learn boost" << std::endl;
	
	learn_boost::UseCaseIndex index = learn_boost::UseCaseIndex::kMemorySmartPtr;
	learn_boost::IRunUseCase *use_case = learn_boost::UseCaseSimpleFactory::Create(index);
	if (use_case) {
		use_case->Run();
	}
	else {
		std::cout << "learn boost usecase index error" << std::endl;
	}

	int wait_char = std::getchar();

	return 0;
}