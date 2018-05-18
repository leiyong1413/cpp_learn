#ifndef LEARN_DESIGN_PATTERN_CREATIONAL_SINGLETON_SINGLETONUSECASE_H__
#define LEARN_DESIGN_PATTERN_CREATIONAL_SINGLETON_SINGLETONUSECASE_H__

#include "../../use_case.h"

namespace learn_design_pattern {

	class ImpUseCaseSingleton : public AbstractUseCase {
	public:
		ImpUseCaseSingleton() = default;
		~ImpUseCaseSingleton() = default;
		virtual std::string Description() const override;
		virtual void Run() override;
	};
} // namespace learn_design_pattern

#endif // 