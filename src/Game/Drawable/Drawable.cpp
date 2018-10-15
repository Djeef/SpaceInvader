/*
 * Drawable.cpp
 *
 *  Created on: 12 oct. 2018
 *      Author: Jean-Fran�ois
 */

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <Game/Drawable/Drawable.hpp>

namespace si {

Drawable::Drawable() :
		_position { 0, 0 }, _size { 0, 0 } {
}

void Drawable::move(const float x, float y) {
	setPosition(_position + sf::Vector2f(x, y));
}

void Drawable::move(const sf::Vector2f movePositon) {
	setPosition(_position + movePositon);
}

void Drawable::setPosition(const float x, float y) {
	_position = sf::Vector2f(x, y);
}

void Drawable::setPosition(const sf::Vector2f position) {
	_position = position;
}

const sf::Vector2f Drawable::getPosition() const {
	return _position;
}

const sf::Vector2f Drawable::getSize() {
	return _size;
}

} /* namespace si */
