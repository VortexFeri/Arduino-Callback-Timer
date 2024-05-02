#include "CallbackTimer.h"

bool Timer::setTimeout(unsigned long delayPeriod, void (*task)()) {
  if (isRunning()) {
    return false;
  }
  set(delayPeriod);
  return setTimeout(task);
}

bool Timer::setTimeout(void (*task)()) {
  if (isRunning()) {
    return false;
  }
  _callback = task;
  _repeatMode = false;
  start();
  return true;
}

bool Timer::setInterval(unsigned long period, void (*task)()) {
  return setInterval(period, -1, task);
}
bool Timer::setInterval(unsigned long period, int times, void (*task)()) {
  if (isRunning() || _execOnce) {
    return false;
  }
  reset();
  _callback = task;
  set(period);
  _repetitionCount = times;
  _repeatMode = true;
  start();
  return true;
}

void Timer::tick() {
  if (_repeatMode && !_execOnce) {
    _execOnce = true;
    _repetitionCount--;
    _callback();
  }
  if (!isDone()) {
    return;
  }
  if (!_callback) {
    return;
  }
  if (!_repeatMode) {
    _callback();
    reset();
  } else if (_repetitionCount != 0) {
    _callback();
    _repetitionCount--;
    start();
  } else {
    int t = _repetitionCount;
    reset();
    _repetitionCount = t;
  }
}

bool Timer::isDone() {
  if (hasStarted() && (getEllapsed() >= _time)) {
    _done = true;
    return true;
  }
  return false;
}

void Timer::set(unsigned long duration) {
  _time = duration;
}

void Timer::reset() {
  stop();
  _done = isDone();
  _last = millis();
  _repetitionCount = 0;
  _callback = nullptr;
}

void Timer::start() {
  _last = millis();
  _done = false;
  _started = true;
}

unsigned long Timer::stop() {
    _done = isDone();
    if (isRunning())
        _last = millis();
    _started = false;
    return getEllapsed();
}
