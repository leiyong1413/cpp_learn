#include <iostream>

#include "use_case.h"

int main() {
	std::cout << "learn design pattern" << std::endl;
	const learn_design_pattern::UseCaseIndex use_case_index = learn_design_pattern::kUseCaseCreationalSingleton;
	auto use_case = learn_design_pattern::SimpleFactory::Create(use_case_index);
	if (use_case) {
		use_case->Run();
	}
	char c_wait = getchar();
	return 0;
}