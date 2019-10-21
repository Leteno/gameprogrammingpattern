// ================= long time ago

void Heroine::handleInput(Input input)
{
    if (input == PRESS_B)
    {
        yVelocity_ = JUMP_VELOCITY;
        setGraphic(IMAGE_JUMP);
    }
}

// ================= fix bug

void Heroine::handleInput(Input input)
{
    if (input == PRESS_B)
    {
        if (!isJumping_)
        {
            isJumping_ = true;
            // Jump...
        }
    }
}

// ================= more complicate

void Heroine::handleInput(Input input)
{
    if (input == PRESS_B)
    {
        // Jump if not jumping...
    }
    else if (input == PRESS_DOWN)
    {
        if (!isJumping_)
        {
            setGraphics(IMAGE_DUCK);
        }
    }
    else if (input == RELEASE_DOWN)
    {
        setGraphics(IMAGE_STAND);
    }
}

// ================= fix state bugs

void Heroine::handleInput(Input input)
{
    if (input == PRESS_B)
    {
        if (!isJumping_ && !isDucking_)
        {
            // Jump...
        }
    }
    else if (input == PRESS_DOWN)
    {
        if (!isJumping_)
        {
            isDucking_ = true;
            setGraphics(IMAGE_DUCK);
        }
    }
    else if (input == RELEASE_DOWN)
    {
        if (isDucking_)
        {
            isDucking_ = false;
            setGraphics(IMAGE_STAND);
        }
    }
}
// keep bug hunting = =


// ===============  Finite State Machine
enum State
{
    STATE_STANDING,
    STATE_JUMPING,
    STATE_DUCKING,
    STATE_DIVING
}

void Heroine:handleInput(Input input)
{
    switch (state_)
    {
        case STATE_STANDING:
            if (input == PRESS_B)
            {
                state_ = STATE_JUMPING;
                yVelocity_ = JUMP_VELOCITY;
                setGraphics(IMAGE_JUMP);
            }
            else if (input == PRESS_DOWN)
            {
                state_ = STATE_DUCKING;
                setGraphics(IMAGE_DUCK);
            }
            break;
        case STATE_JUMPING:
            if (input == PRESS_DOWN)
            {
                state_ = STATE_DIVING;
                setGraphics(IMAGE_DIVE);
            }
            break;
        case STATE_DUCKING:
            if (input == RELEASE_DOWN)
            {
                state_ = STATE_STANDING;
                setGraphics(IMAGE_STAND);
            }
            break;
    }
}

// ======== ducking - charging

void Heroine::update()
{
    if (state_ == STATE_DUCKING)
    {
        chargeTime_ ++;
        if (chargeTime_ > MAX_CHARGE)
        {
            superBomb();
        }
    }
}

void Heroine::handleInput(Input input)
{
    switch (state_)
    {
        case STATE_STANDING:
            if (input == PRESS_DOWN)
            {
                state_ = STATE_DUCKING;
                chargeTime_ = 0;
                setGraphics(IMAGE_DUCK);
            }
            // Handle other inputs...
            break;

            // Other states...
    }
}

// ===================== state interface

class HeroineState
{
public:
    virtual ~HeroineState() {}
    virtual void handleInput(Heroine& heroine, Input input) {}
    virtual void update(Heroine& heroine) {}
};

class DuckingState : public HeroineState
{
public:
    DuckingState()
    : chargeTime_(0)
    {}

    virtual void handleInput(Heroine& heroine, Input input)
    {
        if (input == RELEASE_DOWN)
        {
            heroine.setGraphics(IMAGE_STAND);
        }
    }

    virtual void update(Heroine& heroine)
    {
        chargeTime_++;
        if (chargeTime_ > MAX_CHARGE)
        {
            heroine.superBomb();
        }
    }

private:
    int chargeTime_;
};

// ========================== Delegate to State

class Heroine
{
public:
    virtual void handleInput(Input input)
    {
        state_->handleInput(*this, input);
    }

    virtual void update()
    {
        state_->update(*this);
    }

    // Other methods...

private:
    HeroineState* state_;
};

// ======================= apply Flyweight pattern

class HeroineState
{
public:
    static StandingState standing;
    static DuckingState ducking;
    static JumpingState jumping;
    static DivingState diving;

    // Other code...
};

if (input == PRESS_B)
{
    heroine.state_ = &HeroineState::jumping;
    heroine.setGraphics(IMAGE_JUMP);
}

void Heroine::handleInput(Input input)
{
    HeroineState* state = state_->handleInput(*this, input);
    if (state != NULL)
    {
        delete state_;
        state_ = state;
    }
}

HeroineState* StandingState::handleInput(Heroine& heroine, Input input)
{
    if (input == PRESS_DOWN)
    {
        // Other code...
        return new DuckingState();
    }

    // Stay in this state.
    return NULL;
}
// creating and delete, burn the CPU

// ====================== no god judge, just person to person

HeroineState* DuckingState::handleInput(Heroine& heroine,
                                        Input input)
{
  if (input == RELEASE_DOWN)
  {
    return new StandingState();
  }

  // Other code...
}

class StandingState : public HeroineState
{
public:
  virtual void enter(Heroine& heroine)
  {
    heroine.setGraphics(IMAGE_STAND);
  }

  // Other code...
};

void Heroine::handleInput(Input input)
{
  HeroineState* state = state_->handleInput(*this, input);
  if (state != NULL)
  {
    delete state_;
    state_ = state;

    // Call the enter action on the new state.
    state_->enter(*this);
  }
}

// ============================== Concurrent State Machine
// different aspects has its own state machine

class Heroine
{

private:
    HeroineState* state_;
    HeroineState* equipment_;
};

void Heroine::handleInput(Input input)
{
    state_->handleInput(*this, input);
    equipment_->handleInput(*this, input);
}

// =============================== Hierarchical State Machine
// to reuse the dealing function

class OnGroundState : public HeroineState
{
public:
    virtual void handleInput(Heroine& heroine, Input input)
    {
        if (input == PRESS_B)
        {
            // Jump...
        }
        else if (input == PRESS_DOWN)
        {
            // Duck...
        }
    }
};

class DuckingState : public OnGroundState
{
public:
    virtual void handleInput(Heroine& heroine, Input input)
    {
        if (input == RELEASE_DOWN)
        {
            // Stand up...
        }
        else
        {
            // Didn't handle input, so walk up hierarchy.
            OnGroundState::handleInput(heroine, input);
        }
    }
};

// I just care what is matter to me.

// to be more focused

// ==============================
// However you only remember the state you are
// Not the state you were


// ========>>>>>>>>>>>>>>  use stack to store it.

/*

* The top of the stack is the current state
* You can delete a unused state by remove it. And the old one becomes the current.
  Like: Jumping state is invalid when you onto the ground.
        Remove it, and the StandingState become the top.
  This can also keep the stack small.
*/