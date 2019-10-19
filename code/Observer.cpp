class Observer
{
    friend class Subject;
public:
    Observer()
    : next_(NULL)
    {}
    virtual ~Observer() {}
    virtual void onNotify(const Entity& entity, Event event) = 0;
private:
    Observer* next_;
};

class Achievements : public Observer
{
public:
    virtual void onNotify(const Entity& entity, Event event)
    {
        switch (event)
        {
            case EVENT_ENTITY_FELL:
                if (entity.isHero() && heroIsOnBridge_)
                {
                    unlock(ACHIEVEMENT_FELL_OFF_BRIDGE);
                }
                break;
        }
    }
private:
    void unlock(Achievement achievement)
    {

    }
    bool heroIsOnBridge_;
};

class Subject
{
public:
    Subject()
    : head_(NULL)
    {}
    void addObserver(Observer* observer)
    {
        observer->next_ = head_;
        head_ = observer;
    }
    void removeObserver(Observer* observer)
    {
        if (head_ == observer)
        {
            head_ = observer->next_;
            observer->next_ = NULL;
            return;
        }

        Observer* current = head_;
        while (current != NULL)
        {
            if (current->next_ == observer)
            {
                current->next_ = observer->next_;
                observer->next_ = NULL;
                return;
            }

            current = current->next_;
        }
    }
protected:
    void notify(const Entity& entity, Event event)
    {
        Observer* observer = head_;
        while (observer != NULL)
        {
            observer->onNotify(entity, event);
            observer = observer->next_;
        }
    }
private:
    Observer* head_;
};

class Physics : public Subject
{
public:
    void updateEntity(Entity& entity);
};

physics.entityFell()
    .addObserver(this);