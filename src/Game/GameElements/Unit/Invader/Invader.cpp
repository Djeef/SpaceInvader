/*
 * Invader.cpp
 *
 *  Created on: 14 oct. 2018
 *      Author: Jean-Fran�ois
 */

#include <iostream>
#include <chrono>
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
	sf::Time elapsed = _clock.getElapsedTime();
	if (elapsed.asSeconds() >= (1.0 * (1.0 / _speed))) {

		_nbMove++;
		if (_nbMove >= INVADER_STEP) {
			move(0, INVADER_MOVE);
			_nbMove = 0;
			_rightDirection = !_rightDirection;
		} else {
			if (_rightDirection) {
				move(INVADER_MOVE, 0);
			} else {
				move(-INVADER_MOVE, 0);
			}
		}
		_clock.restart();

	}
}

void Invader::speedUp() {
	_speed += 0.1;
}

bool Invader::isFire() {
	float value = _distribution(_re);
	if (value <= _chanceToFire) {
		return true;
	}
	return false;
}

} /* namespace si */
