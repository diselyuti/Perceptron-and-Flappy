#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include "Game.h";
#include "Perceptron.h";

using namespace sf;
using namespace std;

int gameSessionEducation(Sprite &bird, Sprite &spriteBackground, Sprite &spriteLowerWall, Sprite &spriteUpperWall, RenderWindow &window, Perceptron &perceptron) {
	GameObject player(bird, FloatRect(70, 384, 17, 12));
	Clock timer;
	float time;
	int score = 0;
	queue<GameObject> objectsQueue;

	for (size_t i = 0; i < 4; i++)
	{
		int height = rand() % 150 - 75;
		GameObject upperWall(spriteUpperWall, FloatRect(i * 150 + 200, -100 + height, 26, 160));
		GameObject lowerWall(spriteLowerWall, FloatRect(i * 150 + 200, 600 + height, 26, 160));
		lowerWall.gravitation = 0;
		upperWall.gravitation = 0;
		lowerWall.dx = -0.5;
		upperWall.dx = -0.5;
		lowerWall.height = height;
		upperWall.height = height;

		objectsQueue.push(lowerWall);
		objectsQueue.push(upperWall);
	}

	while (window.isOpen())
	{
		window.draw(spriteBackground);
		time = timer.getElapsedTime().asMicroseconds();
		timer.restart();
		time /= 2000;

		if (objectsQueue.front()._rect.left < -100)
		{
			int height = rand() % 200 - 100;
			GameObject newUpperWall(spriteUpperWall, FloatRect(500, -100 + height, 26, 160));
			GameObject newLowerWall(spriteLowerWall, FloatRect(500, 600 + height, 26, 160));
			newUpperWall.gravitation = 0;
			newLowerWall.gravitation = 0;
			newUpperWall.dx = -0.5;
			newLowerWall.dx = -0.5;
			newLowerWall.height = height;
			newUpperWall.height = height;
			objectsQueue.pop();
			objectsQueue.pop();
			objectsQueue.push(newUpperWall);
			objectsQueue.push(newLowerWall);
			score++;
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		vector<double> info;
		queue<GameObject> tmpObjectsQueue(objectsQueue);
		GameObject tmp = tmpObjectsQueue.front();
		if (tmp._rect.left - player._rect.left > 0)
		{
			info.push_back(tmp._rect.left - player._rect.left);
			info.push_back(tmp.height);
		}
		else {
			tmpObjectsQueue.pop();
			tmpObjectsQueue.pop();
			tmp = tmpObjectsQueue.front();
			info.push_back(tmp._rect.left - player._rect.left);
			info.push_back(tmp.height);
		}

		info.push_back(player._rect.top);
		info.push_back(1);

		vector<double> output = perceptron.output(info);

		cout.setf(ios::fixed);
		cout.precision(20);

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			player.dy = -0.5;
			vector<vector<double>> infoEd;
			info.push_back(1);
			infoEd.push_back(info);
			for (size_t i = 0; i < 10; i++)
			{
				perceptron.simpleEducation(infoEd);
			}	
		}
		else {
			vector<vector<double>> infoEd;
			info.push_back(0.15);
			infoEd.push_back(info);
			perceptron.simpleEducation(infoEd);
		}
		player.update(time);

		bool lose = false;
		vector<double> eduData;
		for (size_t i = 0; i < objectsQueue.size(); i++)
		{
			GameObject tmp = objectsQueue.front();
			objectsQueue.pop();
			tmp.update(time);
			window.draw(tmp._sprite);
			objectsQueue.push(tmp);
			eduData.push_back(tmp._rect.left);
			eduData.push_back(tmp._rect.top);
			if ((abs(player._rect.left - tmp._rect.left) < 50) && (abs(player._rect.top - 470 - tmp.height) > 100)) //&& 
			{
				lose = true;
			}
		}
		
		if (lose)
		{
			return score;
		}

		window.draw(player._sprite);
		window.display();
	}
}

