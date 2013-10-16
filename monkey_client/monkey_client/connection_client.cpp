#include "connection_client.h"
#include "network.h"


connection_client::~connection_client(void)
{
}

void connection_client::handle_connected( const boost::system::error_code& e )
{
	monkey::net::connection::handle_connected(e);
	if (!e) {
		if (!network_.expired()) {
			network_.lock()->on_connected(boost::dynamic_pointer_cast<connection_client>(shared_from_this()));
		}
	}
}
