/*
 * WindowManager.cpp
 *
 *  Created on: 11 oct. 2018
 *      Author: Jean-Fran�ois
 */
#include <iostream>
#include "View.hpp"

namespace si {
View::View(int width, int height, unsigned int fps, sf::String name) {
	// Create new window
	_window.create(sf::VideoMode(width, height), name);

	// Deactivate OpenGL context
	_window.setActive(false);

	// Set framerate to 30
	_window.setFramerateLimit(fps);

	// Set game and window size
	_windowSize = sf::Vector2f(width, height);
	_gameOffset = sf::Vector2f(0.0, 0.0);
	_gameSize = _windowSize;

	_player = std::make_shared<Player>();
}

View::View(int width, int height, int minX, int maxX, int minY, int maxY, unsigned int fps, sf::String name) :
		View { width, height, fps, name } {
	// Set game limits
	_gameOffset = sf::Vector2f(minX, minY);
	_gameSize = sf::Vector2f(maxX, maxY) - (_windowSize - sf::Vector2f(maxX, maxY));
}

void View::startRendering() {
	init();

	// Until the window is open
	while (_window.isOpen()) {
		// Window event
		sf::Event event;

		// Until event is present
		while (_window.pollEvent(event)) {

			// Switch on event type
			switch (event.type) {

			case sf::Event::Closed:
				// Close window
				closeWindow();
				break;

			case sf::Event::KeyPressed:
				// Key pressed, call the controller
				keyPressed(event.key.code);
				break;

			case sf::Event::KeyReleased:
				// Key pressed, call the controller
				keyReleased(event.key.code);
				break;

			default:
				break;
			}
		}

		// Get informations from the model
		update();

		// Rendering
		rendering();
	}
}

void View::init() {
	_background.setSize(_windowSize);
	_background.setColor(sf::Color(100, 100, 100));

	_gameZone.setSize(_gameSize);
	_gameZone.setPosition(_gameOffset);
	_gameZone.setColor(sf::Color::Black);

	_player->setPosition((_windowSize.x / 2.0) - (_player->getSize().x / 2.0) - (_gameOffset.x / 2.0), PLAYER_Y_LINE);
	_units.push_back(_player);

	_units.push_back(std::make_shared<Invader>());
	_units.back()->setPosition(sf::Vector2f(70, 100));
	_units.push_back(std::make_shared<Invader>());
	_units.back()->setPosition(sf::Vector2f(170, 100));
	_units.push_back(std::make_shared<Invader>());
	_units.back()->setPosition(sf::Vector2f(270, 100));
	_units.push_back(std::make_shared<Invader>());
	_units.back()->setPosition(sf::Vector2f(370, 100));
	_units.push_back(std::make_shared<Invader>());
	_units.back()->setPosition(sf::Vector2f(470, 100));
	_units.push_back(std::make_shared<Invader>());
	_units.back()->setPosition(sf::Vector2f(570, 100));
	_units.push_back(std::make_shared<Invader>());
	_units.back()->setPosition(sf::Vector2f(670, 100));

	_units.push_back(std::make_shared<Invader>());
	_units.back()->setPosition(sf::Vector2f(70, 200));
	_units.push_back(std::make_shared<Invader>());
	_units.back()->setPosition(sf::Vector2f(170, 200));
	_units.push_back(std::make_shared<Invader>());
	_units.back()->setPosition(sf::Vector2f(270, 200));
	_units.push_back(std::make_shared<Invader>());
	_units.back()->setPosition(sf::Vector2f(370, 200));
	_units.push_back(std::make_shared<Invader>());
	_units.back()->setPosition(sf::Vector2f(470, 200));
	_units.push_back(std::make_shared<Invader>());
	_units.back()->setPosition(sf::Vector2f(570, 200));
	_units.push_back(std::make_shared<Invader>());
	_units.back()->setPosition(sf::Vector2f(670, 200));
}

void View::keyPressed(sf::Keyboard::Key code) {
	switch (code) {
	case sf::Keyboard::Right:
		_right = true;
		break;
	case sf::Keyboard::Left:
		_left = true;
		break;
	case sf::Keyboard::Space:
		_fire = true;
		break;
	default:
		break;
	}
}

void View::keyReleased(sf::Keyboard::Key code) {
	switch (code) {
	case sf::Keyboard::Right:
		_right = false;
		break;
	case sf::Keyboard::Left:
		_left = false;
		break;
	case sf::Keyboard::Space:
		_fire = false;
		break;
	default:
		break;
	}
}

void View::moveRight() {
	float pos = _gameOffset.x + _gameSize.x - (float) _player->getSize().x;
	if (_player->getPosition().x + MOVE_SPEED > pos) {
		_player->setPosition(pos, PLAYER_Y_LINE);
	} else {
		_player->move(MOVE_SPEED, 0);
	}
}

void View::moveLeft() {
	if (_player->getPosition().x - MOVE_SPEED < _gameOffset.x) {
		_player->setPosition(_gameOffset.x, PLAYER_Y_LINE);
	} else {
		_player->move(-MOVE_SPEED, 0);
	}
}

void View::fire() {
	std::shared_ptr<Bullet> bullet = _player->fire();
	if (bullet != nullptr) {
		_bullets.push_back(bullet);
	}
}

void View::update() {
	// Player actions
	if (!_gameOver) {
		if (_right) {
			moveRight();
		}
		if (_left) {
			moveLeft();
		}
		if (_fire) {
			fire();
		}
	}

	// Bots actions
	for (auto& u : _units) {
		if (Invader* i = dynamic_cast<Invader*>(u.get())) {
			i->update();
			if (i->isFire()) {
				std::shared_ptr<Bullet> bullet = i->fire();
				if (bullet != nullptr) {
					_bullets.push_back(bullet);
				}
			}
		}
	}

	// Bullets actions
	auto (b) = std::begin(_bullets);
	while (b != std::end(_bullets)) {
		(*b)->update();
		std::shared_ptr<Unit> unit = (*b)->collision(_units);
		if (unit != nullptr) {
			(*b)->destroy();
			b = _bullets.erase(b);

			if (Player* p = dynamic_cast<Player*>(unit.get())) {
				_gameOver = true;
			}
			_units.remove(unit);

		} else if ((*b)->getPosition().y < _gameOffset.y || (*b)->getPosition().y > _gameSize.y) {
			(*b)->destroy();
			b = _bullets.erase(b);
		} else {
			++b;
		}
	}
}

void View::rendering() {
	// Clear window
	_window.clear();

	_background.draw(_window);
	_gameZone.draw(_window);
	for (auto& u : _units) {
		u->draw(_window);
	}

	for (auto& b : _bullets) {
		b->draw(_window);
	}

	// Display
	_window.display();
}

void View::closeWindow() {
	_window.close();
}

} /* namespace si */