int gameSessionWithPerceptron(Sprite& bird, Sprite& spriteBackground, Sprite& spriteLowerWall, Sprite& spriteUpperWall, RenderWindow& window, Perceptron& perceptron) {
	GameObject player(bird, FloatRect(70, 484, 17, 12));
	Clock timer;
	float time;
	int score = 0;
	queue<GameObject> objectsQueue;

	for (size_t i = 0; i < 4; i++)
	{
		int height = rand() % 150 - 75;
		GameObject upperWall(spriteUpperWall, FloatRect(i * 150 + 200, -100 + height, 26, 160));
		GameObject lowerWall(spriteLowerWall, FloatRect(i * 150 + 200, 600 + height, 26, 160));
		lowerWall.gravitation = 0;
		upperWall.gravitation = 0;
		lowerWall.dx = -0.5;
		upperWall.dx = -0.5;
		lowerWall.height = height;
		upperWall.height = height;

		objectsQueue.push(lowerWall);
		objectsQueue.push(upperWall);
	}

	while (window.isOpen())
	{
		window.draw(spriteBackground);
		time = timer.getElapsedTime().asMicroseconds();
		timer.restart();
		time /= 2000;

		if (objectsQueue.front()._rect.left < -100)
		{
			int height = rand() % 150 - 75;
			GameObject newUpperWall(spriteUpperWall, FloatRect(500, -100 + height, 26, 160));
			GameObject newLowerWall(spriteLowerWall, FloatRect(500, 600 + height, 26, 160));
			newUpperWall.gravitation = 0;
			newLowerWall.gravitation = 0;
			newUpperWall.dx = -0.5;
			newLowerWall.dx = -0.5;
			newLowerWall.height = height;
			newUpperWall.height = height;
			objectsQueue.pop();
			objectsQueue.pop();
			objectsQueue.push(newUpperWall);
			objectsQueue.push(newLowerWall);
			score++;
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		vector<double> info;

		queue<GameObject> tmpObjectsQueue(objectsQueue);
		GameObject tmp = tmpObjectsQueue.front();
		if (tmp._rect.left - player._rect.left > 0)
		{
			info.push_back(tmp._rect.left - player._rect.left);
			info.push_back(tmp.height);
		}
		else {
			tmpObjectsQueue.pop();
			tmpObjectsQueue.pop();
			tmp = tmpObjectsQueue.front();
			info.push_back(tmp._rect.left - player._rect.left);
			info.push_back(tmp.height);
		}


		info.push_back(player._rect.top);
		info.push_back(1);

		vector<double> output = perceptron.output(info);

		if (output[0] >= 0.5)
		{
			player.dy = -0.5;
		}
		player.update(time);

		bool lose = false;
		bool top;
		vector<double> eduData;
		for (size_t i = 0; i < objectsQueue.size(); i++)
		{
			GameObject tmp = objectsQueue.front();
			objectsQueue.pop();
			tmp.update(time);
			window.draw(tmp._sprite);
			objectsQueue.push(tmp);
			eduData.push_back(tmp._rect.left);
			eduData.push_back(tmp._rect.top);
			if ((abs(player._rect.left - tmp._rect.left) < 50) && (abs(player._rect.top - 470 - tmp.height) > 100)) //&& 
			{
				if (player._rect.top - 470 - tmp.height > 0)
				{
					top = false;
				}
				else top = true;
				lose = true;
			}
		}
		cout.setf(ios::fixed);
		cout.precision(20);
		cout << output[0] << endl;
		if (lose)
		{
			eduData.push_back(player._rect.left);
			eduData.push_back(player._rect.top);
			if (score < 1)
			{
				score = 1;
			}
			if (top)
			{
				info.push_back(0.5 - 0.5/score);
			}
			info.push_back(0.5 + 0.5 / score);
			vector<vector<double>> edu;
			edu.push_back(info);
			perceptron.simpleEducation(edu);


			return score;
		}
		window.draw(player._sprite);
		window.display();
	}
}

int main()
{
	Texture textureBackground;
	textureBackground.loadFromFile("..\\sprite.png", IntRect(0, 0, 144, 256));
	Sprite spriteBackground(textureBackground);
	spriteBackground.setScale(3, 3);
	Texture textureBird;
	textureBird.loadFromFile("..\\sprite.png", IntRect(3, 491, 17, 12));
	Sprite bird(textureBird);
	bird.setScale(3, 3);
	Texture textureUpperWall, textureLowerWall;
	textureUpperWall.loadFromFile("..\\sprite.png", IntRect(56, 323, 26, 160));
	textureLowerWall.loadFromFile("..\\sprite.png", IntRect(84, 323, 26, 160));
	Sprite spriteUpperWall(textureUpperWall), spriteLowerWall(textureLowerWall);
	spriteUpperWall.setScale(3, 3);
	spriteLowerWall.setScale(3, 3);

	Perceptron perc(Perceptron::_10_8_6);
	bool exit = false;
	while (!exit)
	{
		system("cls");
		int choise = 0;
		cout << "Hello, I'm an artificial intelligence learning to play a game of Flappy Bird!\n";
		cout << "1. Pick my neuron configuration\n";
		cout << "2. Set learning rate\n";
		cout << "3. Start 10 game sessions\n";
		cout << "4. Start 100 game sessions\n";
		cout << "5. Start 1000 game sessions\n";
		cout << "6. Set a score to strive for (I will learn until I reach it)\n";
		cout << "7. About\n";
		cout << "8. Exit\n";
		cin >> choise;
		switch (choise)
		{
		case 1:
			system("cls");
			cout << "Neuron configuration is a combination of the number of neurons per layer. Select:\n";
			cout << "1. 1 layer with 3 neurons\n";
			cout << "2. 1 layer with 5 neurons\n";
			cout << "3. 1 layer with 10 neurons\n";
			cout << "4. 2 layers. 1st: 3 neurons; 2nd: 3 neurons\n";
			cout << "5. 2 layers. 1st: 3 neurons; 2nd: 5 neurons\n";
			cout << "6. 3 layers. 1st: 5 neurons; 2nd: 5 neurons; 3d: 5 neurons\n";
			cout << "7. 3 layers. 1st: 10 neurons; 2nd: 8 neurons; 3d: 6 neurons\n";
			cout << "8. 3 layers. 1st: 10 neurons; 2nd: 10 neurons; 3d: 10 neurons\n";
			cin >> choise;
			switch (choise)
			{
			case 1:
				perc.setLayersType(Perceptron::_3);
				break;
			case 2:
				perc.setLayersType(Perceptron::_5);
				break;
			case 3:
				perc.setLayersType(Perceptron::_10);
				break;
			case 4:
				perc.setLayersType(Perceptron::_3_3);
				break;
			case 5:
				perc.setLayersType(Perceptron::_3_5);
				break;
			case 6:
				perc.setLayersType(Perceptron::_5_5_5);
				break;
			case 7:
				perc.setLayersType(Perceptron::_10_8_6);
				break;
			case 8:
				perc.setLayersType(Perceptron::_10_10_10);
				break;
			default:
				break;
			}
			// можно добавить с любым количеством слоев, но без сохранения
			break;
		case 2:
		{
			system("cls");
			bool correct = false;
			while (!correct)
			{
				double rate;
				cout << "Learning rate is my learning level. The closer it is to 0, the more accurately but \nmore slowly I learn, and vice versa, the closer it is to 1, the faster I learn, but not\nnecessarily correctly. \nEnter(0 <= x <= 1 ): ";
				cin >> rate;
				if (rate >= 0 && rate <= 1)
				{
					perc.setLearningRate(rate);
					correct = true;
				}
			}
			break;
		}
		case 3:
		{
			RenderWindow window(VideoMode(432, 768), "Flappy");
			int maxscore = 1;
			perc.loadFromFile();
			for (size_t i = 0; i < 10; i++)
			{
				int score = gameSessionWithPerceptron(bird, spriteBackground, spriteLowerWall, spriteUpperWall, window, perc);
				if (score > maxscore)
				{
					perc.saveToFile();
					maxscore = score;
				}
			}
			break;
		}
		case 4:
		{
			RenderWindow window(VideoMode(432, 768), "Flappy");
			int maxscore = 1;
			perc.loadFromFile();
			for (size_t i = 0; i < 100; i++)
			{
				int score = gameSessionWithPerceptron(bird, spriteBackground, spriteLowerWall, spriteUpperWall, window, perc);
				if (score > maxscore)
				{
					perc.saveToFile();
					maxscore = score;
				}
			}
			break;
		}
		case 5:
		{
			RenderWindow window(VideoMode(432, 768), "Flappy");
			int maxscore = 1;
			perc.loadFromFile();
			for (size_t i = 0; i < 1000; i++)
			{
				int score = gameSessionWithPerceptron(bird, spriteBackground, spriteLowerWall, spriteUpperWall, window, perc);
				if (score > maxscore)
				{
					perc.saveToFile();
					maxscore = score;
				}
			}
			break;
		}
		case 6:
		{
			system("cls");
			unsigned maxScoreLimit;
			cout << "Enter score to reach: ";
			cin >> maxScoreLimit;
			RenderWindow window(VideoMode(432, 768), "Flappy");
			int maxscore = 0;
			perc.loadFromFile();
			while(maxscore < maxScoreLimit)
			{
				int score = gameSessionWithPerceptron(bird, spriteBackground, spriteLowerWall, spriteUpperWall, window, perc);
				if (score > maxscore)
				{
					perc.saveToFile();
					maxscore = score;
				}
			}
			break;
		}
		case 7:
			system("cls");
			cout << "About the project:\n";
			cout << " - This is a project to improve understanding of the workings of rudimentary artificial intelligence.\n";
			cout << " - The user can try out different types of layering in the AI and its abilities by playing Flappt Bird as an example\n";
			cout << " - The user can look at the success rate of the AI and understand the implications of improving its accuracy\n";
			cout << " - The user can simply enjoy a thousand AI failures on the road to perfection\n\n";
			cout << "About me:\n";
			cout << "   I am Dmytro Seliutin, a first-year student at KPI University. Also I am Junior Frontend Developer. My github:\n\n";
			cout << "\thttps://github.com/diselyuti\n\n\n";
			system("pause");
			break;
		case 8:
			exit = true;
			break;
		}
	}
	return 0;
}