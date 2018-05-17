/**
* ѧϰboost timer��
* timer��ʹ�ñ�׼��<ctime>�����std::clock()����ʵ��
* ʹ�ó������ʺ�Ҫ�󲻸ߵļ�ʱ���񣬲��ʺϸ߾���ʱ�����
* �߾���ʹ��cpu_timer ��
*/
#ifndef LEARN_BOOST_TIMER_TIMER_H__
#define LEARN_BOOST_TIMER_TIMER_H__

#include "../index.h"

// ͷ�ļ�����
#include <boost/timer.hpp>
using namespace boost;

namespace learn_boost {
	// �;��ȼ�ʱ��
	class Timer : public IRunUseCase {
	public:
		virtual std::string Description() const override;
		virtual void Run() override;
	};

} // namespace learn_boost

#endif // LEARN_BOOST_TIMER_TIMER_H__