#pragma once
#include "CirclePointObj.h"
#include "Order.h"
#include "GameObject.h"

class StatsBonusEffect;

class Unit : virtual public CirclePointObj, virtual public GameObject
{
public:
	Unit(int army, float radius);
	Unit(int army);
	virtual ~Unit();
	void update(int time);
	void changeAttitude(char newAttitude);
	void takeDamage(int damage, Unit* enemy);
	void setHealth(int newHealthVal);
	void createNewMove(sf::Vector2f mousePos);
	void createNewMoveTo(Unit& target);
	void createNewAttack(Unit& target);
	void createNewStay();	
	void createNewKnockdown(Unit& target);
	void createNewJumpAway(Unit* enemy, int damage);
	bool checkCollision(Unit& other);
	void addToFightList(Unit* enemy);
	void removeFromFightList(Unit* enemy);
	void clearOrders();

	sf::Sprite 
		attitudeIcon,
		unitSprite;

	int
		army,
		morale,
		health,

		attack,
		defense,
		dodges,
		strongAttack,
		attackSpeed;


	bool
		cooldownFlag,
		displayInterface, //temporary!
		ai;
	char 
		attitude;	
	float 
		moveSpeed;
	std::list<Order*> 
		orders;

protected: 
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void constructor();
	void executeMove(int time);
	void executeMoveTo(int time);
	void executeAttack(int time);
	void executeJumpAway(int time);
	void executeKnockdown(int time);
	void moveAnimationUpdate(int time);
	
	void deleteCurrOrder();
	void moveAroundObstacle(const sf::Vector2f& obstPos, const sf::Vector2f& targetPos, int time);
	void setAnimationFrame(int frameNr);

	sf::RectangleShape moveLine;
	sf::Font font;
	sf::Text
		healthTxt,
		moraleTxt,
		blockCooldownTxt,
		attackCooldownTxt,
		defenseTxt;
	StatsBonusEffect* statsEffect;
	std::list <Unit*> fightList; //list of enemies fighting with this unit
	int
		animationCounter,
		animationTimeCounter,
		attackCld,
		attitudeChangeCld,
		aiAttitudeChangeCld;

	const static int ATTITUDE_CHANGE_TIME;
	const static int AI_ATTITUDE_CHANGE_TIME;
};

struct BaseStats {
	static const int TURN_TIME = 2000;

	static const int Q_ATTACK = 2;
	static const int Q_DEFENSE = 5;
	static const int Q_DODGES = 0;
	static const int Q_STRONG_ATTACK = 0;
	static const int Q_ATTACK_SPEED = 1000;

	static const int W_ATTACK = 3;
	static const int W_DEFENSE = 4;
	static const int W_DODGES = 3;
	static const int W_STRONG_ATTACK = 0;
	static const int W_ATTACK_SPEED = 1000;

	static const int E_ATTACK = 5;
	static const int E_DEFENSE = 2;
	static const int E_DODGES = 1;
	static const int E_STRONG_ATTACK = 2;
	static const int E_ATTACK_SPEED = 800;

	static void setParams(Unit* const unit , char attitude) {
		if (attitude == 'Q') {
			unit->attack = Q_ATTACK;
			unit->defense = Q_DEFENSE;
			unit->dodges = Q_DODGES;
			unit->strongAttack = Q_STRONG_ATTACK;
			unit->attackSpeed = Q_ATTACK_SPEED;
		}
		else if (attitude == 'W') {
			unit->attack = W_ATTACK;
			unit->defense = W_DEFENSE;
			unit->dodges = W_DODGES;
			unit->strongAttack = W_STRONG_ATTACK;
			unit->attackSpeed = W_ATTACK_SPEED;
		}
		if (attitude == 'E') {
			unit->attack = E_ATTACK;
			unit->defense = E_DEFENSE;
			unit->dodges = E_DODGES;
			unit->strongAttack = E_STRONG_ATTACK;
			unit->attackSpeed = E_ATTACK_SPEED;
		}
	}

};