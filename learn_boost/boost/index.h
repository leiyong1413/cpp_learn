#ifndef LEARN_BOOST_INDEX_H__
#define LEARN_BOOST_INDEX_H__

#include <string>

namespace learn_boost {

	// GOOGLE枚举命名规则：
	// 枚举值应全部大写，单词间以下划线相连：MY_EXCITING_ENUM_VALUE
	// 枚举名称属于类型，因此大小写混合：UrlTableErrors

	// 用列索引
	enum UseCaseIndex
	{
		NONE = -1,

		TIMER,			// 简单计时器 timer
		PROGRESS,		// 自动计时器 progress_timer
		DATE_TIME_GREGORIAN,	// DATE TIME 日期处理组件 gregorian
		DATE_TIME_POSIX_TIME,	// DATE TIME 时间处理组件 posix
		MEMORY_SMART_PTR,		// SMART PTR 智能指针 smart_ptr
		COUNT
	};

	class IRunUseCase {
	public:
		virtual std::string Description() const = 0;
		// 运行用列
		virtual void Run() = 0;
	};

	// 用列简单工厂
	class UseCaseSimpleFactory {
	public:
		static IRunUseCase* Create(const UseCaseIndex &index);
	};
} // namespace learn_boost
#endif // LEARN_BOOST_INDEX_H__