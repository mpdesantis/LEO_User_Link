#ifndef TOP_HPP
#define TOP_HPP

// Cadmium V2
#include "cadmium/modeling/devs/coupled.hpp"

// Project atopmic models
#include "atomic_model.hpp"

using namespace cadmium;

struct top_coupled : public Coupled {

    /**
     * Constructor for top coupled model.
     *
     * @param id ID of the model.
     */
    top_coupled(const std::string& id) : Coupled(id) {
        auto atomic_1 = addComponent<atomic_model>("model 1");
    }

};

#endif
