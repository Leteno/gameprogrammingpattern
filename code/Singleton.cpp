class FileSystem
{
public:
    static FileSystem& instance()
    {
        if (instance_ == NULL) instance_ = new FileSystem();
        return *instance_;
    }

private:
    FileSystem() {}
    static FileSystem* instance_;
};

//========= modern

class FileSystem
{
public:
    static FileSystem& instance()
    {
        static FileSystem *instance = new FileSystem();
        return *instance;
    }

private:
    FileSystem() {}
};

//==================   cross platform
class FileSystem
{
public:
    static FileSystem& instance();

    virtual ~FileSystem() {}
    virtual char* readFile(char* path) = 0;
    virtual void writeFile(char* path, char* contents) = 0;

protected:
    FileSystem() {}
};
class PS3FileSystem : public FileSystem
{
public:
    virtual char* readFile(char* path) {}
    virtual void writeFile(char* path, char* contents) {}
};

class WiiFileSystem : public FileSystem
{
public:
    virtual char* readFile(char* path) {}
    virtual void writeFile(char* path, char* contents) {}
};

FileSystem& FileSystem::instance()
{
    #if PLATFORM == PLAYSTATION3
        static FileSystem *instance = new PS3FileSystem();
    #elif PLATFORM == WII
        static FileSystem *instance = new WiiFileSystem();
    #endif

    return *instance;
}


// ==================== lazy init

class FileSystem
{
public:
    static FileSystem& instance() { return instance_; }

private:
    FileSystem() {}

    static FileSystem instance_;
};


// ==================== safer

class FileSystem
{
public:
    FileSystem()
    {
        assert(!instantiated_);
        instantiated_ = true;
    }

    ~FileSystem() { instantiated_ = false; }

private:
    static bool instantiated_;
};

bool FileSystem::instantiated_ = false;


// ======================== subclass sandbox

class GameObject
{
protected:
    Log& getLog() { return log_; }

private:
    static Log& log_;
};

class Enemy : public GameObject
{
    void doSomething()
    {
        getLog().write("I can log !");
    }
};

// ====================== game main

class Game
{
public:
    static Game& instance() { return instance_; }

    Log& getLog() {return *log_; }
    FileSystem& getFileSystem() { return *fileSystem_; }
    AudioPlayer& getAudioPlayer() { return *audioPlayer_; }

private:
    static Game instance_;

    Log *log_;
    FileSystem *fileSystem_;
    AudioPlayer *audioPlayer_;
};

Game::instance().getAudioPlayer().play(VERY_LOUD_BANG);