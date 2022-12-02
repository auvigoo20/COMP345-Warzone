#include "PlayerStrategies.h"


// Human Player Strategy

// Constructors

HumanPlayerStrategy::HumanPlayerStrategy()
{
    this->player = nullptr;
}


HumanPlayerStrategy::HumanPlayerStrategy(Player *player)
{
   this->player = player;
}

/**
 * Copy constructor
 * @param s Strategy to copy
 */
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy &s)
{
    this->player = s.player;
}

// Destructor
HumanPlayerStrategy::~HumanPlayerStrategy()
{
}

/**
 * Assignment Operator
 * @param s
 * @return
 */
HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& s) {
    if(this != &s) {
        this->player = s.player;
    }
    return *this;
}

ostream& operator<<(ostream& output, HumanPlayerStrategy& s)
{
    output << "Human Player Strategy" << endl;
}


// Getters and setters

Player* HumanPlayerStrategy::getPlayer()
{
    return this->player;
}


void HumanPlayerStrategy::setPlayer(Player *player)
{
    this->player = player;
}


// Aggressive Player Strategy


// Constructors

AggressivePlayerStrategy::AggressivePlayerStrategy()
{
    this->player = nullptr;
}


AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player)
{
    this->player = player;
}

/**
 * Copy constructor
 * @param s Strategy to copy
 */
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy &s)
{
    this->player = s.player;
}

// Destructor
AggressivePlayerStrategy::~AggressivePlayerStrategy()
{
}

/**
 * Assignment Operator
 * @param s
 * @return
 */
AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& s) {
    if(this != &s) {
        this->player = s.player;
    }
    return *this;
}

ostream& operator<<(ostream& output, AggressivePlayerStrategy& s)
{
    output << "Aggressive Player Strategy" << endl;
}

// Getters and setters

Player* AggressivePlayerStrategy::getPlayer()
{
    return this->player;
}


void AggressivePlayerStrategy::setPlayer(Player *player)
{
    this->player = player;
}


// Benevolent Player Strategy


BenevolentPlayerStrategy::BenevolentPlayerStrategy()
{
    this->player = nullptr;
}


BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *player)
{
    this->player = player;
}


/**
 * Copy constructor
 * @param s Strategy to copy
 */
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy &s)
{
    this->player = s.player;
}

// Destructor
BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
{
}

/**
 * Assignment Operator
 * @param s
 * @return
 */
BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& s) {
    if(this != &s) {
        this->player = s.player;
    }
    return *this;
}

ostream& operator<<(ostream& output, BenevolentPlayerStrategy& s)
{
    output << "Benevolent Player Strategy" << endl;
}

// Getters and setters

Player* BenevolentPlayerStrategy::getPlayer()
{
    return this->player;
}


void BenevolentPlayerStrategy::setPlayer(Player *player)
{
    this->player = player;
}


// Neutral Player Strategy


NeutralPlayerStrategy::NeutralPlayerStrategy()
{
    this->player = nullptr;
}


NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player)
{
    this->player = player;
}


/**
 * Copy constructor
 * @param s Strategy to copy
 */
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &s)
{
    this->player = s.player;
}

// Destructor
NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
}

/**
 * Assignment Operator
 * @param s
 * @return
 */
NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& s) {
    if(this != &s) {
        this->player = s.player;
    }
    return *this;
}

ostream& operator<<(ostream& output, NeutralPlayerStrategy& s)
{
    output << "Neutral Player Strategy" << endl;
}

// Getters and setters

Player* NeutralPlayerStrategy::getPlayer()
{
    return this->player;
}


void NeutralPlayerStrategy::setPlayer(Player *player)
{
    this->player = player;
}


// Cheater Player Strategy

CheaterPlayerStrategy::CheaterPlayerStrategy()
{
    this->player = nullptr;
}


CheaterPlayerStrategy::CheaterPlayerStrategy(Player *player)
{
    this->player = player;
}


/**
 * Copy constructor
 * @param s Strategy to copy
 */
CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy &s)
{
    this->player = s.player;
}

// Destructor
CheaterPlayerStrategy::~CheaterPlayerStrategy()
{
}

/**
 * Assignment Operator
 * @param s
 * @return
 */
CheaterPlayerStrategy& CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy& s) {
    if(this != &s) {
        this->player = s.player;
    }
    return *this;
}

ostream& operator<<(ostream& output, CheaterPlayerStrategy& s)
{
    output << "Cheater Player Strategy" << endl;
}


// Getters and setters

Player* CheaterPlayerStrategy::getPlayer()
{
    return this->player;
}


void CheaterPlayerStrategy::setPlayer(Player *player)
{
    this->player = player;
}

