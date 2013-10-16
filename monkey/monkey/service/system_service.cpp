#include "system_service.h"
#include <iostream>

void monkey::service::system_service::on_registered()
{
	std::cout << get_service_name() << " is registered" <<std::endl;
}
