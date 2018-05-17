/**
* 1. ����ʱ��� date_time
* 2. ����������� gregorian (�������������Ҳ�����ճ�ʹ�õĹ���)
* 3. ����ʱ����� posix_time ��posix����ֲ����ϵͳ�ӿڣ�
*/
#ifndef LEARN_BOOST_DATE_TIME_DATE_TIME_H__
#define LEARN_BOOST_DATE_TIME_DATE_TIME_H__

#include "../index.h"

// ͷ�ļ�����
// ��������
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;

// ����ʱ��
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

namespace learn_boost {
	// ���ڴ���
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