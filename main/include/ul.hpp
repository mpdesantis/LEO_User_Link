#ifndef UL_HPP
#define UL_HPP

// Cadmium V2
#include "cadmium/modeling/devs/coupled.hpp"

// Project atomic models
#include "ut.hpp"
#include "satellite.hpp"

using namespace cadmium;

struct Ul : public Coupled {

    /**
     * Member ports (external)
     */
    Port<bool> link_out;

    /**
     * Constructor for top coupled model.
     *
     * @param id ID of the model.
     */
    Ul(const std::string& id) : Coupled(id) {
        // Initialize external ports
        link_out = addOutPort<bool>("link_out");

        // Model declaration
        auto satellite1 = addComponent<Satellite>("Satellite1");
        auto satellite2 = addComponent<Satellite>("Satellite2");
        auto ut = addComponent<Ut>("UT");

        // Internal port coupling
        addCoupling(satellite1->beam_out, ut->beam_in1);
        addCoupling(satellite2->beam_out, ut->beam_in2);

        // External port coupling
        addCoupling(ut->ut_out, link_out);

    }

};

#endif
