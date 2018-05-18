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
		kNone = -1,

		kTimer,			// �򵥼�ʱ�� timer
		kProgress,		// �Զ���ʱ�� progress_timer
		kDateTimeGregorian,	// DATE TIME ���ڴ������ gregorian
		kDateTimePosixTime,	// DATE TIME ʱ�䴦����� posix
		kMemorySmartPtr,		// SMART PTR ����ָ�� smart_ptr
		kCount
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