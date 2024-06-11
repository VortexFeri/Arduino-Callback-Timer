#ifndef CB_TIMER_H
#define CB_TIMER_H

#include <Arduino.h>

class Timer {
public:
  Timer() : _time(1000){};
  Timer(unsigned long duration) : _time(duration){};
  ~Timer() = default;

  /**
   * @brief Sets up a one-time delayed execution of a task.
   *
   * This method sets up a one-time delayed execution of a task after a specified delay period.
   * It fails and returns false if there is already a callback awaiting.
   *
   * @param delayPeriod The delay period before the task is executed, in milliseconds.
   * @param task A pointer to the function that should be executed.
   *
   * @return true if set succesfully, false otherwise.
   *
   * @note The task will be executed once after the specified delay period.
   *
   * @example
   *
   * auto myTask = []{Serial.println("Task executed");};
   * // Set up a timeout to execute the task after a delay of 5000 milliseconds
   *
   * timer.setTimeout(5000, myTask);
   */
  bool setTimeout(unsigned long delayPeriod, void (*task)());

  /**
   * @brief Sets up a one-time delayed execution of a task.
   *
   * This method sets up a one-time delayed execution of a task after the set delay period.
   * It fails and returns false if there is already a callback awaiting.
   *
   * @param task A pointer to the function that should be executed.
   *
   * @return true if set succesfully, false otherwise.
   *
   * @note The task will be executed once after the specified delay period.
   *
   * @example
   *
   * void myTask() {
   *
   *     Serial.print("Task executed");
   *
   * }
   *
   * // Set up a timeout to execute the task after a delay of 5000 milliseconds
   *
   * timer.set(5000);
   * timer.setTimeout(myTask);
   */
  bool setTimeout(void (*task)());

  /**
   * @brief Sets up a timed interval for executing a task.
   *
   * This method sets up a timed interval for executing a task repeatedly at a specified period.
   * It fails and returns false if there is already a callback awaiting.
   *
   * @param period The time interval between each execution of the task, in milliseconds.
   * @param task A pointer to the function that should be executed.
   *
   * @return true if set succesfully, false otherwise.
   *
   * @note The task will be executed indefinitely until manually stopped.
   *
   * @example
   *
   * void myTask() {
   *
   *     Serial.print("Task executed");
   *
   * }
   *
   * // Set up a timed interval to execute the task with a delay of 1000 milliseconds
   *
   * timer.setInterval(1000, myTask);
   *
   * // To stop the interval, call stop()
   *
   * timer.stop();
   */
  bool setInterval(unsigned long period, void (*task)());

  /**
   * @brief Sets up a timed interval for executing a task.
   *
   * It fails and returns false if there is already a callback awaiting.
   * This method sets up a timed interval for executing a task repeatedly for a specified number of
   * times.
   *
   * @param period The time delay between each execution of the task, in milliseconds.
   * @param times The number of times the task should be executed.
   * @param task A pointer to the function that should be executed.
   *
   * @return true if set succesfully, false otherwise.
   *
   * @example
   *
   * void myTask() {
   *
   *     Serial.print("Task executed"):
   *
   * }
   *
   * // Set up a timed interval to execute the task 10 times with a delay of 1000 milliseconds
   *
   * timer.setInterval(1000, 10, myTask);
   */
  bool setInterval(unsigned long period, int times, void (*task)());

  // Starts the timer. If the timer is still running, it has no effect.
  void start();
  // Stops the timer and returns the the elapsed time. Timed intervals will stop executing.
  unsigned long stop();
  // Resets the timer, setting the elapsed time to zero.
  void reset();
  // Sets the duration of the timer in milliseconds.
  void set(unsigned long duration);
  // Updates the timer, call this in your loop
  void tick();

  /**
   * @brief Checks if the timer has finished.
   *
   * @returns true if the timer has finished (reached its preset duration), false otherwise.
   *
   * @example
   *
   * timer.set(5000);
   * timer.start();
   * if (timer.isDone()) {
   *     // 5 seconds have passed
   * }
   */
  bool isDone();

  /**
   * @brief Checks if the timer is currently running.
   *
   * @returns true if the timer has started and has not finished, false otherwise.
   *
   * @example
   *
   * timer.set(5000);
   * timer.start();
   * if (timer.isRunning()) {
   *     // Timer is currently running
   * }
   */
  inline bool isRunning() { return (hasStarted() && !isDone()); };

  // Returns the elapsed time since the timer started, in milliseconds.
  inline unsigned long getEllapsed() { return millis() - _last; };

  inline int getPreset() { return _time; };
  inline bool hasStarted() { return _started; };

private:
  bool _repeatMode;
  int _repetitionCount;
  unsigned long _time;
  unsigned long _last;
  bool _done;
  bool _started;
  bool _execOnce;
  void (*_callback)();
};

#endif // end CallbackTimer.h
