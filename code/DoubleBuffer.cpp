class Framebuffer
{
public:
    Framebuffer() { clear(); }
    void clear()
    {
        for (int i = 0; i < WIDTH * HEIGHT; i++)
        {
            pixels_[i] = WHITE;
        }
    }

    void draw(int x, int y)
    {
        pixels_[(WIDTH * y) + x] = BLACK;
    }

    const char* getPixels()
    {
        return pixels_;
    }

private:
    static const int WIDTH = 160;
    static const int HEIGHT = 120;

    char pixels_[WIDTH * HEIGHT];
};

// =================== Single buffer
class Scene
{
public:
    void draw()
    {
        buffer_.clear();

        buffer_.draw(1, 1);
        buffer_.draw(4, 1);
        buffer_.draw(1, 3);
        buffer_.draw(2, 4);
        buffer_.draw(3, 4);
        buffer_.draw(4, 3);
    }

    Framebuffer& getBuffer() { return buffer_; }

private:
    Framebuffer buffer_;
};

// ==================== Double buffer
class Scene
{
public:
    Scene()
    : current_(&buffers_[0]),
      next_(&buffers_[1])
    {}

    void draw()
    {
        next_->clear();
        next_->draw(1, 1);
        next_->draw(4, 3);
        swap();
    }

    Framebuffer& getBuffer() { return *current_; }

private:
    void swap()
    {
        // Just switch the pointers.
        Framebuffer* temp = current_;
        current_ = next_;
        next_ = temp;
    }

    Framebuffer  buffers_[2];
    Framebuffer* current_;
    Framebuffer* next_;
};

/**
 * Beautiful.
 * For drawing machine, it just care about getBuffer()
 * And draw the `ready` buffer.
 * However, if the draw() cost a lot of time, you may see one scene for several iterations.
 * 
 * Ioc
 */

//===========================  Artificial unintelligence

class Actor
{
public:
    Actor() : slapped_(false) {}

    virtual ~Actor() {}
    virtual void update() = 0;

    void reset()      { slapped_ = false; }
    void slap()       {slapped_ = true; }
    bool wasSlapped() { return slapped_; }

private:
    bool slapped_;
};

class Stage
{
public:
    void add(Actor* actor, int index)
    {
        actors_[index] = actor;
    }

    void update()
    {
        for (int i = 0; i < NUM_ACTORS; i++)
        {
            actors_[i]->update();
            actors_[i]->reset();
        }
    }
private:
    static const int NUM_ACTORS = 3;
    Actor* actors_[NUM_ACTORS];
};

class Comedian : public Actor
{
public:
    void face(Actor* actor) { facing_ = actor; }

    virtual void update()
    {
        if (wasSlapped()) facing_->slap();
    }

private:
    Actor* facing_;
};

Stage stage;

Comedian* harry = new Comedian();
Comedian* baldy = new Comedian();
Comedian* chump = new Comedian();

harry->face(baldy);
baldy->face(chump);
chump->face(harry);

stage.add(harry, 0);
stage.add(baldy, 1);
stage.add(chump, 2);

harry->slap();
stage.update();

// ===================== buffered slaps

class Actor
{
public:
    Actor(): currentSlapped_(false) {}
    virtual ~Actor() {}
    virtual void update() = 0;

    void swap()
    {
        // Swap the buffer.
        currentSlapped_ = nextSlapped_;
        // Clear the new "next" buffer.
        nextSlapped_ = false;
    }

    void slap()       { nextSlapped_ = true; }
    bool wasSlapped() { return currentSlapped_; }

private:
    bool currentSlapped_;
    bool nextSlapped_;
};

void Stage::update()
{
    for (int i = 0; i < NUM_ACTORS; i++)
    {
        actors_[i]->update();
    }

    for (int i = 0; i < NUM_ACTORS; i++)
    {
        actors_[i]->swap();
    }
}