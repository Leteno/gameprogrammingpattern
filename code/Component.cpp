// ============= dirty code, coupled with each other

if (collidingWithFloor() && (getRenderState() != INVISIBLE))
{
    playSound(HIT_FLOOR);
}

// ====================== original one

class Bjorn
{
public:
    Bjorn()
    : velocity_(0),
      x_(0), y_(0)
    {}

    void update(World& world, Graphics& graphics);

private:
    static const int WALK_ACCELERATION = 1;

    int velocity_;
    int x_, y_;

    Volumn volumne_;

    Sprite spriteStand_;
    Sprite spriteWalkLeft_;
    Sprite spriteWalkRight_;
};

void Bjorn::update(World& world, Graphics& graphics)
{
    // Apply user input to hero's velocity
    switch (Controller::getJoystickDirection())
    {
        case DIR_LEFT:
        velocity_ -= WALK_ACCELERATION;
        break;
        case DIR_RIGHT:
        velocity_ += WALK_ACCELERATION;
        break;
    }

    // Modify position by velocity
    x_ += velocity_;
    world.resolveCollision(volume_, x_, y_, velocity_);

    // Draw the appropriate sprite.
    Sprite* sprite = &spriteStand_;
    if (velocity_ < 0)
    {
        sprite = &spriteWalkLeft_;
    }
    else if (velocity_ > 0)
    {
        sprite = &spriteWalkRight_;
    }

    graphics.draw(*sprite, x_, y_);
}

// ===================== better looking
class InputComponent
{
public:
    void update(Bjorn& bjorn)
    {
         switch (Controller::getJoystickDirection())
        {
            case DIR_LEFT:
            bjorn.velocity -= WALK_ACCELERATION;
            break;
            case DIR_RIGHT:
            bjorn.velocity += WALK_ACCELERATION;
            break;
        } 
    }
private:
    static const int WALK_ACCELERATION = 1;
}

class Bjorn
{
public:
    int velocity;
    int x, y;

    void update(World& world, Graphics& graphics)
    {
        input_.update(*this);

        // Modify position by velocity.
        x += velocity;
        world.resolveCollision(volume_, x, y, velocity);

        // Draw the appropriate sprite.
        Sprite* sprite = &spriteStand_;
        if (velocity < 0)
        {
            sprite = &spriteWalkLeft_;
        }
        else if (velocity > 0)
        {
            sprite = &spriteWalkRight_;
        }

        graphics.draw(*sprite, x, y);
    }

private:
    InputComponent input_;

    Volume volume_;

    Sprite spriteStand_;
    Sprite spriteWalkLeft_;
    Sprite spriteWalkRight_;
};

// =================== splitting out the rest

class PhysicsComponent
{
public:
    void update(Bjorn& bjorn, World& world)
    {
        bjorn.x += bjorn.velocity;
        world.resolveCollision(volume_,
            bjorn.x, bjorn.y, bjorn.velocity);
    }

private:
    Volume volume_;
};

class GraphicsComponent
{
public:
    void update(Bjorn& bjorn, Graphics& graphics)
    {
        Sprite* sprite = &spriteStand_;
        if (bjorn.velocity < 0)
        {
            sprite = &spriteWalkLeft_;
        }
        else if (bjorn.velocity > 0)
        {
            sprite = &spriteWalkRight_;
        }

        graphics.draw(*sprite, bjorn.x, bjorn.y);
    }

private:
    Sprite spriteStand_;
    Sprite spriteWalkLeft_;
    Sprite spriteWalkRight_;
};

class Bjorn
{
public:
    int velocity;
    int x, y;

    void update(World& world, Graphics& graphics)
    {
        input_.update(*this);
        physics_.update(*this, world);
        graphics_.update(*this, graphics);
    }

private:
    InputComponent input_;
    PhysicsComponent physics_;
    GraphicsComponent graphics_;
};


// ===================== make InputComponet decouple with Bjorn

