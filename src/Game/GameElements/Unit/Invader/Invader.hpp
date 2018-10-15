/*
 * Invader.hpp
 *
 *  Created on: 14 oct. 2018
 *      Author: Jean-Fran�ois
 */

#ifndef GAME_DRAWABLE_UNIT_INVADER_INVADER_HPP_
#define GAME_DRAWABLE_UNIT_INVADER_INVADER_HPP_

#include <random>
#include "Game/GameElements/Unit/Unit.hpp"
#include <Game/Updatable/Updatable.hpp>

namespace si {

class Invader: public Unit, public Updatable {
private:
	/**
	 * Random engine
	 */
	std::default_random_engine _re;

	/**
	 * Uniform probability
	 */
	std::uniform_int_distribution<float> _distribution { 0, 100 };

	/**
	 * Chance to fire
	 */
	float _chanceToFire { 0.042 };

public:

	/**
	 * Invader constructor
	 */
	Invader();

	/**
	 * Is fire ?
	 *
	 * @Return if is fire
	 */
	bool isFire();

	/**
	 * Update method implementation
	 */
	void update() override;
};

} /* namespace si */

#endif /* GAME_DRAWABLE_UNIT_INVADER_INVADER_HPP_ */
