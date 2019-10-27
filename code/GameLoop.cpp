// ======= in acient time

while (true)
{
    char* command = readCommand();
    handleCommand(command);
}

// ============== event loops

while (true)
{
    Event* event = waitForEvent();
    dispatchEvent(event);
}

// ===============

while (true)
{
    processInput();
    update();
    render();
}

// 1000ms / FPS = ms per frame

while (true)
{
    double start = getCurrentTime();
    processInput();
    update();
    render();

    sleep(start + MS_PER_FRAME - getCurrentTime());
}

// try to keep it in specific FPS
// if cpu is fast enough, maybe it act fine, however, it must be 'slower'


// ================== use elapse time

double lastTime = getCurrentTime();
while (true)
{
    double current = getCurrentTime();
    double elapsed = current - lastTime;
    processInput();
    update(elapsed);
    render();
    lastTime = current;
}

// run update by elaspsed (2.234251431)
// float value calculation + different render time in between fast and slow machine
// => different result in Precision

//================  update in a fix time

double previous = getCurrentTime();
double lag = 0.0;
while (true)
{
    double current = getCurrentTime();
    double elapsed = current - previous;
    previous = current;
    lag += elapsed;

    processInput();

    while (lag >= MS_PER_UPDATE)
    {
        update();
        lag -= MS_PER_UPDATE;
    }

    render(lag / MS_PER_UPDATE); // to fixup with when 0 < lag < MS_PER_UPDATE
    // lag / MS_PER_UPDATE,   is how many frame should be advanced (0, 1) 
}