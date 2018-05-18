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
		kNone = -1,

		kTimer,			// 简单计时器 timer
		kProgress,		// 自动计时器 progress_timer
		kDateTimeGregorian,	// DATE TIME 日期处理组件 gregorian
		kDateTimePosixTime,	// DATE TIME 时间处理组件 posix
		kMemorySmartPtr,		// SMART PTR 智能指针 smart_ptr
		kCount
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