#ifndef TOP_ODU_HPP
#define TOP_ODU_HPP

// Cadmium V2
#include "cadmium/modeling/devs/coupled.hpp"

// Project atomic models
#include "odu.hpp"

using namespace cadmium;

struct TopCoupledOduTest : public Coupled {

    /**
     * Constructor for top coupled model.
     *
     * @param id ID of the model.
     */
    TopCoupledOduTest(const std::string& id) : Coupled(id) {
        auto atomic_1 = addComponent<Odu>("ODU");
        //auto atomic_2 = addComponent<Odu>("ODU_DRIVER");
    }

};

#endif
