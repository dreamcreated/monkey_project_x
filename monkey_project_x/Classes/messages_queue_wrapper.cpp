#include "messages_queue_wrapper.h"
#include <monkey/net/message_queue.h>
#include "cocos2d.h"


messages_queue_wrapper::messages_queue_wrapper(void)
{
}


messages_queue_wrapper::~messages_queue_wrapper(void)
{
}

void messages_queue_wrapper::update( float dt )
{
	monkey::net::message_queue::get_instance()->update();
}
