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

	if (_font.loadFromFile("data/font/game_over.ttf")) {
		_gameOverText.setFont(_font);
		_gameOverText.setString(" Game Over\npress space");
		_gameOverText.setCharacterSize(110);
		_gameOverText.setFillColor(sf::Color::Red);
		_gameOverText.setPosition(_windowSize.x / 2.0 - 110,
				_windowSize.y / 2.0);

		_winText.setFont(_font);
		_winText.setString("   You Win\npress space");
		_winText.setCharacterSize(110);
		_winText.setFillColor(sf::Color::White);
		_winText.setPosition(_windowSize.x / 2.0 - 110, _windowSize.y / 2.0);
	}
}

View::View(int width, int height, int minX, int maxX, int minY, int maxY,
		unsigned int fps, sf::String name) :
		View { width, height, fps, name } {
	// Set game limits
	_gameOffset = sf::Vector2f(minX, minY);
	_gameSize = sf::Vector2f(maxX, maxY)
			- (_windowSize - sf::Vector2f(maxX, maxY));
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
	// Unit empty
	_units = std::list<std::shared_ptr<Unit>>();

	// Bullet empty
	_bullets = std::list<std::shared_ptr<Bullet>>();

	// Init backgound
	_background.setSize(_windowSize);
	_background.setColor(sf::Color(100, 100, 100));
	_gameZone.setSize(_gameSize);
	_gameZone.setPosition(_gameOffset);
	_gameZone.setColor(sf::Color::Black);

	// Init player
	_player = std::make_shared<Player>();
	_player->setPosition(
			(_windowSize.x / 2.0) - (_player->getSize().x / 2.0)
					- (_gameOffset.x / 2.0), PLAYER_Y_LINE);
	_units.push_back(_player);

	// Init invaders
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			_units.push_back(std::make_shared<Invader>());
			_units.back()->setPosition(sf::Vector2f(100 * j + 25, 50 * i + 25));
		}
	}
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
	/**
	 * Player actions
	 */

	// Player is alive
	// Space key
	if (_fire) {
		_fire = false;
		if (_gameOver) {
			init();
			_gameOver = false;
			return;
		} else if (_win) {
			init();
			_win = false;
			return;
		} else {
			fire();
		}
	}

	if (_gameOver || _win) {
		return;
	}
	// Right key
	if (_right) {
		moveRight();
	}
	// Left Key
	if (_left) {
		moveLeft();
	}

	/**
	 * Bots actions
	 */

	// For each invaders
	for (auto& u : _units) {
		// Check the type (is Invader ?)
		if (Invader* i = dynamic_cast<Invader*>(u.get())) {

			// Update invader
			i->update();

			// Check if the invader want to fire
			if (i->isFire()) {

				// Get the bullet
				std::shared_ptr<Bullet> bullet = i->fire();
				if (bullet != nullptr) {
					_bullets.push_back(bullet);
				}
			}

			if(i->getPosition().y == _player->getPosition().y) {
				_gameOver = true;
				return;
			}
		}
	}

	/**
	 *  Bullets actions
	 */

	bool speedUp = false;

	// First bullet
	auto (b) = std::begin(_bullets);

	// For each bullets
	while (b != std::end(_bullets)) {
		// Update the current bullet
		(*b)->update();
		// Check collision
		std::shared_ptr<Unit> unit = (*b)->collision(_units);

		if (unit != nullptr) {
			// Collision with unit

			if ((*b)->isFromInvader()) {
				if (dynamic_cast<Invader*>(unit.get())) {
					continue;
				}
			}

			// Remove reference of bullet in unit
			(*b)->destroy();
			// Remove bullet from the list
			b = _bullets.erase(b);

			// Check the type of the current unit (is Player ?)
			if (dynamic_cast<Player*>(unit.get())) {
				_gameOver = true;
				return;
			}

			// Remove reference of unit in bullet
			unit->destroy();
			// Remove unit from the list
			_units.remove(unit);

			speedUp = true;
		} else if ((*b)->getPosition().y < _gameOffset.y) {
			// Border of the screen

			// Remove reference of bullet in unit
			(*b)->destroy();
			// Remove bullet from the list
			b = _bullets.erase(b);
		} else if ((*b)->getPosition().y > _gameSize.y) {
			// Border of the screen

			// Remove reference of bullet in unit
			(*b)->destroy();
			// Remove bullet from the list
			b = _bullets.erase(b);
		} else {
			// No collisions next bullet
			++b;
		}

		if (_units.size() == 1 && dynamic_cast<Player*>(_units.front().get())) {
			_win = true;
		}
	}

	// If one invader is destroyed
	if (speedUp) {
		for (auto& u : _units) {
			// Check the type (is Invader ?)
			if (Invader* i = dynamic_cast<Invader*>(u.get())) {
				// Speed up
				i->speedUp();
			}
		}
	}
}

void View::rendering() {
	// Clear window
	_window.clear();

	// Draw background
	_background.draw(_window);
	_gameZone.draw(_window);

	// Draw units
	for (auto& u : _units) {
		u->draw(_window);
	}

	// Draw bullets
	for (auto& b : _bullets) {
		b->draw(_window);
	}

	// Draw Win
	if (_win) {
		_window.draw(_winText);
	}

	// Draw Game Over
	if (_gameOver) {
		_window.draw(_gameOverText);
	}

	// Display
	_window.display();
}

void View::closeWindow() {
	_window.close();
}

} /* namespace si */

