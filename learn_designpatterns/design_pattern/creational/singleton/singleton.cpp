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
				// 互斥量
				static std::mutex instance_mutex_;
				if (NULL == instance_) {
					// 1.lock_guard类是 non-copyable的
					// 2.lock_guard 类是一个mutex封装者，它为了拥有一个或多个mutex而提供了一种方便的 RAII style 机制
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
