#include "use_case.h"

#include "creational\singleton\singleton_usecase.h"

namespace learn_design_pattern {
	
	boost::shared_ptr<AbstractUseCase> SimpleFactory::Create(const UseCaseIndex& index) {

		switch (index) {
		case kUseCaseCreationalSingleton:{
			return boost::make_shared<ImpUseCaseSingleton>();
		}
		default:
			break;
		}

		return nullptr;
	}

} // namespace learn_design_pattern