#pragma once
#include <boost/shared_ptr.hpp>
namespace monkey{
namespace utils{
	template<class T>
	class singleton {
	public:
		static boost::shared_ptr<T> get_instance() {
			static boost::shared_ptr<T> p_instance(new T);
			return p_instance;
		}
	};
};
};