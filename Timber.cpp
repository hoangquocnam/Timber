#include <iostream>
#include<SFML/Graphics.hpp>
#include<sstream>
#include<SFML/Audio.hpp>

using namespace sf;
using namespace std;

const int NUM_BRANCHES = 6;
const double AXE_POSITION_LEFT = 700;
const double AXE_POSITION_RIGHT = 1075;

Sprite Branches[NUM_BRANCHES];

enum class side {
	LEFT,
	RIGHT,
	NONE,
};

side BranchPosition[NUM_BRANCHES];

void MoveBee(bool& isActiveBee, Sprite& sprtBee, double& speedBee, Time dt) {
	if (!isActiveBee) {
		// speed
		srand(time(NULL));
		speedBee = (double)(rand() % 200) + 200;

		// height
		srand((int)time(0) * 10);
		double height = (double)(rand() % 400) + 100;
		sprtBee.setPosition(2000, height);
		isActiveBee = 1;
	}
	else {
		// move
		sprtBee.setPosition(sprtBee.getPosition().x - (speedBee * dt.asSeconds()), sprtBee.getPosition().y);
		if (sprtBee.getPosition().x < -100) {
			isActiveBee = 0;
		}
	}

}

void MoveCloud(bool& isActiveCloud, Sprite& Cloud, double& speedCloud, Time dt, int order) {
	if (!isActiveCloud) {
		// speed
		srand((int)time(NULL) * (10 * order));
		speedCloud = (double)(rand() % (200 * order));

		//height
		srand((int)time(NULL) * (10 * order));
		double height = (double)(rand() % (100 * order));
		Cloud.setPosition(-200, height);
		isActiveCloud = 1;
	}
	else
	{
		Cloud.setPosition(Cloud.getPosition().x + (speedCloud * dt.asSeconds()), Cloud.getPosition().y);
		if (Cloud.getPosition().x >= 2000) {
			isActiveCloud = 0;
		}
	}
}

void updateBranches(int seed) {
	for (int i = NUM_BRANCHES - 1; i > 0; i--) {
		BranchPosition[i] = BranchPosition[i - 1];
		srand(time(0) + seed);
		int r = rand() % 5;

		switch (r)
		{
		case 0:
			BranchPosition[0] = side::LEFT;
			break;
		case 1:
			BranchPosition[0] = side::RIGHT;
			break;
		default:
			BranchPosition[0] = side::NONE;
			break;
		}
	}
}

void Clear(Sprite& RIP, Sprite& Player, Sprite& AXE, bool& acceptInput) {
	for (int i = 0; i < NUM_BRANCHES; i++) {
		BranchPosition[i] = side::NONE;
	}
	RIP.setPosition(-2000, -2000);
	Player.setPosition(580, 720);
	AXE.setPosition(AXE_POSITION_LEFT, 830);
	acceptInput = 1;
}

