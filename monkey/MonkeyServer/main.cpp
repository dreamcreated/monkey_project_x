#include <string>
#include <iostream>
#include <monkey/net/server.h>
#include <common/messages/Login.pb.h>
#include <common/messages/scene_messages.pb.h>
#include <boost/thread.hpp>
#include <monkey/net/message_queue.h>
#include "logic/session_factory.h"
#include <boost/shared_ptr.hpp>
#include "logic/logic_context.h"

#pragma comment(lib, "common.lib")

int main(int argc, char** argv) {
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	logic_context::get_instance()->init();
	using namespace monkey;
	boost::shared_ptr<session_factory> pFac(new session_factory);
	net::message_queue::get_instance()->register_session_factory(pFac);
	net::server local_server("0.0.0.0", "1991", 4);
	local_server.run();


	google::protobuf::ShutdownProtobufLibrary();


	//common::Login l;
	common::scene_enter a;
	common::scene_move b;
	system("pause");
}