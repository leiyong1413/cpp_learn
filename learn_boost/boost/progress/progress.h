/**
* ѧϰboost progress ��
* progress �ײ�ʹ��boost��timer��,�̳�timer
* progress_timer ���캯��ʹ�ò�����std::ostream & os = std::cout �� ����ʱ�������io���У�Ĭ����std::cout��
* progress_timer ����ʱ���Զ����ʱ�䣬�����Զ���ʱ
*/
#ifndef LEARN_BOOST_PROGRESS_PROGRESS_TIMER_H__
#define LEARN_BOOST_PROGRESS_PROGRESS_TIMER_H__

#include "../index.h"

// ͷ�ļ�����
#include <boost/progress.hpp>
using namespace boost;

namespace learn_boost {
	// �;��ȼ�ʱ��
	class ProgressTimer : public IRunUseCase {
	public:
		virtual std::string Description() const override;
		virtual void Run() override;
	};

} // namespace learn_boost

#endif // LEARN_BOOST_PROGRESS_PROGRESS_TIMER_H__