#include <SFML/Graphics.hpp>
#include "Game/View.hpp"

/**
 * Main of the game
 */
int main() {
	// Create view
	si::View view(800, 600, 20, 780, 20, 580, 60, "Space Invader");

	// Start rendering management
	view.startRendering();

	// Exit success
	return 0;
}
