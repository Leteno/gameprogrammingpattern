
class Audio
{
public:
    virtual ~Audio() {}
    virtual void playSound(int soundID) = 0;
    virtual void stopSound(int soundID) = 0;
    virtual void stopAllSounds() = 0;
};

class ConsoleAudio : public Audio
{
public:
    virtual void playSound(int soundID)
    {
        // Play sound using console audio api...
    }

    virtual void stopSound(int soundID)
    {
        // Stop sound using console audio api...
    }

    virtual void stopAllSounds()
    {
        // Stop all sounds using console audio api...
    }
};

class Locator
{
public:
    static Audio* getAudio() { return service_; }

    static void provide(Audio* service)
    {
        service_ = service;
    }

private:
    static Audio* service_;
};

Audio* audio = Locator::getAudio();
audio->playSound(VERY_LOUD_BANG);

ConsoleAudio* audio = new ConsoleAudio();
Locator::provide(audio);

// ====================== NULL Prevention

class NullAudio: public Audio
{
public:
    virtual void playSound(int soundID) { /* Do nothing. */ }
    virtual void stopSound(int soundID) { /* Do nothing. */ }
    virtual void stopAllSounds(int soundID) { /* Do nothing. */ }
};

class Locator
{
public:
    static void initialize() { service_ = &nullService_; }
    static Audio& getAudio() { return *service_; }
    static void provide(Audio* service)
    {
        if (service == NULL)
        {
            // Revert to null service
            service_ = &nullService_;
        }
        else
        {
            service_ = service;
        }
    }

private:
    static Audio* service_;
    static NullAudio nullService_;
};

// ============ wrap audio system by logging

class LoggedAudio : public Audio
{
public:
    LoggedAudio(Audio &wrapped)
    : wrapped_(wrapped)
    {}

    virtual void playSound(int soundID)
    {
        log("play sound");
        wrapped_.playSound(soundID);
    }

    virtual void stopSound(int soundID)
    {
        log("stop sound");
        wrapped_.stopSound(soundID);
    }

    virtual void stopAllSounds()
    {
        log("stop all sounds");
        wrapped_.stopAllSounds();
    }

private:
    void log(const char* message)
    {
        // Code to log message
    }

    Audio &wrapped_;
};

void enableAudioLogging()
{
    Audio* service = new LoggedAudio(Locator::getAudio());
    Locator::provide(service);
}

/**
 * Users don't need to handle a missing service.
 * They just call and leave it.
 * Their function is always clean without any safe checks.
 * 
 * Leave the main logic alone, don't pollute it.
 */

/**
 * Control the scope based on your need.
 * 
 * If global, then static globally
 * 
 * If restricted to a class, then make a new instance.
 * 
 */