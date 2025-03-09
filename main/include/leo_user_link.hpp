#ifndef LEO_USER_LINK_HPP
#define LEO_USER_LINK_HPP

// Cadmium V2
#include "cadmium/modeling/devs/coupled.hpp"

// Project atomic models
#include "ul.hpp"

using namespace cadmium;

struct LeoUserLink : public Coupled {

    /**
     * Constructor for top coupled model.
     *
     * @param id ID of the model.
     */
    LeoUserLink(const std::string& id) : Coupled(id) {
        auto ul = addComponent<Ul>("UL");
    }

};

#endif

