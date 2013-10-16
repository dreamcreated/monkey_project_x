#pragma once
#include <boost/asio.hpp>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
namespace monkey{
namespace net{

class io_service_pool
	: private boost::noncopyable
{
public:
	explicit io_service_pool(std::size_t pool_size);
	
	void run();

	void stop();

	boost::asio::io_service& get_io_service();
private:
	typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;
	typedef boost::shared_ptr<boost::asio::io_service::work> work_ptr;

	std::vector<io_service_ptr> io_services_;
	std::vector<work_ptr> work_;
	std::size_t next_io_service_;
};

};
};