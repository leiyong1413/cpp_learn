/**
* 1. 日期时间库 date_time
* 2. 处理日期组件 gregorian (格里高利日历，也就是日常使用的公历)
* 3. 处理时间组件 posix_time （posix可移植操作系统接口）
*/
#ifndef LEARN_BOOST_DATE_TIME_DATE_TIME_H__
#define LEARN_BOOST_DATE_TIME_DATE_TIME_H__

#include "../index.h"

// 头文件包含
// 处理日期
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;

// 处理时间
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

namespace learn_boost {
	// 日期处理
	class DateTimeGregorian : public IRunUseCase {
	public:
		virtual std::string Description() const override;
		virtual void Run() override;
	};

	class DateTimePosixtime : public IRunUseCase {
	public:
		virtual std::string Description() const override;
		virtual void Run() override;
	};

} // namespace learn_boost

#endif // LEARN_BOOST_DATE_TIME_DATE_TIME_H__