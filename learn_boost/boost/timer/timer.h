/**
* 学习boost timer库
* timer库使用标准库<ctime>里面的std::clock()函数实现
* 使用场景：适合要求不高的计时任务，不适合高精度时间测量
* 高精度使用cpu_timer 库
*/
#ifndef LEARN_BOOST_TIMER_TIMER_H__
#define LEARN_BOOST_TIMER_TIMER_H__

#include "../index.h"

// 头文件包含
#include <boost/timer.hpp>
using namespace boost;

namespace learn_boost {
	// 低精度计时器
	class Timer : public IRunUseCase {
	public:
		virtual std::string Description() const override;
		virtual void Run() override;
	};

} // namespace learn_boost

#endif // LEARN_BOOST_TIMER_TIMER_H__