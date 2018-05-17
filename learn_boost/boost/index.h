#ifndef LEARN_BOOST_INDEX_H__
#define LEARN_BOOST_INDEX_H__

#include <string>

namespace learn_boost {

	// GOOGLEö����������
	// ö��ֵӦȫ����д�����ʼ����»���������MY_EXCITING_ENUM_VALUE
	// ö�������������ͣ���˴�Сд��ϣ�UrlTableErrors

	// ��������
	enum UseCaseIndex
	{
		NONE = -1,

		TIMER,			// �򵥼�ʱ�� timer
		PROGRESS,		// �Զ���ʱ�� progress_timer
		DATE_TIME_GREGORIAN,	// DATE TIME ���ڴ������ gregorian
		DATE_TIME_POSIX_TIME,	// DATE TIME ʱ�䴦����� posix
		MEMORY_SMART_PTR,		// SMART PTR ����ָ�� smart_ptr
		COUNT
	};

	class IRunUseCase {
	public:
		virtual std::string Description() const = 0;
		// ��������
		virtual void Run() = 0;
	};

	// ���м򵥹���
	class UseCaseSimpleFactory {
	public:
		static IRunUseCase* Create(const UseCaseIndex &index);
	};
} // namespace learn_boost
#endif // LEARN_BOOST_INDEX_H__