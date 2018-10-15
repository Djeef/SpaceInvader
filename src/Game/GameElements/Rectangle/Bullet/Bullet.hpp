/*
 * Bullet.hpp
 *
 *  Created on: 14 oct. 2018
 *      Author: Jean-Fran�ois
 */

#ifndef GAME_SHAPE_BULLET_HPP_
#define GAME_SHAPE_BULLET_HPP_

#define BULLET_SPEED 5

#include <iostream>
#include <memory>
#include <list>
#include <Game/Updatable/Updatable.hpp>
#include <Game/GameElements/Rectangle/Rectangle.hpp>
#include <Game/GameElements/Rectangle/Bullet/BulletDir.hpp>

namespace si {

class Unit;

class Bullet: public Rectangle, public Updatable {
private:
	/**
	 * Bullet direction
	 */
	BulletDir _bulletDir;

	/**
	 * From this unit
	 */
	si::Unit* _unit;

public:
	/**
	 * Bulet constructo
	 *
	 * @Param bulletDir
	 * 		bullet direction
	 */
	Bullet(BulletDir bulletDir);

	/**
	 * Bullet constructor
	 *
	 * @Param bulletDir
	 * 		bullet direction
	 * @Param unit
	 * 		from this unit
	 */
	Bullet(BulletDir bulletDir, si::Unit* unit);

	/**
	 * Default destructor
	 */
	~Bullet() = default;

	/**
	 * Delete bullet
	 */
	void destroy();

	/**
	 * Check collision
	 *
	 * @Param units
	 * 		list of all units
	 *
	 * @Return true if collision
	 */
	std::shared_ptr<Unit> collision(std::list<std::shared_ptr<Unit>>& units);

	/**
	 * Update method implementation
	 */
	void update() override;
};

} /* namespace si */

#endif /* GAME_SHAPE_BULLET_HPP_ */
