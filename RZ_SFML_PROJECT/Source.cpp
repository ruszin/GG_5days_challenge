#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SDitems.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include "MainMission.h"
using namespace sf;
class Bullets {
public:
	sf::Image bullet_image,bullet_tank_image;
	sf::Texture bullet_texture,bullet_tank_texture;
	sf::Sprite bullet_sprite,bullet_tank_sprite;
	bool shot_bullet = 0;
	bool average_bullet = 0;
};
class Player {
public:
	///////////отрефакторить по битам в возрастании
	float health_player=800;
	bool life_player;
	int points_game = 0;
	float damage_player = 3;
	bool asteroid_gg = 0;
};
class Enemy {
public:
	sf::Image enemy_tank_image;
	sf::Texture enemy_tank_texture;
	sf::Sprite enemy_tank_sprite;
	bool spawnEnemy = true;
	float health_enemy_tank = 1000;
	float damage_enemy_tank =3;
	bool enemyMove = true;
	bool enemyShot = false;
};
class TexturePack {
public:
	bool AppearExplosion=true;
	int GetRandomNum()  {
		return std::rand() % 7 + 0;
	}
	double GetRandomPosAsteroids() {
		return double(std::rand()%950+100);
	}
	std::string GetRandomAsteroidsID() {
		std::string s = "";
		switch (GetRandomNum()) {
		case 0:
			s = "sprites/asteroid_copy_0.png";
			break;
		case 1:
			s= "sprites/asteroid_copy_1.png";
			break;
		case 2:
			s = "sprites/asteroid_copy_2.png";
			break;
		case 3:
			s = "sprites/asteroid_copy_3.png";
			break;
		case 4:
			s = "sprites/asteroid_copy_4.png";
			break;
		case 5:
			s = "sprites/asteroid_copy_5.png";
			break;
		case 6:
			s = "sprites/asteroid_copy_6.png";
			break;
		case 7:
			s = "sprites/asteroid_copy_7.png";
			break;
		}
		return s;
	}
	double GetRandomSpeedAsteroids() {
		return rand() % 7+0;
	}
	
};

