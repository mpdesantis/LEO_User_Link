#ifndef TOP_ODU_HPP
#define TOP_ODU_HPP

// Cadmium V2
#include "cadmium/modeling/devs/coupled.hpp"

// Project atomic models
#include "satellite.hpp"

using namespace cadmium;

struct CmSatelliteTest : public Coupled {

    /**
     * Constructor for top coupled model.
     *
     * @param id ID of the model.
     */
    CmSatelliteTest(const std::string& id) : Coupled(id) {
        auto atomic_1 = addComponent<Satellite>("Satellite1");
        auto atomic_2 = addComponent<Satellite>("Satellite2");
    }

};

#endif
