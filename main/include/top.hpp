#ifndef TOP_HPP
#define TOP_HPP

// Cadmium V2
#include "cadmium/modeling/devs/coupled.hpp"

// Project atopmic models
#include "atomic_model.hpp"

using namespace cadmium;

struct TopCoupledOduTest : public Coupled {

    /**
     * Constructor for top coupled model.
     *
     * @param id ID of the model.
     */
    TopCoupledOduTest(const std::string& id) : Coupled(id) {
        auto atomic_1 = addComponent<Odu>("ODU");
        auto atomic_2 = addComponent<Odu>("ODU_DRIVER");
    }

};

#endif
