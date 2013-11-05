#pragma once
#include <string>
#include "../messages/scene_messages.pb.h"
namespace common {
class UserData
{
public:
	UserData(void);
	~UserData(void);
	int Pos_x() const { return player_info.player_position().x(); }
	void Pos_x(int val) { player_info.mutable_player_position()->set_x(val); }
	int Pos_y() const { return player_info.player_position().y(); }
	void Pos_y(int val) { player_info.mutable_player_position()->set_y(val); }
	std::string User_name() const { return m_user_name; }
	void User_name(std::string val) { m_user_name = val; }
	int Scene_id() const { return m_scene_id; }
	void Scene_id(int val) { m_scene_id = val; }
	unsigned int Player_id() const { return player_info.player_id(); }
	void Player_id(unsigned int val) { player_info.set_player_id(val); }
	common::player_info& Player_info() { return player_info; }
private:
	std::string m_user_name;
	int m_scene_id;
	common::player_info player_info;
};
};
