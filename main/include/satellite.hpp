#ifndef SATELLITE_HPP
#define SATELLITE_HPP

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
enum class SatelliteStateName {
    PASSIVE,
    ILLUMINATE
};

/**
 * operator<< overload definition.
 *
 * Defines the output format of the SatelliteStateName enum class.
 */
std::ostream& operator<<(std::ostream& os, SatelliteStateName state_name) {
    switch (state_name) {
        case SatelliteStateName::PASSIVE:
            os << "PASSIVE";
            break;
        case SatelliteStateName::ILLUMINATE:
            os << "ILLUMINATE";
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
struct SatelliteState {

    /**
     * Members
     */
    double sigma;
    SatelliteStateName s;
    bool signal;
    
    /**
     * Constructor
     */
    explicit SatelliteState(): sigma(1), s(SatelliteStateName::PASSIVE) {
    }
};



/**
 * operator<< overload definition.
 *
 * Defines the output format to a given file stream uwsing this model's state variables.
 */
std::ostream& operator<<(std::ostream &out, const SatelliteState& state) {
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
class Satellite : public Atomic<SatelliteState> {

private:

public:

    /**
     * Constants
     */
    static constexpr double PASSIVE_TIME_MIN = 6.00;
    static constexpr double PASSIVE_TIME_MAX = 12.00;
    static constexpr double ILLUMINATE_TIME_MIN = 8.00;
    static constexpr double ILLUMINATE_TIME_MAX = 16.00;

    /**
     * Member ports
     */
    Port<bool> beam_out;
    
    /**
     * Constructor
     */
    Satellite(const std::string id) : Atomic<SatelliteState>(id, SatelliteState()) {
        // Initialize ports
        beam_out = addOutPort<bool>("beam_out");
    }

    /**
     * Internal transition function (delta_int)
     */
    void internalTransition(SatelliteState& state) const override {
        // Case: PASSIVE
        if (state.s == SatelliteStateName::PASSIVE) {
            // Update state
            state.s = SatelliteStateName::ILLUMINATE;
            // Update signal indicator
            state.signal = false;
            // Update sigma 
            randomizeSigma(state, ILLUMINATE_TIME_MIN, ILLUMINATE_TIME_MAX);
        }
        // Case: ILLUMINATE
        else {
            // Update state
            state.s = SatelliteStateName::PASSIVE;
            // Update signal indicator
            state.signal = true;
            // Update sigma
            randomizeSigma(state, PASSIVE_TIME_MIN, PASSIVE_TIME_MAX);
        }
    }

    /**
     * External transition function (delta_ext)
     */
    void externalTransition(SatelliteState& state, double e) const override {
        // NA
    }
    
    
    /**
     * Output function (lambda)
     */
    void output(const SatelliteState& state) const override {
        // Write the output port
        beam_out->addMessage(state.signal);
    }

    /**
     * Time advance function (ta)
     */
    [[nodiscard]] double timeAdvance(const SatelliteState& state) const override {     
        return state.sigma;
    }

    /**
     * Get a random sigma within defined limits
     */
    void randomizeSigma(SatelliteState& state, double min, double max) const {     
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        state.sigma = dis(gen);
    }

};

#endif
