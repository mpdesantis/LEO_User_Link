#ifndef DRIVER_HPP
#define DRIVER_HPP

// Standard includes
#include <random>
#include <iostream>

// Cadmium V2 includes
#include "cadmium/modeling/devs/atomic.hpp"

// Namespaces
using namespace cadmium;

namespace driver {

/**
 * Enum
 */
enum class StateName {
    SENDING
};

/**
 * operator<< overload definition.
 *
 * Defines the output format of the StateName enum class.
 */
std::ostream& operator<<(std::ostream& os, StateName state_name) {
    switch (state_name) {
        case StateName::SENDING:
            os << "SENDING";
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
struct DriverState {
    /**
     * Members
     */
    double sigma;
    StateName s;
    bool output_signal;
    
    /**
     * Constructor
     */
    explicit DriverState(): sigma(1), s(StateName::SENDING), output_signal(false) {
    }
};

/**
 * operator<< overload definition.
 *
 * Defines the output format to a given file stream using this model's state variables.
 */
std::ostream& operator<<(std::ostream &out, const DriverState& state) {
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
class Driver : public Atomic<DriverState> {

private:

public:

    /**
     * Constants
     */
    static constexpr double SEND_TIME_MIN = 0.10;
    static constexpr double SEND_TIME_MAX = 4.00;

    /**
     * Member ports
     */
    Port<bool> test_out;

    /**
     * Constructor
     */
    Driver(const std::string id) : Atomic<DriverState>(id, DriverState()) {
        // Initialize ports
        test_out = addOutPort<bool>("test_out");

    }

    /**
     * Internal transition function (delta_int)
     */
    void internalTransition(DriverState& state) const override {

        // Toggle ouput_signal so we send in alternation
        state.output_signal = !state.output_signal;
        // Update sigma with a random value in range
        randomizeSigma(state);
    }

    /**
     * External transition function (delta_ext)
     */
    void externalTransition(DriverState& state, double e) const override {
        // Update sigma based on elapsed duration
        state.sigma -= e; 
    }
    
    
    /**
     * Output function (lambda)
     */
    void output(const DriverState& state) const override {


        // Write the output port
        test_out->addMessage(state.output_signal);

    }

    /**
     * Time advance function (ta)
     */
    [[nodiscard]] double timeAdvance(const DriverState& state) const override {     
        return state.sigma;
    }

    /**
     * Get a random sigma within defined limits
     */
    void randomizeSigma(DriverState& state) const {     
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(SEND_TIME_MIN, SEND_TIME_MAX);
        state.sigma = dis(gen);
    }

};

} // end namespace driver

#endif
