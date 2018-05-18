#ifndef LEARNDESIGNPATTERN_USECASE_H__
#define LEARNDESIGNPATTERN_USECASE_H__

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
using namespace boost;

namespace learn_design_pattern {

	// 用列
	enum UseCaseIndex{
		kNone = -1,

		kUseCaseCreationalSingleton,

		kCount
	};

	// 用列抽象
	class AbstractUseCase {
	public:
		virtual std::string Description() const = 0;
		virtual void Run() = 0;
	protected:
		// c++ 11 default
		// 保护析构 使用智能指针管理
		virtual ~AbstractUseCase() = default;
	};

	// 简单工厂的实现
	class SimpleFactory {
	public:
		// 使用shared_ptr 创建简单工厂
		static boost::shared_ptr<AbstractUseCase> Create(const UseCaseIndex& index);
	};


} // namespace learn_design_pattern

#endif // LEARNDESIGNPATTERN_USECASE_H__