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
	int max_health;
	int heal_uses = 3;
	bool is_dodging;
	

public:
	Player(std::string name, int hp, int atk)
		: name(name), health(hp),max_health(hp), attack_power(atk) {}

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
		if (this->is_dodging)
		{
			/*std::cout << name << " dodged the attack!\n";*/ //ovo je neka graska bila
			this->is_dodging = false;
			return;
		}
		this->health -= dmg;
		if (health < 0) health = 0;

	}

	void dodge()
	{
		this->is_dodging = true;
		std::cout << name << " is preparing to dodge the next attack!\n";
	}

	void heal()
	{
		if (heal_uses <= 0) {
			std::cout << name << " tried to heal, but has no heals left!\n";
			return;
		}

		int old_health = health;

		this->health += 20;
		if (this->health > max_health)
			this->health = max_health;

		heal_uses--; // ovde oduzima heath uses da ne moze non stop.
		std::cout << name << " healed himself\n";

	}

	// metoda da li je neko mrtav xD
	bool is_dead() const
	{
		return this->health <= 0;
	}

	// ispisuje ko koliko ima hp
	void print_status()
	{
		std::cout << name << " Has " << health << " HP\n";
	}

	// radim geter jer je "name" privated
	std::string get_name() const
	{
		return this->name;
	}

	int get_health() const {
		return health;
	}

	int get_heal_uses() const
	{
		return heal_uses;
	}

};

int main()
{
	srand(static_cast<unsigned int>(time(0))); // seed za rand() Misli da moze i drugacije da se uradi random num tj slucajni broj

	// Kreiram objekat
	Player player1("Zlatan", 100, 25);
	Player player2("Goblin", 50, 20);


	int round = 1;

	while (1) {

		std::cout << "\n----- Round " << round++ << " -----\n";
		if(!player1.is_dead())
		{

			int test;

			std::cout << "Choose: 1 to attack, 2 to dodge, 3 to heal" << std::endl;
			std::cin >> test;
			std::cout << player1.get_name() << " chose: " << test << '\n';
			switch (test)
			{
			case 1:
				player1.attack(player2);
				player2.print_status();
				break;
			case 2 :
				player1.dodge();
				break;
			case 3 :
				player1.heal();
				std::cout << "Remaining heals: " << player1.get_heal_uses() << "\n";
				break;
			}
		}
		else 
		{
			
			break;
		}

		if (!player2.is_dead())
		{
			int action = rand() % 3 + 1; // 1,2,3

			switch (action)
			{
			case 1:
				player2.attack(player1);
				break;
			case 2:
				player2.dodge();
				break;
			case 3:
				if (player2.get_heal_uses() > 0 && player2.get_health() < 50) {
					player2.heal();
					std::cout << "Goblin has " << player2.get_heal_uses() << " heals left.\n";
				}
				else {
					std::cout << "Goblin tried to heal, but couldn’t, so he attacks!\n";
					player2.attack(player1);
				}
				break;
			}

			player1.print_status();
		}
		else
		{
			break;
		}

		if (player1.is_dead())
		{
			break;
		}
	}

	std::cout << "\n---- END GAME!!! ----\n";
	if (player1.is_dead())
		std::cout << player2.get_name() << " IS THE  WINNER!!\n";
	else
		std::cout << player1.get_name() << " IS THE  WINNER!!\n";



}