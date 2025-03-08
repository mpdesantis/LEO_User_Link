#ifndef CM_ODU_TEST_HPP
#define CM_ODU_TEST_HPP

// Cadmium V2
#include "cadmium/modeling/devs/coupled.hpp"

// Project atomic models
#include "odu.hpp"
#include "driver.hpp"

using namespace cadmium;

struct CmOduTest : public Coupled {

    /**
     * Constructor for top coupled model.
     *
     * @param id ID of the model.
     */
    CmOduTest(const std::string& id) : Coupled(id) {
        auto atomic_1 = addComponent<driver::Driver>("Driver");
        auto atomic_2 = addComponent<Odu>("ODU");

        addCoupling(atomic_1->test_out, atomic_2->beam_in);
    }

};

#endif
