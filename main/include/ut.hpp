#ifndef UT_HPP
#define UT_HPP

// Cadmium V2
#include "cadmium/modeling/devs/coupled.hpp"

// Project atomic models
#include "idu.hpp"
#include "odu.hpp"

using namespace cadmium;

struct Ut : public Coupled {

    /**
     * Member ports (external)
     */
    Port<bool> beam_in1;
    Port<bool> beam_in2;
    Port<bool> ut_out;

    /**
     * Constructor for top coupled model.
     *
     * @param id ID of the model.
     */
    Ut(const std::string& id) : Coupled(id) {
        // Model declaration
        auto idu = addComponent<Idu>("IDU");
        auto odu1 = addComponent<Odu>("Odu1");
        auto odu2 = addComponent<Odu>("Odu2");

        // Initialize external ports
        beam_in1 = addInPort<bool>("beam_in1");
        beam_in2 = addInPort<bool>("beam_in2");
        ut_out = addOutPort<bool>("ut_out");

        // External port coupling
        addCoupling(beam_in1, odu1->beam_in);
        addCoupling(beam_in2, odu2->beam_in);
        addCoupling(idu->idu_out, ut_out);

        // Internal port coupling
        addCoupling(odu1->signal_out, idu->signal_in1);
        addCoupling(odu2->signal_out, idu->signal_in2);
    }

};

#endif
