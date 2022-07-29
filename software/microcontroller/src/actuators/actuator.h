#ifndef PEAPOD_ACTUATORS_ACTUATOR_H_
#define PEAPOD_ACTUATORS_ACTUATOR_H_

// HEADERS

#include <Arduino.h>

#include <utils/base.h>

// DECLARATIONS

// All actuator state info
typedef struct ActuatorState {
  // Error level
  errorlevel_t error;

  // Other state information
  debuglevel_t debug;

  // Last successfully set target - is set to the value of `target` on successful `set()`
  float lasttarget;
} ActuatorState;

// CLASS

class Actuator {
  public:
    /**
     * @param failtarget Target that the actuator should be set to in case of failure
     */
    Actuator(const char* const* id, float failtarget);

    /**
     * Wrapper function for `set()`. Checks debug state (initialized).
     * @returns Pointer to actuator state
     */
    ActuatorState* update(void);

    /**
     * Wrapper function for `initialize()`. Sets debug state to indicate initialization success or failure, and also performs a first `update()`.
     * @return Pointer to actuator state
     */
    ActuatorState* begin(void);

    // @return Pointer to actuator state
    ActuatorState* getState(void);

    // @param target Actuator target
    void setTarget(float target);

    // @return String representation of this actuator
    String toString(void);

  protected:
    /**
     * Initializes actuator. To be implemented by the child class.
     * @return Error level for this initialization attempt
     */
    virtual errorlevel_t initialize(void) = 0;

    /**
     * Sets actuator state. To be implemented by the child class.
     * @param target Target for this actuator
     * @return Error level for this set attempt
     */
    virtual errorlevel_t set(float target) = 0;

  private:
    // Actuator ID
    const char* const* _id;

    // Stores all the latest state data for this actuator.
    ActuatorState state;

    // Failsafe target
    float failtarget;

    // Target state value for this actuator
    float target;
};

#endif
