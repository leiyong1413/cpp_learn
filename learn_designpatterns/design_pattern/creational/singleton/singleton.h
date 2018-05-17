#ifndef LEARN_DESIGN_PATTERN_CREATIONAL_SINGLETON_SINGLETON_H__
#define LEARN_DESIGN_PATTERN_CREATIONAL_SINGLETON_SINGLETON_H__

#include <iostream>
#include <mutex>

namespace learn {
	namespace design_pattern {
		namespace creational {

			// ����ʵ�֣�����˼�壬�����򲻵��ѾͲ���ȥʵ�����࣬Ҳ����˵�ڵ�һ���õ���ʵ����ʱ��Ż�ȥʵ����
			// ���̰߳�ȫ,�����߳�ͬʱ�״ε���Instance������ͬʱ��⵽p��NULLֵ���������̻߳�ͬʱ����һ��ʵ����p
			class Singleton {
			public:
				// ��ͨ����������
				// ��д���ʿ�ͷ
				static Singleton* Instance();

				// �洢����������ȡ��ͬ�������� �棺������set_varname
				// ��С�Ĵ�ȡ������������
				int num_student() const {
					return num_student_;
				}
				
				void set_num_student(const int num_student) {
					num_student_ = num_student;
				}

				int age() const {
					return age_;
				}

				void set_age(const int age) {
					age_ = age;
				}
			protected:
				// singleton ������ʵ�л������캯������Ϊprotected �� private
				Singleton();
			private:
				// �����������ȫСд��������ĵ��ʺ��»���
				// ���Ա�����»��߽�β
				static Singleton* instance_;

				int num_student_;
				int age_;
			};

			// ����ʵ�֣����˿϶�Ҫ������ʳ�������ڵ����ඨ���ʱ��ͽ���ʵ����
			// �̰߳�ȫ
			class SingletonReference {
			public:
				// ʹ������
				static SingletonReference& Instance() {
					static SingletonReference instance;
					return instance;
				}
			private:
				// C++11��׼������һ�������ԣ�defaulted������
				// ֻ���ں�����������ϡ�=default;�����Ϳɽ��ú�������Ϊdefaulted��������������Ϊ��ʽ������defaulted�����Զ����ɺ�����
				// defaulted�������Խ���������������Ա�������Ҹ������Ա����û��Ĭ�ϲ���
				SingletonReference() = default;
				~SingletonReference() = default;

				// c++11��׼���������ԣ���ȷ�����Ȼ������ĳ�����������ֽ�ֹ���Ǳ�ʹ�õ���˼
				// ��ֹ���ɸú�������������
				SingletonReference(const SingletonReference&) = delete;
				// ��ֹ���ɸú�������ֵ�����
				SingletonReference& operator=(const SingletonReference&) = delete;
			};

			// ��ͨ�������Ͷ�����ʽ���Ƚϣ�
			// ������Ҫ�����߳�ͬ���������ڷ������Ƚϴ󣬻��߿��ܷ��ʵ��̱߳Ƚ϶�ʱ�����ö���ʵ�֣�����ʵ�ָ��õ�����(�ռ任ʱ��)
			// ��Ϊ��̬ʵ����ʼ���ڳ���ʼʱ����������֮ǰ�������߳��Ե��̷߳�ʽ����˳�ʼ���������̰߳�ȫ
			// �������ڷ�������Сʱ����������ʵ�֡�������ʱ�任�ռ�

			// �̰߳�ȫ��ʵ��
			// 1.����
			class SingletonWithLock{
			public:
				static SingletonWithLock* Instance();
			protected:
				SingletonWithLock();
			private:
				// ע�� �ྲ̬��Ա���������������ʼ��
				// ���Ա�����cpp�г�ʼ��
				static SingletonWithLock* instance_;
			};

		} // namespace creational
	} // namespace design_pattern
} // namespace learn

#endif // LEARN_DESIGN_PATTERN_CREATIONAL_SINGLETON_SINGLETON_H__