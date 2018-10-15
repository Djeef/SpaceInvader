/*
 * Drawable.hpp
 *
 *  Created on: 12 oct. 2018
 *      Author: Jean-Fran�ois
 */

#ifndef VIEW_UNIT_DRAWABLE_HPP_
#define VIEW_UNIT_DRAWABLE_HPP_

#include <utility>
#include <SFML/Graphics.hpp>

namespace si {
class Drawable {
protected:
	/**
	 * Position
	 */
	sf::Vector2f _position;

	/**
	 * Size
	 */
	sf::Vector2f _size;

public:
	/**
	 * Drawable constructor
	 */
	Drawable();

	/**
	 * Virtual destructor
	 */
	virtual ~Drawable() = default;

	/**
	 * Draw the drawable in the window
	 *
	 * @Param window
	 * 		main window
	 */
	virtual void draw(sf::RenderWindow& window) = 0;

	/**
	 * Move Drawable
	 *
	 * @Param x
	 * 		x position
	 * @Param y
	 * 		y position
	 */
	void move(const float x, const float y);

	/**
	 * Move Drawable
	 *
	 * @Param movePosition
	 * 		move vector
	 */
	void move(const sf::Vector2f movePositon);

	/**
	 * Set new position
	 *
	 * @Param x
	 * 		x position
	 * @Param y
	 * 		y position
	 */
	void setPosition(const float x, const float y);

	/**
	 * Set new position
	 *
	 * @Param position
	 * 		new position
	 */
	void setPosition(const sf::Vector2f position);

	/**
	 * Get position
	 *
	 * @Return
	 * 		the position
	 */
	const sf::Vector2f getPosition() const;

	/**
	 * Get size
	 *
	 * @Return
	 * 		the size
	 */
	const virtual sf::Vector2f getSize();

};
} /* namespace si */

#endif /* VIEW_UNIT_DRAWABLE_HPP_ */
