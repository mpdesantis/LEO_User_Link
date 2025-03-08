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
    static constexpr double LOCK_TIME = 8.00;

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

        std::cout << "ODU::" << __func__ << " entry state: " << state.s << std::endl;

        // DEBUG: Occurs only when we LEAVE ACQUIRE_LOCK
        // Case: ACQUIRE_LOCK
        if (state.s == OduStateName::ACQUIRE_LOCK) {
            // Update state
            state.s = OduStateName::TX_RX;
            // Update sigma
            state.sigma = std::numeric_limits<double>::infinity();
            // Update lock
            state.lock = true;
        }

        std::cout << "ODU::" << __func__ << " final state: " << state.s << std::endl;

    }

    /**
     * External transition function (delta_ext)
     */
    void externalTransition(OduState& state, double e) const override {

        std::cout << "ODU::" << __func__ << " entry state: " << state.s << std::endl;

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
                        // Update state
                        state.s = OduStateName::ACQUIRE_LOCK;
                        // Update sigma
                        state.sigma = LOCK_TIME;
                        // Update lock indicator
                        state.lock = true;
                    }
                    break;
                // Case: ACQUIRE_LOCK
                case OduStateName::ACQUIRE_LOCK:
                    // Case: beam_in?OFF
                    if (!port_message) {
                        // Update state
                        state.s = OduStateName::PASSIVE;
                        // Update sigma
                        state.sigma = std::numeric_limits<double>::infinity();
                        // Update lock indicator
                        state.lock = false;
                    }
                    break;
                // Case: TX_RX
                case OduStateName::TX_RX:
                    // Case: beam_in?OFF
                    if (!port_message) {
                        // Update state
                        state.s = OduStateName::PASSIVE;
                        // Update sigma
                        state.sigma = std::numeric_limits<double>::infinity();
                        // Update lock indicator
                        state.lock = false;
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

        std::cout << "ODU::" << __func__ << "::final state: " << state.s << std::endl;
    }
    
    
    /**
     * Output function (lambda)
     */
    void output(const OduState& state) const override {

        std::cout << "ODU::" << __func__ << " entry state: " << state.s << std::endl;

        // Port message to write to port
        bool port_message = false;

        // Switch on state
        switch (state.s) {
            // Case: ACQUIRE_LOCK
            case OduStateName::ACQUIRE_LOCK:
                // Output: signal_out!ON
                port_message = true;
                break;
            // Default:
            // Case: TX_RX
            default:
                // Output: signal_out!OFF
                port_message = false;
                break;
        }

        // Write the output port
        signal_out->addMessage(port_message);

        std::cout << "ODU::" << __func__ << " final state: " << state.s << std::endl;

    }

    /**
     * Time advance function (ta)
     */
    [[nodiscard]] double timeAdvance(const OduState& state) const override {     
        return state.sigma;
    }

};

#endif
