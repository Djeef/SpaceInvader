/*
 * Unit.hpp
 *
 *  Created on: 14 oct. 2018
 *      Author: Jean-Fran�ois
 */

#ifndef GAME_UNIT_UNIT_HPP_
#define GAME_UNIT_UNIT_HPP_

#include <memory>
#include "Game/Drawable/Drawable.hpp"
#include <Game/GameElements/Rectangle/Bullet/BulletDir.hpp>

namespace si {

class Bullet;

class Unit: public Drawable {
protected:
	/**
	 * The texture of the unit
	 */
	sf::Texture _texture;

	/**
	 * The associated sprite
	 */
	sf::Sprite _sprite;

	/**
	 * The bullet
	 */
	std::shared_ptr<Bullet> _bullet;

	/**
	 * The bullet direction
	 */
	si::BulletDir _bulletDir;
public:

	/**
	 * Unit constructor
	 */
	Unit(BulletDir bulletDir);

	/**
	 * Fire
	 */
	std::shared_ptr<Bullet> fire();

	/**
	 * Get size
	 *
	 * @Return
	 * 		the size
	 */
	const sf::Vector2f getSize() override;

	/**
	 * Remove bullet
	 */
	void removeBullet();

	/**
	 * Draw unit
	 *
	 * @Param window
	 * 		main window
	 */
	void draw(sf::RenderWindow& window) override;
};

} /* namespace si */

#endif /* GAME_UNIT_UNIT_HPP_ */