int main()
{
#pragma region Make a window

	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

#pragma endregion

#pragma region Background

	Texture txtBackground;
	txtBackground.loadFromFile("graphics/background.png");
	Sprite sprtBackground;
	sprtBackground.setTexture(txtBackground);
	sprtBackground.setPosition(0, 0);

#pragma endregion

#pragma region Tree

	Texture txtTree;
	txtTree.loadFromFile("graphics/tree.png");
	Sprite sprtTree;
	sprtTree.setTexture(txtTree);
	sprtTree.setPosition(810, 0);

	Texture Tree;
	Tree.loadFromFile("graphics/tree2.png");

	Sprite tree1;
	Sprite tree2;
	Sprite tree3;
	tree1.setTexture(Tree);
	tree2.setTexture(Tree);
	tree3.setTexture(Tree);

	tree1.setPosition(50, -100);
	tree2.setPosition(1500, 50);
	tree3.setPosition(1500, 0);

#pragma endregion

#pragma region Bee
	Texture txtBee;
	txtBee.loadFromFile("graphics/bee.png");
	Sprite sprtBee;
	sprtBee.setTexture(txtBee);
	sprtBee.setPosition(0, 800);

	bool isActiveBee = 0;
	double speedBee = 0.0f;

#pragma endregion

#pragma region Clouds

	Texture txtCloud1;
	txtCloud1.loadFromFile("graphics/cloud.png");
	Sprite sprtCloud1;
	sprtCloud1.setTexture(txtCloud1);
	sprtCloud1.setPosition(100, 0);
	bool isActiveCloud1 = 0;
	double speedCloud1 = 0.0f;

	Texture txtCloud2;
	txtCloud2.loadFromFile("graphics/cloud.png");
	Sprite sprtCloud2;
	sprtCloud2.setTexture(txtCloud2);
	sprtCloud2.setPosition(1500, 150);
	bool isActiveCloud2 = 0;
	double speedCloud2 = 0.0f;

	Texture txtCloud3;
	txtCloud3.loadFromFile("graphics/cloud.png");
	Sprite sprtCloud3;
	sprtCloud3.setTexture(txtCloud3);
	sprtCloud3.setPosition(1000, 250);
	bool isActiveCloud3 = 0;
	double speedCloud3 = 0.0f;

#pragma endregion

#pragma region Time bar

	// Time
	Clock clock;

	// Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHegiht = 80;
	timeBar.setSize(Vector2f{ timeBarStartWidth, timeBarHegiht });
	timeBar.setFillColor(Color::Cyan);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTime;
	float timeRemain = 6;
	float timeBarWidthperSec = timeBarStartWidth / timeRemain;

#pragma endregion

#pragma region Font / Text

	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	// Text
	int score = 0;
	Text msgTxt, scoreTxt;

	msgTxt.setFont(font);
	scoreTxt.setFont(font);

	msgTxt.setString("Press Enter to start!");
	scoreTxt.setString("Score = 0");

	msgTxt.setCharacterSize(75);
	scoreTxt.setCharacterSize(100);

	msgTxt.setFillColor(Color::White);
	scoreTxt.setFillColor(Color::White);

	FloatRect txtRect = msgTxt.getGlobalBounds();
	msgTxt.setOrigin(txtRect.left + txtRect.width / 2.0, txtRect.top + txtRect.height / 2.0);

	msgTxt.setPosition(1920 / 2.0, 1080 / 2.0);
	scoreTxt.setPosition(20, 20);

#pragma endregion

#pragma region Branches

	Texture txtBranch;
	txtBranch.loadFromFile("graphics/branch.png");

	for (int i = 0; i < NUM_BRANCHES; i++) {
		Branches[i].setTexture(txtBranch);
		Branches[i].setPosition(-100, -100);
		Branches[i].setOrigin(220, 20);
	}

#pragma endregion

#pragma region Player

	// Player
	side sidePlayer = side::LEFT;
	Texture txtPlayer;
	txtPlayer.loadFromFile("graphics/player.png");

	Sprite Player;
	Player.setTexture(txtPlayer);
	Player.setPosition(580, 720);

	// RIP
	Texture txtRIP;
	txtRIP.loadFromFile("graphics/rip.png");
	Sprite RIP;
	RIP.setTexture(txtRIP);
	RIP.setPosition(-600, -860);

	// Axe
	Texture txtAxe;
	txtAxe.loadFromFile("graphics/axe.png");
	Sprite Axe;
	Axe.setTexture(txtAxe);
	Axe.setPosition(700, 830);

#pragma endregion

#pragma region Log
	Texture txtLog;
	txtLog.loadFromFile("graphics/log.png");
	Sprite Log;
	Log.setTexture(txtLog);
	Log.setPosition(810, 720);

	bool isActiveLog = 0;
	double speedLogX = 1000;
	double speedLogY = -1500;

#pragma endregion

#pragma region Sound

	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	SoundBuffer dieBuffer;
	dieBuffer.loadFromFile("sound/death.wav");
	Sound die;
	die.setBuffer(dieBuffer);

	SoundBuffer timeoverBuffer;
	timeoverBuffer.loadFromFile("sound/time_out.wav");
	Sound timeOut;
	timeOut.setBuffer(timeoverBuffer);

#pragma endregion

	bool paused = true;
	bool acceptInput = 0;
	Event event;


	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			paused = 0;
			score = 0;
			timeRemain = 6;
			Clear(RIP, Player, Axe, acceptInput);
		}

		if (acceptInput) {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				sidePlayer = side::RIGHT;
				score++;
				// if chop right, add time
				if (timeRemain < 6) timeRemain += (2 / score) + 0.15;
				Axe.setPosition(AXE_POSITION_RIGHT, Axe.getPosition().y);
				Player.setPosition(1200, 720);
				updateBranches(score);

				Log.setPosition(810, 720);
				speedLogX = -5000;
				isActiveLog = true;
				acceptInput = false;
				chop.play();
			}

			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				sidePlayer = side::LEFT;
				score++;
				if (timeRemain < 6) timeRemain += (2 / score) + 0.15;
				Axe.setPosition(AXE_POSITION_LEFT, Axe.getPosition().y);
				Player.setPosition(580, 720);
				updateBranches(score);

				Log.setPosition(810, 720);
				speedLogX = 5000;
				isActiveLog = true;
				acceptInput = false;
				chop.play();

			}
		}

		while (window.pollEvent(event)) {
			if (event.type == Event::KeyReleased && !paused) {
				acceptInput = 1;
				Axe.setPosition(-2000, Axe.getPosition().y);
			}
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		window.clear();

		if (!paused) {
			Time dt = clock.restart(); // dt = delta time   
			timeRemain -= dt.asSeconds();
			timeBar.setSize(Vector2f(timeBarWidthperSec * timeRemain, timeBarHegiht));
			if (timeRemain < 0) {
				paused = 1;
				msgTxt.setString("Game Over!");
				txtRect = msgTxt.getLocalBounds();
				msgTxt.setOrigin(txtRect.left + txtRect.width / 2.0, txtRect.top + txtRect.height / 2.0);
				msgTxt.setPosition(1920 / 2.0, 1080 / 2.0);
				/*if (timeRemain == 0)*/ timeOut.play();
			}

			MoveBee(isActiveBee, sprtBee, speedBee, dt);
			MoveCloud(isActiveCloud1, sprtCloud1, speedCloud1, dt, 1);
			MoveCloud(isActiveCloud2, sprtCloud2, speedCloud2, dt, 2);
			MoveCloud(isActiveCloud3, sprtCloud3, speedCloud3, dt, 3);

			stringstream ss;
			ss << "Score = " << score;
			scoreTxt.setString(ss.str());

			for (int i = 0; i < NUM_BRANCHES; i++) {
				double heightbranch = i * 150.0;
				if (BranchPosition[i] == side::LEFT) {
					Branches[i].setPosition(600, heightbranch);
					Branches[i].setRotation(180);
				}
				else if (BranchPosition[i] == side::RIGHT) {
					Branches[i].setPosition(1330, heightbranch);
					Branches[i].setRotation(0);
				}
				else {
					Branches[i].setPosition(-200, -200);
				}
			}

			if (isActiveLog) {
				Log.setPosition(Log.getPosition().x + (speedLogX * dt.asSeconds()), Log.getPosition().y + (speedLogY * dt.asSeconds()));
				int LogX = Log.getPosition().x;
				if (LogX < -100 || LogX > 2000) {
					isActiveLog = 0;
					Log.setPosition(810, 720);
				}
			}

			if (BranchPosition[5] == sidePlayer) {
				paused = true;
				acceptInput = false;

				RIP.setPosition(Player.getPosition().x, Player.getPosition().y + 50);
				Player.setPosition(-2000, 2000);
				Axe.setPosition(-2000, -2000);

				paused = 1;
				msgTxt.setString("PONK !!!");
				txtRect = msgTxt.getLocalBounds();
				msgTxt.setOrigin(txtRect.left + txtRect.width / 2.0, txtRect.top + txtRect.height / 2.0);
				msgTxt.setPosition(1920 / 2.0, 1080 / 2.0);
				die.play();
			}
		}

		// draw

		window.draw(sprtBackground);
		window.draw(sprtTree);
		window.draw(sprtCloud1);
		window.draw(tree2);
		window.draw(sprtCloud2);
		window.draw(tree1);
		window.draw(sprtCloud3);
		window.draw(tree3);
		window.draw(sprtBee);
		window.draw(scoreTxt);
		window.draw(timeBar);
		window.draw(Player);
		window.draw(Axe);
		window.draw(Log);
		window.draw(RIP);

		if (paused) {
			window.draw(msgTxt);
		}
		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(Branches[i]);
		}
		//
		window.display();

	}
	return 0;
}


