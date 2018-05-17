#ifndef LEARN_DESIGN_PATTERN_CREATIONAL_SIMPLE_FACTORY_SIMPLE_FACTORY_H__
#define LEARN_DESIGN_PATTERN_CREATIONAL_SIMPLE_FACTORY_SIMPLE_FACTORY_H__

#include <iostream>
#include <mutex>

namespace learn {
	namespace design_pattern {
		namespace creational {
			/**
			* 1.简单工厂 静态工厂模式
			*	创建一个工厂类，用来创建其他类的实列，至于类是怎么样创建的对用户来说是不可见的
 			*/

			// 实现一个计算的 加 减 乘 除 操作
			// 基类
			class Operation{
			public:
				double num1() const {
					return num1_;
				}
				void set_num1(const double num1) {
					num1_ = num1;
				}
				double num2() const {
					return num2_;
				}
				void set_num2(const double num2) {
					num2_ = num2;
				}

				//结果
				virtual double Result() const { return 0; }
			private:
				double num1_;
				double num2_;
			};

			class Add : public Operation{
			public:
				// c++11 新特性：override 关键字，可以避免派生类中忘记重写虚函数
				virtual double Result() const override;
			};

			class Sub : public Operation{
			public:
				virtual double Result() const override;
			};

			class Mul : public Operation {
			public:
				virtual double Result() const override;
			};

			class Div : public Operation{
			public:
				virtual double Result() const override;
			};
		} // namespace creational
	} // namespace design_pattern
} // namespace learn
#endif // LEARN_DESIGN_PATTERN_CREATIONAL_SIMPLE_FACTORY_SIMPLE_FACTORY_H__