//void menu(RenderWindow & window) {
//	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
//	menuTexture1.loadFromFile("D://SFML_TEST_PROJ/sprites/new_game.jpg");
//	menuTexture2.loadFromFile("D://SFML_TEST_PROJ/sprites/exit_game.jpg");
//	menuBackground.loadFromFile("D://SFML_TEST_PROJ/sprites/menu_background.jpg");
//	Sprite menu1(menuTexture1),menu2(menuTexture2),menuBg(menuBackground);
//	bool isMenu = 1;
//	int menuNum = 0;
//	menu1.setPosition(100, 30);
//	menu2.setPosition(100, 500);
//	menuBg.setPosition(0, 0);
//	while (isMenu)
//	{
//		menu1.setColor(Color::White);
//		menu2.setColor(Color::White);
//		menuNum = 0;
//		window.clear(Color(129, 181, 221));
//		if (IntRect(100, 30, 30, 150).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
//		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
//		if (Mouse::isButtonPressed(Mouse::Left))
//		{
//			if (menuNum == 1) isMenu = false;
//			if (menuNum == 2) { window.close(); isMenu = false; }
//		}
//		window.draw(menuBg);
//		window.draw(menu1);
//		window.draw(menu2);
//		window.display();
//	}
//	////////////////////////////////////////////////////
//}
int main()
{
	sf::RenderWindow window(sf::VideoMode(1920,1080),"Galaxy Guard");
	//menu(window);
	srand(time(NULL));
	Image gg_image; Texture gg_texture; Sprite gg_sprite;
	SDitems sd_it; Player person; Enemy enemy; Bullets bullet;
	///////////////////////////////
	sf::Music music;
	music.openFromFile("background_music.ogg");
	music.play();
	music.setVolume(20);
	sf::SoundBuffer buffer, buffer_enemy;
	buffer.loadFromFile("shoot_gg.ogg");
	buffer_enemy.loadFromFile("shoot_enemy.wav");
	sf::Sound sound, sound_enemy;
	sound.setBuffer(buffer);
	sound_enemy.setBuffer(buffer_enemy);
	sound_enemy.setVolume(20);
	sound.setVolume(20);
	///////////////////////////////
	Image gg_explosion_image; Texture gg_explosion_texture; Sprite gg_explosion_sprite;
	gg_explosion_image.loadFromFile("sprites/explosion.png");
	gg_explosion_texture.loadFromImage(gg_explosion_image);
	gg_explosion_sprite.setTexture(gg_explosion_texture);
	//////////////////////////////
	enemy.enemy_tank_image.loadFromFile("sprites/enemy_ship_tank.png");
	enemy.enemy_tank_texture.loadFromImage(enemy.enemy_tank_image);
	enemy.enemy_tank_sprite.setTexture(enemy.enemy_tank_texture);
	/////////////////////////////
	bullet.bullet_image.loadFromFile("sprites/shot.png");
	bullet.bullet_texture.loadFromImage(bullet.bullet_image);
	bullet.bullet_sprite.setTexture(bullet.bullet_texture);
	///////////////////////////////
	Image gg_explosion_tank_image; Texture gg_explosion_tank_texture; Sprite gg_explosion_tank_sprite;
	gg_explosion_tank_image.loadFromFile("sprites/shot_exp.png");
	gg_explosion_tank_texture.loadFromImage(gg_explosion_tank_image);
	gg_explosion_tank_sprite.setTexture(gg_explosion_tank_texture);
	///////////////////////////////
	bullet.bullet_tank_image.loadFromFile("sprites/shot_tank.png");
	bullet.bullet_tank_texture.loadFromImage(bullet.bullet_tank_image);
	bullet.bullet_tank_sprite.setTexture(bullet.bullet_tank_texture);
	///////////////////////////////
	Font fontEN;
	fontEN.loadFromFile("CyrilicOld.ttf");
	Text textEN("", fontEN, 30); Text textHP("", fontEN, 30);
	textEN.setFillColor(Color::Green); textHP.setFillColor(Color::Red);
	textEN.setStyle(Text::Bold); textHP.setStyle(Text::Bold);
	Text textMission("", fontEN, 30);
	textMission.setFillColor(Color::Red);
	Text textHP_Enemy("",fontEN,30);
	textHP_Enemy.setFillColor(Color::Red);
	textHP_Enemy.setStyle(Text::Bold);
	///////////////////////////////
	Image background_space_image; Texture background_space_texture; Sprite background_space_sprite;
	background_space_image.loadFromFile("sprites/background_space.jpg");
	background_space_texture.loadFromImage(background_space_image);
	background_space_sprite.setTexture(background_space_texture);
	background_space_sprite.setPosition(0, 0);
	///////////////////////////////
	gg_image.loadFromFile("sprites/GG_person_test.png");
	gg_texture.loadFromImage(gg_image);
	gg_sprite.setTexture(gg_texture);
	gg_sprite.setPosition(20, 500);
	///////////////////////////////
	Image asteroid_image; Texture asteroid_texture; Sprite asteroid_sprite;
	Image asteroid_image2; Texture asteroid_texture2; Sprite asteroid_sprite2;
	Image asteroid_image3; Texture asteroid_texture3; Sprite asteroid_sprite3;
	TexturePack mainObject;
	/////////////////////////////
	asteroid_image.loadFromFile(mainObject.GetRandomAsteroidsID());
	asteroid_texture.loadFromImage(asteroid_image);
	asteroid_sprite.setTexture(asteroid_texture);
	asteroid_sprite.setPosition(1900,500);
	////////////////////////////
	asteroid_image2.loadFromFile(mainObject.GetRandomAsteroidsID());
	asteroid_texture2.loadFromImage(asteroid_image2);
	asteroid_sprite2.setTexture(asteroid_texture2);
	asteroid_sprite2.setPosition(2200, 300);
	///////////////////////////
	asteroid_image3.loadFromFile(mainObject.GetRandomAsteroidsID());
	asteroid_texture3.loadFromImage(asteroid_image3);
	asteroid_sprite3.setTexture(asteroid_texture3);
	asteroid_sprite3.setPosition(2000, 900);
	/////////////////////////////
	float x_enemy, y_enemy, x_bullet, y_bullet, x_gg, y_gg, x_bullet_tank, y_bullet_tank;
	/////////////////////////////
	bullet.bullet_tank_sprite.setPosition(enemy.enemy_tank_sprite.getPosition().x-20, enemy.enemy_tank_sprite.getPosition().y+35);
	////////////////////////////
	Clock clock;
	bool TruePosMission = 1;
	while (window.isOpen())
	{
		double time_binding = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time_binding /= sd_it.time_const;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {
if ((event.key.code == Keyboard::Tab)) {


	switch (TruePosMission) {

	case true: {
		TruePosMission = false;
		textMission.setString(GetCurrentMission());
		textMission.setPosition(10, 45);
		break;
	}
	case false: {
		textMission.setString("");
		TruePosMission = true;
		break;
	}
	}
}
			}
		}
		////////////////////////
		if (music.getStatus() == false) {
			music.play();
		}
		/////////////////////////
		person.asteroid_gg = false;
		bullet.average_bullet = false;
		enemy.enemyShot = false;
		/////////////////////////
		x_enemy = enemy.enemy_tank_sprite.getPosition().x; y_enemy = enemy.enemy_tank_sprite.getPosition().y;
		x_bullet = bullet.bullet_sprite.getPosition().x; y_bullet = bullet.bullet_sprite.getPosition().y;
		x_gg = gg_sprite.getPosition().x; y_gg = gg_sprite.getPosition().y;
		x_bullet_tank = bullet.bullet_tank_sprite.getPosition().x; y_bullet_tank = bullet.bullet_tank_sprite.getPosition().y;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !bullet.shot_bullet)
		{
			sound.play();
			bullet.shot_bullet = true;
			bullet.bullet_sprite.setPosition(gg_sprite.getPosition().x + sd_it.center_gg_sprite_x, gg_sprite.getPosition().y + sd_it.center_gg_sprite_y);
		}
		if (bullet.bullet_sprite.getPosition().x > 1920) {
			bullet.shot_bullet = false;
		}
		///////////////////////
		if (x_bullet_tank < -300 ) {
			sound_enemy.play();
			bullet.bullet_tank_sprite.setPosition(x_enemy - 20, y_enemy + 35);
		}
		bullet.bullet_tank_sprite.move(sd_it.speed_bullet_enemy*time_binding, 0);
		///enemy px 364*198
		if (x_bullet < x_enemy + 150 && x_bullet >= x_enemy + 60 && y_bullet <= y_enemy + 120 && y_bullet >= y_enemy - 20 && bullet.shot_bullet) {
			bullet.average_bullet = true;
		}
		////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && gg_sprite.getPosition().y > 0) {
			gg_sprite.move(0, -sd_it.speed_gg_ort*time_binding);
		}
		if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && gg_sprite.getPosition().y < 840) {
			gg_sprite.move(0, sd_it.speed_gg_ort*time_binding);
		}
		if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && gg_sprite.getPosition().x > 0) {
			gg_sprite.move(-sd_it.speed_gg_ort*time_binding, 0);
		}
		if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && gg_sprite.getPosition().x < 1400) {
			gg_sprite.move(sd_it.speed_gg_ort*time_binding, 0);
		}
		////////
		asteroid_image.loadFromFile(mainObject.GetRandomAsteroidsID());
		////////
		if (asteroid_sprite.getPosition().x < sd_it.updatePos_asteroids) {
			asteroid_sprite.setPosition(1900, mainObject.GetRandomPosAsteroids());
		}
		if (asteroid_sprite2.getPosition().x < sd_it.updatePos_asteroids) {
			asteroid_sprite2.setPosition(1900, mainObject.GetRandomPosAsteroids());
		}
		if (asteroid_sprite3.getPosition().x < sd_it.updatePos_asteroids) {
			asteroid_sprite3.setPosition(1900, mainObject.GetRandomPosAsteroids());
		}
		//////////////////////////////////////////////////////////////////////////
		if (person.points_game >= 0 && enemy.spawnEnemy) {
			enemy.enemy_tank_sprite.setPosition(1540, 60);
			enemy.spawnEnemy = false;
		}
		if (enemy.enemy_tank_sprite.getPosition().y < 10 || enemy.enemyMove) {
			enemy.enemyMove = true;
			enemy.enemy_tank_sprite.move(0, sd_it.speed_enemy*time_binding);
		}
		if (enemy.enemy_tank_sprite.getPosition().y > 800 || enemy.enemyMove == false) {
			enemy.enemyMove = false;
			enemy.enemy_tank_sprite.move(0, -sd_it.speed_enemy*time_binding);
		}
		//////////////////////////////////////////////////////////////////////////
		if (gg_sprite.getPosition().x < asteroid_sprite.getPosition().x + 30 && gg_sprite.getPosition().x < asteroid_sprite.getPosition().x + 30 && gg_sprite.getPosition().x<asteroid_sprite.getPosition().x + 30 && gg_sprite.getPosition().x>asteroid_sprite.getPosition().x - 30 && gg_sprite.getPosition().x < asteroid_sprite.getPosition().x + 30 && gg_sprite.getPosition().y < asteroid_sprite.getPosition().y + 30 && gg_sprite.getPosition().x<asteroid_sprite.getPosition().x + 30 && gg_sprite.getPosition().y>asteroid_sprite.getPosition().y - 30) {
			person.health_player -= 1;
			person.asteroid_gg = true;
		}
		if (gg_sprite.getPosition().x < asteroid_sprite2.getPosition().x + 30 && gg_sprite.getPosition().x < asteroid_sprite2.getPosition().x + 30 && gg_sprite.getPosition().x<asteroid_sprite2.getPosition().x + 30 && gg_sprite.getPosition().x>asteroid_sprite2.getPosition().x - 30 && gg_sprite.getPosition().x < asteroid_sprite2.getPosition().x + 30 && gg_sprite.getPosition().y < asteroid_sprite2.getPosition().y + 30 && gg_sprite.getPosition().x<asteroid_sprite2.getPosition().x + 30 && gg_sprite.getPosition().y>asteroid_sprite2.getPosition().y - 30) {
			person.health_player -= 1;
			person.asteroid_gg = true;
		}
		if (gg_sprite.getPosition().x < asteroid_sprite3.getPosition().x + 30 && gg_sprite.getPosition().x < asteroid_sprite3.getPosition().x + 30 && gg_sprite.getPosition().x<asteroid_sprite3.getPosition().x + 30 && gg_sprite.getPosition().x>asteroid_sprite3.getPosition().x - 30 && gg_sprite.getPosition().x < asteroid_sprite3.getPosition().x + 30 && gg_sprite.getPosition().y < asteroid_sprite3.getPosition().y + 30 && gg_sprite.getPosition().x<asteroid_sprite3.getPosition().x + 30 && gg_sprite.getPosition().y>asteroid_sprite3.getPosition().y - 30) {
			person.health_player -= 1;
			person.asteroid_gg = true;
		}
		if(bullet.bullet_tank_sprite.getPosition().x < gg_sprite.getPosition().x +150  &&  bullet.bullet_tank_sprite.getPosition().x >= gg_sprite.getPosition().x+30 && bullet.bullet_tank_sprite.getPosition().y >= gg_sprite.getPosition().y+10 && bullet.bullet_tank_sprite.getPosition().y < gg_sprite.getPosition().y+80){
			person.health_player -= 100;
			enemy.enemyShot = true;
		}
		////251x168 px gg_person size
		////120*90 px asteroid size
		/////////////////////////////////////////////////////////////////////////
		asteroid_sprite.move(sd_it.speed_asteroid_1, 0);
		asteroid_sprite2.move(sd_it.speed_asteroid_2, 0);
		asteroid_sprite3.move(sd_it.speed_asteroid_3, 0);
		////////
		std::ostringstream playerPoints;
		std::ostringstream playerHp;
		std::ostringstream enemyHP;
		playerPoints << person.points_game;
		textEN.setString("CURRENT POINTS: " + playerPoints.str());
		textEN.setPosition(10, 0);
		playerHp << person.health_player;
		textHP.setString("Your HP: " + playerHp.str());
		textHP.setPosition(400, 0);
		enemyHP << enemy.health_enemy_tank;
		textHP_Enemy.setString("Boss HP: " + enemyHP.str());
		textHP_Enemy.setPosition(640, 0);
		//////////
		window.clear();
		window.draw(background_space_sprite);
		window.draw(gg_sprite);
		window.draw(enemy.enemy_tank_sprite);
		window.draw(asteroid_sprite);
		window.draw(asteroid_sprite2);
		window.draw(asteroid_sprite3);
		window.draw(textEN);
		window.draw(textHP);
		window.draw(textHP_Enemy);
		if (person.asteroid_gg) {
			gg_explosion_sprite.setPosition(gg_sprite.getPosition().x, gg_sprite.getPosition().y);
			window.draw(gg_explosion_sprite);
		}
		if (!TruePosMission) {
			window.draw(textMission);
		}
		if (bullet.shot_bullet) {
			bullet.bullet_sprite.move(sd_it.speed_bullet_gg*time_binding,0);
			window.draw(bullet.bullet_sprite);
		}
		if (bullet.average_bullet) {
			person.points_game += 100;
			enemy.health_enemy_tank -= person.damage_player;
			gg_explosion_sprite.setPosition(bullet.bullet_sprite.getPosition().x, bullet.bullet_sprite.getPosition().y);
			window.draw(gg_explosion_sprite);
		}
		window.draw(bullet.bullet_tank_sprite);
		if (enemy.health_enemy_tank <= 0 || person.health_player <= 0) {
			window.close();
		}
		if (enemy.enemyShot) {
			gg_explosion_tank_sprite.setPosition(bullet.bullet_tank_sprite.getPosition().x, bullet.bullet_tank_sprite.getPosition().y);
			window.draw(gg_explosion_tank_sprite);
			bullet.bullet_tank_sprite.setPosition(x_enemy - 20, y_enemy + 35);
		}
		window.display();
	}
	return 0;
}