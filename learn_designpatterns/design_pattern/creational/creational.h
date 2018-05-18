#ifndef LEARNDESIGNPATTERN_CREATIONAL_CREATIONAL_H__
#define LEARNDESIGNPATTERN_CREATIONAL_CREATIONAL_H__

namespace learn_design_pattern {

	// 创建型：管理对象的产生
	// 创建型抽象了类的实例化过程，封装对象的创建动作

	// 抽象工厂：abstract factory
	// 1.对象的创建封装在一个类中，该类的唯一任务就是按需生产各种对象
	// 通过派生子类的方式可以生产不同系列的、整套的对象。
	// 2. 工厂类是单列, 保证系统全局可以访问
	// 3. 工厂类的每个方法是工厂方法。

	// 简单工厂：simple factory 
	// 抽象工厂退化成一个没有子类的简单工厂

	// 工厂方法：factory method
	// 1.把对象的创建封装在一个方法中，子类可以改变工厂方法的生产行为生产不同的对象
	// boost 中的 make_shared() make_optional() make_tuple() 等函数都是工厂方法模式


	// 原型模式：prototype
	// 1.使用类的实列通过拷贝的方式创建对象，具体的拷贝行为可以定制
	// 最常见的方式：实现一个clone()函数
	// boost中的 enable_shared_from_this 类似于一个原型模式，创建一个指向自身的shared_ptr


	// 单列模式： singleton
	// 1. 保证一个类有且仅有一个实列，提供一个全局访问点。
	// boost 在 serialization 库中提供了一个可用的实现

	// 生成器: builder
	// 1. 分解复杂对象的创建过程，创建过程可以被子类改变，使同样的过程可以生产出不同的对象
	// 2. 与工厂模式的不同， 不是一次性的创建出产品， 而是分步骤装配出对象，因此可以对创建过程更精细的控制

} // namespace learn_design_pattern

#endif // LEARNDESIGNPATTERN_CREATIONAL_CREATIONAL_H__