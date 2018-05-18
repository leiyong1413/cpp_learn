#ifndef LEARNDESIGNPATTERN_USECASE_H__
#define LEARNDESIGNPATTERN_USECASE_H__

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
using namespace boost;

namespace learn_design_pattern {

	// ����
	enum UseCaseIndex{
		kNone = -1,

		kUseCaseCreationalSingleton,

		kCount
	};

	// ���г���
	class AbstractUseCase {
	public:
		virtual std::string Description() const = 0;
		virtual void Run() = 0;
	protected:
		// c++ 11 default
		// �������� ʹ������ָ�����
		virtual ~AbstractUseCase() = default;
	};

	// �򵥹�����ʵ��
	class SimpleFactory {
	public:
		// ʹ��shared_ptr �����򵥹���
		static boost::shared_ptr<AbstractUseCase> Create(const UseCaseIndex& index);
	};


} // namespace learn_design_pattern

#endif // LEARNDESIGNPATTERN_USECASE_H__