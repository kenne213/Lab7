
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;



int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(100, 120));
	ball.applyImpulse(Vector2f(0.4, 0));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);

	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	// Create the top wall 
	PhysicsRectangle topwall;
	topwall.setSize(Vector2f(800, 20));
	topwall.setCenter(Vector2f(400, 10));
	topwall.setStatic(true);
	world.AddPhysicsBody(topwall);

	// Create the left wall 
	PhysicsRectangle leftwall;
	leftwall.setSize(Vector2f(20, 560));
	leftwall.setCenter(Vector2f(10, 300));
	leftwall.setStatic(true);
	world.AddPhysicsBody(leftwall);

	// Create the right wall 
	PhysicsRectangle rightwall;
	rightwall.setSize(Vector2f(20, 560));
	rightwall.setCenter(Vector2f(790, 300));
	rightwall.setStatic(true);
	world.AddPhysicsBody(rightwall);

	// Create the obstacle 
	PhysicsRectangle obstacle;
	obstacle.setSize(Vector2f(100, 60));
	obstacle.setCenter(Vector2f(400, 300));
	obstacle.setStatic(true);
	world.AddPhysicsBody(obstacle);

	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	int bangCount(0);
	obstacle.onCollision = [&bangCount, &window, &obstacle](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;

		if (bangCount == 3) {
			Clock simpleClock;
			Time start(simpleClock.getElapsedTime());
			Time simpleDelta(start - start); //start at 0

			exit(0);
		}
	};

	topwall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	leftwall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	rightwall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	Clock clock;
	Time lastTime(clock.getElapsedTime());

	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());

		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}

		window.clear();
		window.draw(ball);
		window.draw(floor);
		window.draw(topwall);
		window.draw(leftwall);
		window.draw(rightwall);
		window.draw(obstacle);
		window.display();
	}
}