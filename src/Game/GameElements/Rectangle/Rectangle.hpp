/*
 * Element.hpp
 *
 *  Created on: 14 oct. 2018
 *      Author: Jean-Fran�ois
 */

#ifndef GAME_SHAPE_SHAPE_HPP_
#define GAME_SHAPE_SHAPE_HPP_

#include "Game/Drawable/Drawable.hpp"

namespace si {

class Rectangle: public Drawable {
protected:
	/**
	 * The rectangle
	 */
	sf::RectangleShape rectangle;

	/**
	 * Color of the rectangle
	 */
	sf::Color _color;

public:

	/**
	 * Rectangle destructor
	 */
	virtual ~Rectangle() = default;

	/**
	 * Draw unit
	 *
	 * @Param window
	 * 		main window
	 */
	void draw(sf::RenderWindow& window);

	/**
	 * Set new size
	 *
	 * @Param x
	 * 		x size
	 * @Param y
	 * 		y size
	 */
	void setSize(const unsigned int x, const unsigned int y);

	/**
	 * Set new size
	 *
	 * @Param size
	 * 		new size
	 */
	void setSize(const sf::Vector2f position);

	/**
	 * Set color
	 *
	 * @Param color
	 * 		the color
	 */
	void setColor(const sf::Color color);
};

} /* namespace si */

#endif /* GAME_SHAPE_SHAPE_HPP_ */
