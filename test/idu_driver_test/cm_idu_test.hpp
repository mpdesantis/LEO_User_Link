#ifndef CM_IDU_TEST_HPP
#define CM_IDU_TEST_HPP

// Cadmium V2
#include "cadmium/modeling/devs/coupled.hpp"

// Project atomic models
#include "idu.hpp"
#include "driver.hpp"

using namespace cadmium;

struct CmIduTest : public Coupled {

    /**
     * Constructor for top coupled model.
     *
     * @param id ID of the model.
     */
    CmIduTest(const std::string& id) : Coupled(id) {
        auto driver1 = addComponent<driver::Driver>("DriverSatellite1");
        auto driver2 = addComponent<driver::Driver>("DriverSatellite2");
        auto idu = addComponent<Idu>("IDU");

        addCoupling(driver1->test_out, idu->signal_in1);
        addCoupling(driver2->test_out, idu->signal_in2);
    }

};

#endif
