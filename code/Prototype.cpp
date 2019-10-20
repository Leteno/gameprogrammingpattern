class Monster
{
};

class Ghost : public Monster {};
class Demon : public Monster {};
class Sorcerer : public Monster {};

class Spawner
{
public:
    virtual ~Spawner() {}
    virtual Monster* spawnMonster() = 0;
};

class GhostSpawner : public Spawner
{
public:
    virtual Monster* spawnMonster()
    {
        return new Ghost();
    }
};

//=================================

class Monster
{
public:
    virtual ~Monster() {}
    virtual Monster* clone() = 0;
};

class Ghost : public Monster
{
public:
    Ghost(int health, int speed)
    : health_(health),
      speed_(speed)
    {}

    virtual Monster* clone()
    {
        return new Ghost(health_, speed_);
    }
private:
    int health_;
    int speed_;
};

class Spawner
{
public:
    Spawner(Monster* prototype)
    : prototype_(prototype)
    {}

    Monster* spawnMonster()
    {
        return prototype_->clone();
    }
private:
    Monster* prototype_;
};

Monster* ghostPrototype = new Ghost(15, 3);
Spawner* ghostSpawner = new Spawner(ghostPrototype);


//============================

typedef Monster* (*SpawnCallback)();

class Spawner
{
public:
    Spawner(SpawnCallback spawn)
    : spawn_(spawn)
    {}

    Monster* spawnMonster()
    {
        return spawn_();
    }
private:
    SpawnCallback spawn_;
};

Monster* spawnGhost()
{
    return new Ghost();
}

Spawner* ghostSpawner = new Spawner(spawnGhost);


//=================================

class Spawner
{
public:
    virtual ~Spawner() {}
    virtual Monster* spawnMonster() = 0;
};

template <class T>
class SpawnerFor : public Spawner
{
public:
    virtual Monster* spawnMonster() { return new T(); }
};


//====================================

function Weaphon(range, damage) {
    this.range = range;
    this.damage = damage;
}

var sword = new Weaphon(10, 16);

Weapon.prototype.attack = function(target) {
    if (distanceTo(target) > this.range) {
        console.log("Out of range!");
    } else {
        target.health -= this.damage;
    }
}

Spawner* ghostSpawner = new SpawnerFor<Ghost>();
