#ifndef LEARN_DESIGN_PATTERN_CREATIONAL_SIMPLE_FACTORY_SIMPLE_FACTORY_H__
#define LEARN_DESIGN_PATTERN_CREATIONAL_SIMPLE_FACTORY_SIMPLE_FACTORY_H__

#include <iostream>
#include <mutex>

namespace learn {
	namespace design_pattern {
		namespace creational {
			/**
			* 1.�򵥹��� ��̬����ģʽ
			*	����һ�������࣬���������������ʵ�У�����������ô�������Ķ��û���˵�ǲ��ɼ���
 			*/

			// ʵ��һ������� �� �� �� �� ����
			// ����
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

				//���
				virtual double Result() const { return 0; }
			private:
				double num1_;
				double num2_;
			};

			class Add : public Operation{
			public:
				// c++11 �����ԣ�override �ؼ��֣����Ա�����������������д�麯��
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