#include "net/game_network.h"
#include <monkey/net/message_queue.h>
#include "net/game_session_factory.h"
#include "logic/logic_context.h"

int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow
	)
{
	logic_context::get_instance()->init();
	auto pGameNetwork = game_network::get_instance();
	boost::shared_ptr<game_session_factory> pFac(new game_session_factory);
	monkey::net::message_queue::get_instance()->register_session_factory(pFac);
	auto pConnection = pGameNetwork->create_connection("127.0.0.1", "1991");
	pConnection->set_tag(LOGIN_SESSION);
	pGameNetwork->async_start_service();


	return 0;
}