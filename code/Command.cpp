class Command
{
public:
    virtual ~Command() {}
    virtual void execute(GameActor& actor) = 0;
    virtual void undo() = 0;
};

class JumpCommand : public Command
{
public:
    virtual void execute(GameActor& actor) { actor->jump(); }
};

class MoveUnitCommand : public Command
{
public:
    MoveUnitCommand(Unit* unit, int x, int y)
    : unit_(unit),
      x_(x),
      y_(y)
      {}
    virtual void execute()
    {
        unit_->moveTo(x_, y_);
    }
private:
    Unit* unit_;
    int x_, y_;
}

class InputHandler
{
public:
    Command* handleInput();
private:
    Command* buttonX_;
    Command* buttonY_;
    Command* buttonA_;
    Command* buttonB_;
};

Command* InputHandler::handleInput()
{
    Unit* unit = getSelectedUnit();
    if (isPressed(BUTTON_UP)) {
        int destY = unit->y() - 1;
        return new MoveUnitCommand(unit, unit->x(), destY);
    }
    // ...
    if (isPressed(BUTTON_X)) return buttonX_;
    else if (isPressed(BUTTON_Y)) return buttonY_;
    else if (isPressed(BUTTON_A)) return buttonA_;
    else if (isPressed(BUTTON_B)) return buttonB_;

    return NULL;
}

void main() {
    Command* command = inputHandler.handleInput();
    if (command)
    {
        command->execute(actor);
    }
}