class PlayerInputComponent : public InputComponent
{
public:
  virtual void update(Bjorn& bjorn)
  {
    switch (Controller::getJoystickDirection())
    {
      case DIR_LEFT:
        bjorn.velocity -= WALK_ACCELERATION;
        break;

      case DIR_RIGHT:
        bjorn.velocity += WALK_ACCELERATION;
        break;
    }
  }

private:
  static const int WALK_ACCELERATION = 1;
};

class Bjorn
{
public:
  int velocity;
  int x, y;

  Bjorn(InputComponent* input)
  : input_(input)
  {}

  void update(World& world, Graphics& graphics)
  {
    input_->update(*this);
    physics_.update(*this, world);
    graphics_.update(*this, graphics);
  }

private:
  InputComponent* input_;
  PhysicsComponent physics_;
  GraphicsComponent graphics_;
};

Bjorn* bjorn = new Bjorn(new PlayerInputComponent());

// ================ new InputComponent

class DemoInputComponent : public InputComponent
{
public:
  virtual void update(Bjorn& bjorn)
  {
    // AI to automatically control Bjorn...
  }
};

Bjorn* bjorn = new Bjorn(new DemoInputComponent());

/**
 * Actually, GraphicsSystem don't care about input
 * They concern about position(x, y),
 * So InputSystem should deal with position, and make it work
 * And then, we can pass the new position to GraphicsSystem for renderring
 */

// ========================  best practise

class PhysicsComponent
{
public:
  virtual ~PhysicsComponent() {}
  virtual void update(GameObject& obj, World& world) = 0;
};

class GraphicsComponent
{
public:
  virtual ~GraphicsComponent() {}
  virtual void update(GameObject& obj, Graphics& graphics) = 0;
};

class GameObject
{
public:
  int velocity;
  int x, y;

  GameObject(InputComponent* input,
             PhysicsComponent* physics,
             GraphicsComponent* graphics)
  : input_(input),
    physics_(physics),
    graphics_(graphics)
  {}

  void update(World& world, Graphics& graphics)
  {
    input_->update(*this);
    physics_->update(*this, world);
    graphics_->update(*this, graphics);
  }

private:
  InputComponent* input_;
  PhysicsComponent* physics_;
  GraphicsComponent* graphics_;
};

// example for specific component.
class BjornPhysicsComponent : public PhysicsComponent
{
public:
  virtual void update(GameObject& obj, World& world)
  {
    // Physics code...
  }
};

class BjornGraphicsComponent : public GraphicsComponent
{
public:
  virtual void update(GameObject& obj, Graphics& graphics)
  {
    // Graphics code...
  }
};

GameObject* createBjorn()
{
  return new GameObject(new PlayerInputComponent(),
                        new BjornPhysicsComponent(),
                        new BjornGraphicsComponent());
}

// ==================== How the components communicate with each other

// referring directly to each other.
class BjornGraphicsComponent
{
public:
  BjornGraphicsComponent(BjornPhysicsComponent* physics)
  : physics_(physics)
  {}

  void Update(GameObject& obj, Graphics& graphics)
  {
    Sprite* sprite;
    if (!physics_->isOnGround())
    {
      sprite = &spriteJump_;
    }
    else
    {
      // Existing graphics code...
    }

    graphics.draw(*sprite, obj.x, obj.y);
  }

private:
  BjornPhysicsComponent* physics_;

  Sprite spriteStand_;
  Sprite spriteWalkLeft_;
  Sprite spriteWalkRight_;
  Sprite spriteJump_;
};

/**
 * Good: Simple and fast
 * Bad:  two components are tightly coupled
 */

// By sending messages:

class Component
{
public:
  virtual ~Component() {}
  virtual void receive(int message) = 0;
};

class ContainerObject
{
public:
  void send(int message)
  {
    for (int i = 0; i < MAX_COMPONENTS; i++)
    {
      if (components_[i] != NULL)
      {
        components_[i]->receive(message);
      }
    }
  }

private:
  static const int MAX_COMPONENTS = 10;
  Component* components_[MAX_COMPONENTS];
};

/**
 * Sibling components are decoupled
 * container object is simple.
 * 
 * BTW, this is Mediator pattern.
 * ContainerObject is the Mediator in two components.
 */