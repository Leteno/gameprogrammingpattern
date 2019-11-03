// =============

while (running)
{
    Event event = getNextEvent();
    // Handle event...
}

// ==================

class Audio
{
public:
    static void playSound(SoundId id, int volume);
};

void Audio::playSound(SoundId id, int volume)
{
    ResourceId resource = loadSound(id);
    int channel = findOpenChannel();
    if (channel == -1) return;
    startSound(resource, channel, volume);
}

class Menu
{
public:
    void onSelect(int index)
    {
        Audio::playSound(SOUND_BLOOP, VOL_MAX);
        // Other stuff...
    }
};

// ============== keep in mind
/**
 * A central event queue is a global variable
 * The state of the world can change under you(don't assume the world should be what, be third-party)
 * You can get stuck in feedback loops (event cycle: A->B B->A A->B)
 */
struct PlayMessage
{
    SoundId id;
    int volume;
};

class Audio
{
public:
    static void init()
    {
        numPending_ = 0;
    }
private:
    static const int MAX_PENDING = 16;

    static PlayMessage pending_[MAX_PENDING];
    static int numPending_;
};

void Audio::playSound(SoundId id, int volume)
{
    assert(numPending_ < MAX_PENDING);

    pending_[numPending_].id = id;
    pending_[numPending_].volume = volume;
    numPending_++;
}

class Audio
{
public:
    static void update()
    {
        for (int i = 0; i < numPending_; i++)
        {
            ResourceId resource = loadSound(pending_[i].id);
            int channel = findOpenChannel();
            if (channel == -1) return;
            startSound(resource, channel, pending_[i].volume);
        }

        numPending_ = 0;
    }

    // Other stuff...
};

// ======================= ring buffer

class Audio
{
public:
    static void init()
    {
        head_ = 0;
        tail_ = 0;
    }
    // Methods...

private:
    static int head_;
    static int tail_;
};

void Audio::playSound(SoundId id, int volume)
{
    assert(tail_ < MAX_PENDING);

    // Add to the end of the list.
    pending_[tail_].id = id;
    pending_[tail_].volume = volume;
    tail_++;
}

void Audio::update()
{
    // If there are no pending requests, do nothing.
    if (head_ == tail_) return;

    ResourceId resource = loadSound(pending_[head_].id);
    int channel = findOpenChannel();
    if (channel == -1) return;
    startSound(resource, channel, pending_[head_].volume);

    head_++;
}

// ring buffer.
void Audio::playSound(SoundId id, int volume)
{
    assert((tail_ + 1) % MAX_PENDING != head_);

    // Add to the end of the list.
    pending_[tail_].id = id;
    pending_[tail_].volume = volume;
    tail_ = (tail_ + 1) % MAX_PENDING;
}

void Audio::update()
{
    // If there are no pending requests, do nothing.
    if (head_ == tail_) return;

    ResourceId resource = loadSound(pending_[head_].id);
    int channel = findOpenChannel();
    if (channel == -1) return;
    startSound(resource, channel, pending_[head_].volume);

    head_ = (head_ + 1) % MAX_PENDING;
}