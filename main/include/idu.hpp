#ifndef IDU_HPP
#define IDU_HPP

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
enum class IduStateName {
    PASSIVE,
    CONNECTING,
    DISCONNECTING,
    MOD_DEMOD
};

/**
 * operator<< overload definition.
 *
 * Defines the output format of the IduStateName enum class.
 */
std::ostream& operator<<(std::ostream& os, IduStateName state_name) {
    switch (state_name) {
        case IduStateName::PASSIVE:
            os << "PASSIVE";
            break;
        case IduStateName::CONNECTING:
            os << "CONNECTING";
            break;
        case IduStateName::DISCONNECTING:
            os << "DISCONNECTING";
            break;
        case IduStateName::MOD_DEMOD:
            os << "MOD_DEMOD";
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
struct IduState {
    /**
     * Members
     */
    double sigma;
    IduStateName s;
    // RF chain indicators
    bool chain1_up;
    bool chain2_up;
    
    /**
     * Constructor
     */
    explicit IduState(): sigma(std::numeric_limits<double>::infinity()), s(IduStateName::PASSIVE), chain1_up(false), chain2_up(false) {
    }

    /**
     * Methods
     */

    // Return true if a link is up (ie. at least one chain up)
    bool link_up() const { return chain1_up || chain2_up; }
    
};

/**
 * operator<< overload definition.
 *
 * Defines the output format to a given file stream using this model's state variables.
 */
std::ostream& operator<<(std::ostream &out, const IduState& state) {
    out << "{" 
            << "state=" << state.s << ", "
            << "sigma=" << state.sigma << ", "
            << "chain1_up=" << state.chain1_up << ", "
            << "chain2_up=" << state.chain2_up
        << "}";
    return out;
}

/**
 * Atomic model class definition.
 *
 * Extends the Cadmium V2 `Atomic` class.
 */
class Idu : public Atomic<IduState> {

private:

public:

    /**
     * Constants
     */
    static constexpr double CONNECTING_TIME = 1.00;
    static constexpr double DISCONNECTING_TIME = 0.50;

    /**
     * Member ports
     */
    Port<bool> signal_in1;
    Port<bool> signal_in2;
    Port<bool> idu_out;

    /**
     * Constructor
     */
    Idu(const std::string id) : Atomic<IduState>(id, IduState()) {
        // Initialize ports
        signal_in1 = addInPort<bool>("signal_in1");
        signal_in2 = addInPort<bool>("signal_in2");
        idu_out = addOutPort<bool>("idu_out");
    }

    /**
     * Internal transition function (delta_int)
     */
    void internalTransition(IduState& state) const override {

        // Switch on state
        switch (state.s) {
            // Case: PASSIVE
            case IduStateName::PASSIVE:
                state.s = IduStateName::CONNECTING;
                break;
            // Case: CONNECTING
            case IduStateName::CONNECTING:
                state.s = IduStateName::MOD_DEMOD;
                break;
            // Case: MOD_DEMOD
            case IduStateName::MOD_DEMOD:
                // At least one chain is up; continue modulating/demodulating on link
                if (state.link_up()) {
                    state.s = IduStateName::MOD_DEMOD;
                }
                // All chains down; therefore, link is down
                else {
                    state.s = IduStateName::DISCONNECTING;
                }
                break;
            // Case: DISCONNECTING
            case IduStateName::DISCONNECTING:
                state.s = IduStateName::PASSIVE;
                break;
            // Default:
            default:
                break;
        }
    }

    /**
     * External transition function (delta_ext)
     */
    void externalTransition(IduState& state, double e) const override {

        /* Input Port Handling */

        // Check signal_in1 port for content
        if (!signal_in1->empty()) {

            // Content of the port message (last only)
            const auto& port_message = signal_in1->getBag().back();

            // Switch on state
            switch (state.s) {
                // Case: PASSIVE
                case IduStateName::PASSIVE:
                    // Case: signal_in1?ON
                    if (port_message) {
                        state.chain1_up = true;
                        state.s = IduStateName::CONNECTING;
                    }
                    break;
                // Case: MOD_DEMOD
                case IduStateName::MOD_DEMOD:
                    // Case: signal_in1?ON
                    if (port_message) {
                        state.chain1_up = true;
                        state.s = IduStateName::MOD_DEMOD;
                    }
                    // Case: signal_in1?OFF
                    else {
                        state.chain1_up = false;
                        // Case: At least one chain up
                        if (state.link_up()) {
                            state.s = IduStateName::MOD_DEMOD;
                        }
                        // Case: No chains up
                        else {
                            state.s = IduStateName::DISCONNECTING;
                        }
                    }
                    break;
                default:
                    break;
            } // end switch
        } // end if


        // Check signal_in2 port for content
        if (!signal_in2->empty()) {

            // Content of the port message (last only)
            const auto& port_message = signal_in2->getBag().back();

            // Switch on state
            switch (state.s) {
                // Case: PASSIVE
                case IduStateName::PASSIVE:
                    // Case: signal_in2?ON
                    if (port_message) {
                        state.chain2_up = true;
                        state.s = IduStateName::CONNECTING;
                    }
                    break;
                // Case: MOD_DEMOD
                case IduStateName::MOD_DEMOD:
                    // Case: signal_in2?ON
                    if (port_message) {
                        state.chain2_up = true;
                        state.s = IduStateName::MOD_DEMOD;
                    }
                    // Case: signal_in2?OFF
                    else {
                        state.chain2_up = false;
                        // Case: At least one chain up
                        if (state.link_up()) {
                            state.s = IduStateName::MOD_DEMOD;
                        }
                        // Case: No chains up
                        else {
                            state.s = IduStateName::DISCONNECTING;
                        }
                    }
                    break;
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
    void output(const IduState& state) const override {

        // Output corresponds to status of the link
        idu_out->addMessage(state.link_up());

    }

    /**
     * Time advance function (ta)
     */
    [[nodiscard]] double timeAdvance(const IduState& state) const override {     
        
        // Switch on state
        switch (state.s) {
            case IduStateName::PASSIVE:
            case IduStateName::MOD_DEMOD:
                return std::numeric_limits<double>::infinity();
                break;
            case IduStateName::CONNECTING:
                return CONNECTING_TIME;
                break;
            case IduStateName::DISCONNECTING:
                return DISCONNECTING_TIME;
                break;
            default:
                return 1.0;
                break;
        }
    }

};

#endif
