/*
 * WindowManager.h
 *
 *  Created on: 11 oct. 2018
 *      Author: Jean-Fran�ois
 */

#ifndef VIEW_VIEW_HPP_
#define VIEW_VIEW_HPP_

#define PLAYER_Y_LINE 550
#define MOVE_SPEED 5

#include <iostream>
#include <memory>
#include <list>
#include <SFML/Graphics.hpp>
#include "Game/GameElements/Rectangle/Rectangle.hpp"
#include "Game/GameElements/Rectangle/Bullet/Bullet.hpp"
#include "Game/GameElements/Unit/Player/Player.hpp"
#include "Game/GameElements/Unit/Invader/Invader.hpp"

namespace si {
class View {
private:
	/**
	 * The main window
	 */
	sf::RenderWindow _window;

	/**
	 * The player
	 */
	std::shared_ptr<Player> _player;

	/**
	 * Background
	 */
	si::Rectangle _background;

	/**
	 * Game zone
	 */
	si::Rectangle _gameZone;

	/**
	 * All units
	 */
	std::list<std::shared_ptr<Unit>> _units;

	/**
	 * All bullets
	 */
	std::list<std::shared_ptr<Bullet>> _bullets;

	/**
	 * Window limits
	 */
	sf::Vector2f _windowSize;

	/**
	 * Game offset
	 */
	sf::Vector2f _gameOffset;

	/**
	 * Game limits
	 */
	sf::Vector2f _gameSize;

	/**
	 * Game over
	 */
	bool _gameOver = false;

	/**
	 * Key values: right
	 */
	bool _right = false;

	/**
	 * Key values: left
	 */
	bool _left = false;

	/**
	 * Key values: space
	 */
	bool _fire = false;

public:
	/**
	 * View constructor (game limit are 0 to width and 0 to height)
	 *
	 * @Param width
	 * 		the window width
	 * @Param height
	 * 		the window height
	 * @Param fps
	 * 		frame per second max
	 * @Param name
	 * 		the window name
	 */
	View(int width, int height, unsigned int fps, sf::String name);

	/**
	 * View constructor
	 *
	 * @Param width
	 * 		the window width
	 * @Param height
	 * 		the window height
	 * @Param minX
	 * 		game limit x min
	 * @Param maxX
	 * 		game limit x max
	 * @Param minY
	 * 		game limit y min
	 * @Param maxY
	 * 		game limit y max
	 * @Param fps
	 * 		frame per second max
	 * @Param name
	 * 		the window name
	 */
	View(int width, int height, int minX, int maxX, int minY, int maxY, unsigned int fps, sf::String name);

	/**
	 * Vuew destructor
	 */
	~View() = default;

	/**
	 * Init view
	 */
	void init();

	/**
	 * Start rendering management
	 */
	void startRendering();

	/**
	 * Key pressed
	 *
	 * @Param code
	 * 		code of the key
	 */
	void keyPressed(sf::Keyboard::Key code);

	/**
	 * Key release
	 *
	 * @Param code
	 * 		code of the key
	 */
	void keyReleased(sf::Keyboard::Key code);

	/**
	 * Move right player
	 */
	void moveRight();

	/**
	 * Move left player
	 */
	void moveLeft();

	/**
	 * Fire !
	 */
	void fire();

	/**
	 * Update view with data from model
	 */
	void update();

	/**
	 * One step rendering
	 */
	void rendering();

	/**
	 * Close window function
	 */
	void closeWindow();
}
;
} /* namespace si */
#endif /* VIEW_VIEW_HPP_ */
