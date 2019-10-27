// ============ update()

while (true)
{
    // Patrol right.
    for (double x = 0; x < 100; x++)
    {
        skeleton.setX(x);
    }

    // Patrol left.
    for (double x = 100; x > 0; x--)
    {
        skeleton.setX(x);
    }
}

// ==============  update with GameLoop
Entity skeleton;
bool patrollingLeft = false;
double x = 0;

// Main game loop:
while (true)
{
    if (patrollingLeft)
    {
        x--;
        if (x == 0) patrollingLeft = false;
    }
    else
    {
        x++;
        if (x == 100) patrollingLeft = true;
    }
    skeleton.setX(x);

    // Handle user input and render game...
}

// ================ update with GameLoop, and fire bolts

// Skeleton variables...
Entity leftStatue;
Entity rightStatue;
int leftStatueFrames = 0;
int rightStatueFrames = 0;

// Main game loop:
while (true)
{
    // Skeleton code...

    if (++leftStatueFrames == 90)
    {
        leftStatueFrames = 0;
        leftStatue.shootLightning();
    }

    if (++rightStatueFrames == 80)
    {
        rightStatueFrames = 0;
        rightStatue.shootLightning();
    }

    // Handle user input and render game...
}

// ============== be careful of the spawn object:

int numObjectsThisTurn = numObjects_;
for (int i = 0; i < numObjectsThisTurn; i++)
{
    objects_[i]->update();
}
// as to spawn object that add to the end of objects_,
// we should ignore, in case of unexpected many to update


// once the object is "dead", mark it as "dead",
// in the next scan, we deal the corpses by two-pointers.

// ======================== sample code

class Entity
{
public:
    Entity()
    : x_(0), y_(0)
    {}

    virtual ~Entity() {}
    virtual void update() = 0;

    double x() const { return x_; }
    double y() const { return y_; }

    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }

private:
    double x_;
    double y_;
};

class World
{
public:
    World()
    : numEntities_(0)
    {}

    void gameLoop();

private:
    Entity* entities_[MAX_ENTITIES];
    int numEntities_;
};

void World::gameLoop()
{
    while (true)
    {
        // Handle user input

        // Update each entity.
        for (int i = 0; i < numEntities_; i++)
        {
            entities_[i]->update();
        }

        // Physics and rendering...
    }
}

// Favor 'object composition' over 'class inheritance'

class Sea : public Entity
{
    void update()
    {
        // update sea
    }
};

class Sun : public Entity
{
    void update()
    {
        // update sun
    }
};

class Background : public Entity
{
    void update()
    {
        // update Background
        sea_.update();
        sun_.update();
    }
private:
    Sea sea_;
    Sun sun_;
};

// ================

class Skeleton : public Entity
{
public:
    Skeleton()
    : patrollingLeft_(false)
    {}

    virtual void update()
    {
        if (patrollingLeft_)
        {
            setX(x() - 1);
            if (x() == 0) patrollingLeft_ = false;
        }
        else
        {
            setX(x() + 1);
            if (x() == 100) patrollingLeft_ = true;
        }
    }

private:
    bool patrollingLeft_;
};

class Statue : public Entity
{
public:
    Statue(int delay)
    : frames_(0),
      delay_(delay)
    {}

    virtual void update()
    {
        if (++frames_ == delay_)
        {
            shootLightning();

            // Reset the timer.
            frames_ = 0;
        }
    }

private:
    int frames_;
    int delay_;

    void shootLightning()
    {
        // Shoot the lightning...
    }
};


// ====================== elapse time

void Skeleton::update(double elapsed)
{
    if (patrollingLeft_)
    {
        x -= elapsed;
        if (x <= 0)
        {
            patrollingLeft_ = false;
            x = -x;
        }
    }
    else
    {
        x += elapsed;
        if (x >= 100)
        {
            patrollingLeft_ = true;
            x = 100 - (x - 100);
        }
    }
}

/**
 * more complexity of dealing the time step
 */

