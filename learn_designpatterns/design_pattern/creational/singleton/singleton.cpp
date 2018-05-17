#include "singleton.h"

namespace learn {
	namespace design_pattern {
		namespace creational {

			Singleton* Singleton::instance_ = NULL;

			Singleton::Singleton():num_student_(0),age_(0){
				std::cout << "Singleton constructor" << std::endl;
			}

			Singleton* Singleton::Instance() {
				if (NULL == instance_) {
					instance_ = new Singleton();
				}
				return instance_;
			}

			SingletonWithLock* SingletonWithLock::instance_ = NULL;
			SingletonWithLock::SingletonWithLock(){
				std::cout << "SingletonWithLock constructor" << std::endl;
			}

			SingletonWithLock* SingletonWithLock::Instance() {
				// ������
				static std::mutex instance_mutex_;
				if (NULL == instance_) {
					// 1.lock_guard���� non-copyable��
					// 2.lock_guard ����һ��mutex��װ�ߣ���Ϊ��ӵ��һ������mutex���ṩ��һ�ַ���� RAII style ����
					std::lock_guard<std::mutex> lock(instance_mutex_);
					if (NULL == instance_) {
						instance_ = new SingletonWithLock();
					}
				}
				return instance_;
			}

		} // namespace creational
	} // namespace design_pattern
} // namespace learn
