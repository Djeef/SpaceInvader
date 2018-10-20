/*
 * Invader.hpp
 *
 *  Created on: 14 oct. 2018
 *      Author: Jean-Fran�ois
 */

#ifndef GAME_DRAWABLE_UNIT_INVADER_INVADER_HPP_
#define GAME_DRAWABLE_UNIT_INVADER_INVADER_HPP_

#define INVADER_MOVE 25
#define INVADER_STEP 14

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
	std::uniform_int_distribution<int> _distribution { 0, 100 };

	/**
	 * Start the chrono
	 */
	sf::Clock _clock;

	/**
	 * Number of horizontal movement
	 */
	int _nbMove { };

	/**
	 * Is right direction
	 */
	bool _rightDirection { true };

	/**
	 * Chance to fire
	 */
	float _chanceToFire { 0.42 };

	/**
	 * Speed
	 */
	float _speed { 1 };

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
	 * Speed up
	 */
	void speedUp();

	/**
	 * Update method implementation
	 */
	void update() override;
};

} /* namespace si */

#endif /* GAME_DRAWABLE_UNIT_INVADER_INVADER_HPP_ */
