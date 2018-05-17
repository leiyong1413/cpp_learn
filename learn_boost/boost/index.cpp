#include "index.h"

#include "timer\timer.h"
#include "progress\progress.h"
#include "date_time\date_time.h"

#include "memory\smart_ptr\smart_ptr.h"

namespace learn_boost {

	IRunUseCase* UseCaseSimpleFactory::Create(const UseCaseIndex &index) {
		IRunUseCase * use_case = 0;

		switch (index)
		{
		case learn_boost::NONE:
			break;
		case learn_boost::TIMER:
			use_case = new learn_boost::Timer();
			break;
		case learn_boost::PROGRESS:
			use_case = new learn_boost::ProgressTimer();
			break;
		case learn_boost::DATE_TIME_GREGORIAN:
			use_case = new learn_boost::DateTimeGregorian();
			break;
		case learn_boost::DATE_TIME_POSIX_TIME:
			use_case = new learn_boost::DateTimePosixtime();
			break;
		case learn_boost::MEMORY_SMART_PTR:
			use_case = new learn_boost::SmartPtr();
			break;
		case learn_boost::COUNT:
			break;
		default:
			break;
		}

		return use_case;
	}
}