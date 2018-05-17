/**
* 学习boost progress 库
* progress 底层使用boost的timer库,继承timer
* progress_timer 构造函数使用参数，std::ostream & os = std::cout ， 析构时将输出到io流中，默认是std::cout中
* progress_timer 析构时会自动输出时间，用于自动计时
*/
#ifndef LEARN_BOOST_PROGRESS_PROGRESS_TIMER_H__
#define LEARN_BOOST_PROGRESS_PROGRESS_TIMER_H__

#include "../index.h"

// 头文件包含
#include <boost/progress.hpp>
using namespace boost;

namespace learn_boost {
	// 低精度计时器
	class ProgressTimer : public IRunUseCase {
	public:
		virtual std::string Description() const override;
		virtual void Run() override;
	};

} // namespace learn_boost

#endif // LEARN_BOOST_PROGRESS_PROGRESS_TIMER_H__