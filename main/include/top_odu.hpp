#ifndef TOP_ODU_HPP
#define TOP_ODU_HPP

// Cadmium V2
#include "cadmium/modeling/devs/coupled.hpp"

// Project atomic models
#include "odu.hpp"

using namespace cadmium;

struct top_coupled : public Coupled {

    /**
     * Constructor for top coupled model.
     *
     * @param id ID of the model.
     */
    top_coupled(const std::string& id) : Coupled(id) {
        auto atomic_odu1 = addComponent<atomic_model>("ODU1");
    }

};

#endif
