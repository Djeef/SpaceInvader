/*
 * Invader.cpp
 *
 *  Created on: 14 oct. 2018
 *      Author: Jean-Fran�ois
 */

#include <iostream>
#include <functional>
#include <Game/GameElements/Unit/Invader/Invader.hpp>

namespace si {
Invader::Invader() :
		Unit { BulletDir::DOWN } {
	if (!_texture.loadFromFile("data/sprite/invader.png")) {
		throw std::runtime_error("Invader: texture not found");
	}
	_re.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

void Invader::update() {

}

bool Invader::isFire() {
	float value = _distribution(_re);
	if (value <= _chanceToFire) {
		return true;
	}
	return false;
}

} /* namespace si */
