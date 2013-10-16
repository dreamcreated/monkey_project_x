#include "session.h"
namespace monkey{
namespace net{

boost::shared_ptr<connection> session::get_connection()
{
	return connection_;
}

session::session( void )
{

}

session::~session( void )
{

}

};
};
