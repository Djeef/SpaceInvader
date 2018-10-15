/*
 * Bullet.cpp
 *
 *  Created on: 14 oct. 2018
 *      Author: Jean-Fran�ois
 */

#include <Game/GameElements/Rectangle/Bullet/Bullet.hpp>
#include <Game/GameElements/Unit/Unit.hpp>

namespace si {

Bullet::Bullet(BulletDir bulletDir) :
		Rectangle { }, Updatable { }, _bulletDir { bulletDir } {
	_unit = nullptr;
}

Bullet::Bullet(BulletDir bulletDir, si::Unit* unit) :
		Bullet { bulletDir } {
	_unit = unit;
}

void Bullet::destroy() {
	if (_unit != nullptr) {
		_unit->removeBullet();
	}
}

std::shared_ptr<Unit> Bullet::collision(std::list<std::shared_ptr<Unit>>& units) {
	for (auto& u : units) {
		double maxLef = std::max(u->getPosition().x, getPosition().x);
		double minRig = std::min(u->getPosition().x + u->getSize().x, getPosition().x + getSize().x);
		if (maxLef < minRig) {
			double maxBot = std::max(u->getPosition().y, getPosition().y);
			double minTop = std::min(u->getPosition().y + u->getSize().y, getPosition().y + getSize().y);
			if (maxBot < minTop) {
				return u;
			}
		}
	}
	return nullptr;
}

void Bullet::update() {
	if (_bulletDir == BulletDir::DOWN) {
		move(0, BULLET_SPEED);
	} else {
		move(0, -BULLET_SPEED);
	}
}

} /* namespace si */
