// not defining different super powers
// define that behavior in data instead.

// interact with subsystem(sound, video) leave to base class
// subclass focus on behavior and use the method base class provide
// decoupling subclass with subsystem.
// however, coupling baseclass with subsystem, which means
// a big spider web, change one method may effect all the subclass
// However, this is what we want, control the way to subsystem

class Superpower
{
public:
    virtual ~Superpower() {}
protected:
    virtual void activate() = 0;

    void move(double x, double y, double z)
    {
        // Code here
    }

    void playSound(SoundId sound, double volume)
    {
        // Code here...
    }

    void spawnParticles(ParticleType type, int count)
    {
        // Code here...
    }
};

class SkyLaunch : public Superpower
{
protected:
    virtual void activate()
    {
        // Spring into the air.
        playSound(SOUND_SPROING, 1.0f);
        spawnParticles(PARTICLE_DUST, 10);
        move(0, 0, 20);
    }
};

// =============================== Add Hero coordinator

class Superpower
{
protected:
    double getHeroX()
    {
        // Code here...
    }

    double getHeroY()
    {
        // Code here...
    }

    double getHeroZ()
    {
        // Code here...
    }

    // Existing stuff...
};

class SkyLaunch : public Superpower
{
protected:
    virtual void activate()
    {
        if (getHeroZ() == 0)
        {
            // On the ground, so spring into the air.
            playSound(SOUND_SPROING, 1.0f);
            spawnParticles(PARTICLE_DUST, 10);
            move(0, 0, 20);
        }
        else if (getHeroZ() < 10.0f)
        {
            // Near the ground, so do a double jump.
            playSound(SOUND_SWOOP, 1.0f);
            move(0, 0, getHeroZ() - 20);
        }
        else
        {
            // Way up in the air, so do a dive stack.
            playSound(SOUND_DIVE, 0.7f);
            spawnParticles(PARTICLE_SPARKLES, 1);
            move(0, 0, -getHeroZ());
        }
    }
};


// ============== consideration:

/**
 * What operations should be provided in base class?
 *  1. (no) provided operation is only used in one or a few subclasses
 * 
 */

/**
 * Should methods be provided directly, or through objects that contain them?
 */

class Superpower
{
protected:
    void playSound(SoundId sound, double volume) {}
    void stopSound(SoundId sound) {}
    void setVolumn(SoundId sound) {}
};

/**
 * VS
 */

class SoundPlayer
{
    void playSound(SoundId sound, double volume) {}
    void stopSound(SoundId sound) {}
    void setVolumn(SoundId sound) {}
};

class Superpower
{
protected:
    SoundPlayer& getSoundPlayer()
    {
        return soundPlayer_;
    }
private:
    SoundPlayer soundPlayer_;
};

/**
 * How does the base class get the state that it needs?
 */

// Pass it to the base class constructor

class Superpower
{
public:
    Superpower(ParticleSystem* particles)
    : particles_(particles)
    {} 

private:
    ParticleSystem* particles_;
};

class SkyLaunch : public Superpower
{
public:
    SkyLaunch(ParticleSystem* particles)
    : Superpower(particles)
    {}
};

// Do two-stage initialization

Superpower* power = new SkyLaunch();
power->init(particles);

// don't forget to use init() after new SkyLaunch

Superpower* createSkyLaunch(ParticleSystem* particles)
{
    Superpower* power = new SkyLaunch();
    power->init(particles);
    return power;
}