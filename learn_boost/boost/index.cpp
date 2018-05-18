#include "index.h"

#include "timer\timer.h"
#include "progress\progress.h"
#include "date_time\date_time.h"

#include "memory\smart_ptr\smart_ptr.h"

namespace learn_boost {

	IRunUseCase* UseCaseSimpleFactory::Create(const UseCaseIndex &index) {
		IRunUseCase * use_case = 0;

		switch (index) {
		case learn_boost::kNone:
			break;
		case learn_boost::kTimer:
			use_case = new learn_boost::Timer();
			break;
		case learn_boost::kProgress: {
			use_case = new learn_boost::ProgressTimer();
			break;
		}
		case learn_boost::kDateTimeGregorian: {
			use_case = new learn_boost::DateTimeGregorian();
			break;
		}
		case learn_boost::kDateTimePosixTime: {
			use_case = new learn_boost::DateTimePosixtime();
			break;
		}
		case learn_boost::kMemorySmartPtr: {
			use_case = new learn_boost::SmartPtr();
			break;
		}
		case learn_boost::kCount:
			break;
		default:
			break;
		}

		return use_case;
	}
}