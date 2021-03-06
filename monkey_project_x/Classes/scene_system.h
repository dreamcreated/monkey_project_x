#pragma once
#include <monkey/service/system_service.h>
#include <monkey/utils/singleton.hpp>
#include <common/messages/scene_messages.pb.h>
#include <boost/shared_ptr.hpp>

typedef std::map<int, boost::shared_ptr<common::player_info>> players_map_type;

class scene_system
	: public monkey::service::system_service
	, public monkey::utils::singleton<scene_system>
{
public:

	static void on_scene_enter(boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_enter> msg);
	static void on_scene_move(boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_move> msg);
	static void on_player_list(boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::player_list> msg);

	bool init();
	void fint();
	void on_user_enter(boost::shared_ptr<monkey::net::session> client_context);
	void on_user_leave(boost::shared_ptr<monkey::net::session> client_context);

	scene_system(void);
	~scene_system(void);

	const players_map_type& get_players() const;
private:
	bool register_player(int player_id, const boost::shared_ptr<common::player_info> player_info);
	bool unregister_player(int player_id);
	void clear();
	players_map_type m_players;
};

