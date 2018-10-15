/*
 * Updatable.hpp
 *
 *  Created on: Oct 15, 2018
 *      Author: djeef
 */

#ifndef SRC_GAME_UPDATABLE_UPDATABLE_HPP_
#define SRC_GAME_UPDATABLE_UPDATABLE_HPP_

namespace si {

class Updatable {

public:
	/**
	 * Virtual destructor
	 */
	virtual ~Updatable() = default;

	/**
	 * Update methode
	 */
	virtual void update() = 0;
};

} /* namespace si */

#endif /* SRC_GAME_UPDATABLE_UPDATABLE_HPP_ */
