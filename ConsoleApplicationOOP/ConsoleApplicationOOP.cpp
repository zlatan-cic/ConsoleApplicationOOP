#include <iostream>  
#include <string>    
#include <cstdlib>   
#include <ctime>     


class Player {
private:
	// atributi
	std::string name;
	int health;
	int attack_power;

public:
	Player(std::string name, int hp, int atk)
		: name(name), health(hp), attack_power(atk) {}

	/*
	*	ATTACK function
	*/
	void attack(Player& target)
	{
		// Nasumicno generise broj između 1 i attack_power kao količinu štete - @var damage
		int damage = rand() % attack_power + 1;
		std::cout << name << " Attack " << target.name << " hit by " << damage << " dmg!\n";

		target.take_damage(damage);
	}

	/*
	*  funkcija take damage
	*/
	void take_damage(int dmg)
	{
		health -= dmg;
		if (health < 0) health = 0;
	}

	// metoda da li je neko mrtav xD
	bool is_dead() const
	{
		return health <= 0;
	}

	// ispisuje ko koliko ima hp
	void print_status()
	{
		std::cout << name << " Has " << health << " HP\n";
	}

	// radim geter jer je "name" privated
	std::string get_name() const
	{
		return name;
	}

};

int main()
{
	srand(static_cast<unsigned int>(time(0))); // seed za rand() Misli da moze i drugacije da se uradi random num tj slucajni broj

	//Player player0("Zlatan", 100, 20);
	// Kreiram objekat
	Player player1("Zlatan", 100, 20);
	Player player2("Goblin", 100, 15);


	int round = 1;
	while (!player1.is_dead() && !player2.is_dead())
	{
		std::cout << "\n----- Round " << round++ << " -----\n";
		player1.attack(player2);
		player2.print_status();

		if (player2.is_dead()) break; /// ovo mi je trebalo malo bolje da razmislim jer ako goblin ima 0 hp on moze opet da me napadne xD

		player2.attack(player1);
		player1.print_status();
	}

	std::cout << "\n---- END GAME!!! ----\n";
	if (player1.is_dead())
		std::cout << player2.get_name() << " IS WINNER!!\n";
	else
		std::cout << player1.get_name() << " IS WINNER!!\n";



}