#ifndef ODU_HPP
#define ODU_HPP

// Standard includes
#include <random>
#include <iostream>

// Cadmium V2 includes
#include "cadmium/modeling/devs/atomic.hpp"

// Namespaces
using namespace cadmium;

/**
 * Enum
 */
enum class OduStateName {
    PASSIVE,
    ACQUIRE_LOCK,
    RELEASE_LOCK,
    TX_RX
};

/**
 * operator<< overload definition.
 *
 * Defines the output format of the OduStateName enum class.
 */
std::ostream& operator<<(std::ostream& os, OduStateName state_name) {
    switch (state_name) {
        case OduStateName::PASSIVE:
            os << "PASSIVE";
            break;
        case OduStateName::ACQUIRE_LOCK:
            os << "ACQUIRE_LOCK";
            break;
        case OduStateName::RELEASE_LOCK:
            os << "RELEASE_LOCK";
            break;
        case OduStateName::TX_RX:
            os << "TX_RX";
            break;
        default:
            os << "ERROR";
            break;
    }
    return os;
}


/**
 * Atomic model state variables
 */
struct OduState {
    /**
     * Members
     */
    double sigma;
    OduStateName s;
    bool lock;
    
    /**
     * Constructor
     */
    explicit OduState(): sigma(std::numeric_limits<double>::infinity()), s(OduStateName::PASSIVE), lock(false) {
   }

};

/**
 * operator<< overload definition.
 *
 * Defines the output format to a given file stream uwsing this model's state variables.
 */
std::ostream& operator<<(std::ostream &out, const OduState& state) {
    out << "{" 
            << "state=" << state.s << ", "
            << "sigma=" << state.sigma << ", "
            << "lock=" << state.lock
        << "}";
    return out;
}

/**
 * Atomic model class definition.
 *
 * Extends the Cadmium V2 `Atomic` class.
 */
class Odu : public Atomic<OduState> {

private:

public:

    /**
     * Constants
     */
    static constexpr double ACQUIRE_LOCK_TIME = 2.00;
    static constexpr double RELEASE_LOCK_TIME = 1.00;

    /**
     * Member ports
     */
    Port<bool> beam_in;
    Port<bool> signal_out;
    
    /**
     * Constructor
     */
    Odu(const std::string id) : Atomic<OduState>(id, OduState()) {
        // Initialize ports
        beam_in = addInPort<bool>("beam_in");
        signal_out = addOutPort<bool>("signal_out");
    }

    /**
     * Internal transition function (delta_int)
     */
    void internalTransition(OduState& state) const override {

        // Switch on state
        switch (state.s) {
            // Case: PASSIVE
            case OduStateName::PASSIVE:
                state.s = OduStateName::ACQUIRE_LOCK;
                break;
            // Case: ACQUIRE_LOCK
            case OduStateName::ACQUIRE_LOCK:
                state.s = OduStateName::TX_RX;
                break;
            // Case: TX_RX
            case OduStateName::TX_RX:
                state.s = OduStateName::RELEASE_LOCK;
                break;
            // Case: RELEASE_LOCK
            case OduStateName::RELEASE_LOCK:
                state.s = OduStateName::PASSIVE;
                break;
            // Default:
            default:
                break;
        }

    }

    /**
     * External transition function (delta_ext)
     */
    void externalTransition(OduState& state, double e) const override {

        /* Input Port Handling */

        // Check input port for content
        if (!beam_in->empty()) {

            // Content of the port message (last only)
            const auto& port_message = beam_in->getBag().back();

            // Switch on state
            switch (state.s) {
                // Case: PASSIVE
                case OduStateName::PASSIVE:
                    // Case: beam_in?ON
                    if (port_message) {
                        state.lock = true;
                        state.s = OduStateName::ACQUIRE_LOCK;
                    }
                    break;
                // Case: TX_RX
                case OduStateName::TX_RX:
                    // Case: beam_in?ON
                    if (port_message) {
                        state.lock = true;
                        state.s = OduStateName::TX_RX;
                    }
                    // Case: beam_in?OFF
                    else {
                        state.lock = false;
                        state.s = OduStateName::RELEASE_LOCK;
                    }
                    break;
                // Default:
                default:
                    break;

            } // end switch
        } // end if

        /* Additional Handling */

        // Update sigma based on elapsed duration
        state.sigma -= e; 

    }
    
    
    /**
     * Output function (lambda)
     */
    void output(const OduState& state) const override {

        // Output corresponds to status of the lock
        signal_out->addMessage(state.lock);

    }

    /**
     * Time advance function (ta)
     */
    [[nodiscard]] double timeAdvance(const OduState& state) const override {     
        // Switch on state
        switch (state.s) {
            case OduStateName::PASSIVE:
            case OduStateName::TX_RX:
                return std::numeric_limits<double>::infinity();
                break;
            case OduStateName::ACQUIRE_LOCK:
                return ACQUIRE_LOCK_TIME;
                break;
            case OduStateName::RELEASE_LOCK:
                return RELEASE_LOCK_TIME;
                break;
            default:
                return 1.0;
                break;
        }
    }

};

#endif
