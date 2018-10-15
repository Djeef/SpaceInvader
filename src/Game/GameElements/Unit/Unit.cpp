/*
 * Unit.cpp
 *
 *  Created on: 14 oct. 2018
 *      Author: Jean-Fran�ois
 */

#include <Game/GameElements/Unit/Unit.hpp>
#include <Game/GameElements/Rectangle/Bullet/Bullet.hpp>

namespace si {

Unit::Unit(BulletDir bulletDir) :
		Drawable { }, _bulletDir { bulletDir } {
}

std::shared_ptr<Bullet> Unit::fire() {
	if (_bullet == nullptr) {
		_bullet = std::make_shared<Bullet>(_bulletDir, this);
		_bullet->setColor(sf::Color::White);
		_bullet->setSize(4, 10);

		_bullet->setPosition(getPosition());
		if (_bulletDir == BulletDir::DOWN) {
			_bullet->move(30, 30);
		} else {
			_bullet->move((getSize().x / 2.0) - (_bullet->getSize().x / 2.0), -getSize().y / 2.0);
		}
		return _bullet;

	}
	return nullptr;
}

void Unit::removeBullet() {
	_bullet = nullptr;
}

const sf::Vector2f Unit::getSize() {
	sf::Vector2u posUint = _texture.getSize();
	_size = sf::Vector2f(posUint.x, posUint.y);
	return _size;
}

void Unit::draw(sf::RenderWindow& window) {
	_sprite.setTexture(_texture);
	_sprite.setPosition(_position);
	window.draw(_sprite);
}
} /* namespace si */
