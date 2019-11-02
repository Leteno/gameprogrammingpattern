class Monster
{
public:
    virtual ~Monster() {}
    virtual const char* getAttack() = 0;

protected:
    Monster(int startingHealth)
    : health_(startingHealth)
    {}

private:
    int health_;
};

class Dragon : public Monster
{
public:
    Dragon() : Monster(230) {}

    virtual const char* getAttack()
    {
        return "The dragon breathes fire!";
    }
};

class Troll : public Monster
{
public:
    Troll() : Monster(48) {}

    virtual const char* getAttack()
    {
        return "The troll clubs you!";
    }
};

// ======================

class Breed
{
public:
    Breed(int health, const char* attack)
    : health_(health),
      attack_(attack)
    {}

    int getHealth() { return health_; }
    const char* getAttack() { return attack_; }

private:
    int health_;
    const char* attack_;
};

class Monster
{
public:
    Monster(Breed& breed)
    : health_(breed.getHealth()),
      breed_(breed)
    {}

    const char* getAttack()
    {
        return breed_.getAttack();
    }

private:
    int health_;
    Breed& breed_;
};

// ==========================

class Breed
{
public:
    Monster* newMonster() { return new Monster(*this); }

    // Previous Breed code...
};

class Monster
{
    friend class Breed;

public:
    const char* getAttack() { return breed_.getAttack(); }

private:
    Monster(Breed& breed)
    : health_(breed.getHealth()),
      breed_(breed)
    {}

    int health_;
    Breed& breed_;
};

// ==========================
class Breed
{
public:
    Breed(Breed* parent, int health, const char* attack)
    : parent_(parent),
      health_(health),
      attack_(attack)
    {}

    int getHealth();
    const char* getAttack();

private:
    Breed* parent_;
    int health_;
    const char* attack_;
};

int Breed::getHealth()
{
    // Override.
    if (health_ != 0 || parent_ == NULL) return health_;

    // Inherit.
    return parent_->getHealth();
}

const char* Breed::getAttack()
{
    // Override.
    if (attack_ != NULL || parent_ == NULL) return attack_;

    // Inherit.
    return parent_->getAttack();
}

Breed(Breed* parent, int health, const char* attack)
: health_(health),
  attack_(attack)
{
    if (parent != NULL)
    {
        if (health == 0) health_ = parent->getHealth();
        if (attack == NULL) attack_ = parent->getAttack();
    }
}

int getHealth() { return health_; }
const char* getAttack() { return attack_; }

{
    "Troll": {
        "health": 25,
        "attack": "The troll hits you!"
    },
    "Troll Archer": {
        "parent": "Troll",
        "health": 0,
        "attack": "The troll archer fires an arrow!"
    },
    "Troll Wizard": {
        "parent": "Troll",
        "health": 0,
        "attack": "The troll wizard casts a spell on you!"
    }
}