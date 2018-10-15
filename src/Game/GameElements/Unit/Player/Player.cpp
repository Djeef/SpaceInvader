/*
 * Player.cpp
 *
 *  Created on: 14 oct. 2018
 *      Author: Jean-Fran�ois
 */

#include <Game/GameElements/Unit/Player/Player.hpp>

namespace si {
Player::Player() :
		Unit { BulletDir::TOP } {
	if (!_texture.loadFromFile("data/sprite/player.png")) {
		throw std::runtime_error("Player: texture not found");
	}
}
} /* namespace si */
