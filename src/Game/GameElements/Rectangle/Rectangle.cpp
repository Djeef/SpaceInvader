/*
 * Element.cpp
 *
 *  Created on: 14 oct. 2018
 *      Author: Jean-Fran�ois
 */

#include <Game/GameElements/Rectangle/Rectangle.hpp>

namespace si {


void Rectangle::setSize(const unsigned int x, const unsigned int y) {
	_size = sf::Vector2f(x, y);
}

void Rectangle::setSize(const sf::Vector2f size) {
	_size = size;
}

void Rectangle::setColor(const sf::Color color) {
	_color = color;
}

void Rectangle::draw(sf::RenderWindow& window) {
	rectangle.setSize(_size);
	rectangle.setPosition(_position);
	rectangle.setFillColor(_color);
	window.draw(rectangle);
}

} /* namespace si */
