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
enum class StateName {
    PASSIVE,
    ACQUIRE_LOCK,
    TX_RX
};

/**
 * operator<< overload definition.
 *
 * Defines the output format of the StateName enum class.
 */
std::ostream& operator<<(std::ostream& os, StateName state_name) {
    switch (state_name) {
        case StateName::PASSIVE:
            os << "PASSIVE";
            break;
        case StateName::ACQUIRE_LOCK:
            os << "ACQUIRE_LOCK";
            break;
        case StateName::TX_RX:
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
    StateName s;
    
    /**
     * Constructor
     */
    explicit OduState(): sigma(std::numeric_limits<double>::infinity()), s(StateName::PASSIVE) {
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
            << "sigma=" << state.sigma 
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
    static constexpr double LOCK_TIME = 2.00;

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

        // Case: ACQUIRE_LOCK
        if (state.s == StateName::ACQUIRE_LOCK) {
            // Update state
            state.s = StateName::TX_RX;
            // Update sigma
            state.sigma = std::numeric_limits<double>::infinity();
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
                case StateName::PASSIVE:
                    // Case: beam_in?ON
                    if (port_message) {
                        // Update state
                        state.s = StateName::ACQUIRE_LOCK;
                        // Update sigma
                        state.sigma = LOCK_TIME;
                    }
                    break;
                // Case: TX_RX
                case StateName::TX_RX:
                    // Case: beam_in?OFF
                    if (!port_message) {
                        // Update state
                        state.s = StateName::PASSIVE;
                        // Update sigma
                        state.sigma = std::numeric_limits<double>::infinity();
                    }
                    break;
                // Default:
                // Case: ACQUIRE_LOCK
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

        // Port message to write to port
        bool port_message = false;

        // Switch on state
        switch (state.s) {
            // Case: ACQUIRE_LOCK
            case StateName::ACQUIRE_LOCK:
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

    }

    /**
     * Time advance function (ta)
     */
    [[nodiscard]] double timeAdvance(const OduState& state) const override {     

        //// Switch on state
        //switch (state.s) {
        //    // Case: ACQUIRE_LOCK
        //    case StateName::ACQUIRE_LOCK:
        //        state.sigma = LOCK_TIME;
        //        break;
        //    // Default:
        //    // Case: PASSIVE
        //    // Case: TX_RX
        //    default:
        //        state.sigma = std::numeric_limits<double>::infinity();
        //        break;
        //}

        return state.sigma;
    }

};

#endif
