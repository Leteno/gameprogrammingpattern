class Expression
{
public:
    virtual ~Expression() {}
    virtual double evaluate() = 0;
};

class NumberExpression : public Expression
{
public:
    NumberExpression(double value)
    : value_(value)
    {}

    virtual double evaluate()
    {
        return value_;
    }

private:
    double value_;
};

class AdditionExpression : public Expression
{
public:
    AdditionExpression(Expression* left, Expression* right)
    : left_(left),
      right_(right)
    {}

    virtual double evaluate()
    {
        double left = left_->evaluate();
        double right = right_->evaluate();

        return left + right;
    }
private:
    Expression* left_;
    Expression* right_;
};

// Interpretor, slow, use up too many memory

// =================== enter the mistery

void setHealth(int wizard, int amount);
void setWisdom(int wizard, int amount);
void setAgility(int wizard, int amount);
void playSound(int soundId);
void spawnParticles(int particleType);

enum Instruction
{
    INST_SET_HEALTH = 0x00,
    INST_SET_WISDOM = 0x01,
    INST_SET_AGILITY = 0x02,
    INST_PLAY_SOUND = 0x03,
    INST_SPAWN_PARTICLES = 0x04
};

switch (Instruction)
{
    case INST_SET_HEALTH:
        setHealth(0, 100);
        break;
    case INST_SET_WISDOM:
        setWisdom(0, 100);
        break;
    case INST_SET_AGILITY:
        setAgility(0, 100);
        break;
    case INST_PLAY_SOUND:
        playSound(SOUND_BANG);
        break;
    case INST_SPAWN_PARTICLES:
        spawnParticles(PARTICLE_FLAME);
        break;
}

class VM
{
public:
    void interpret(char bytecode[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            char instruction = bytecode[i];
            switch (instruction)
            {
                // Cases for each instruction...
            }
        }
    }
};

// ========================= stack to do so

class VM
{
public:
    VM()
    : stackSize_(0)
    {}

private:
    static const int MAX_STACK = 128;
    int stackSize_;
    int stack_[MAX_STACK];
};

// push and pop

class VM
{
private:
    void push(int value)
    {
        // Check for stack overflow.
        assert(stackSize_ < MAX_STACK);
        stack_[stackSize_++] = value;
    }

    int pop()
    {
        // Make sure the stack isn't empty.
        assert(stackSize_ > 0);
        return stack_[--stackSize_];
    }
};

// use stack to do with instruction

switch (instruction)
{
    case INST_SET_HEALTH:
    {
        int amount = pop();
        int wizard = pop();
        setHealth(wizard, amount);
        break;
    }
    case INST_SET_WISDOM:
    case INST_SET_AGILITY:
    // Same as above...

    case INST_PLAY_SOUND:
        playSound(pop());
        break;

    case INST_SPAWN_PARTICLES:
        spawnParticles(pop());
        break;
}

// for new pattern:

case INST_LITERAL:
{
    // Read the next byte from the bytecode.
    int value = bytecode[++i];
    push(value);
    break;
}

// LITERAL 0 LITERAL 10 HEALTH
// 0x05 0x0 0x05 0xA 0x00
// ==> push(0), push(10), setHealth(pop(), pop())

// the data is the code !!!

// ======================  Behavior = composition

// above one, we can easily set the health of special value.
// but we can't like say: increase wisdom by half of now.

// However, we can add new instruction

case INST_GET_HEALTH:
{
    int wizard = pop();
    push(getHealth(wizard));
    break;
}

// add Addition function:
case INST_ADD:
{
    int b = pop();
    int a = pop();
    push(a + b);
    break;
}

// for the function:
setHealth(0, getHealth(0) +
    (getAgility(0) + getWisdom(0)) / 2);


// ====>
LITERAL 0
LITERAL 0
GET_HEALTH
LITERAL 0
GET_AGILITY
LITERAL 0
GET_WISDOM
ADD
LITERAL 2
DIVIDE
ADD
SET_HEALTH

// ======================= tagged variant
// more complex value, tagged union
enum ValueType
{
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING
};

struct Value
{
    ValueType type;
    union
    {
        int intValue;
        double doubleValue;
        char* stringValue;
    };
};
