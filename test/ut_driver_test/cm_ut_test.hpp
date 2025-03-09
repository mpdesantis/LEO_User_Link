#ifndef CM_UT_TEST_HPP
#define CM_UT_TEST_HPP

// Cadmium V2
#include "cadmium/modeling/devs/coupled.hpp"

// Project atomic models
#include "ut.hpp"
#include "driver.hpp"

using namespace cadmium;

struct CmUtTest : public Coupled {

    /**
     * Constructor for top coupled model.
     *
     * @param id ID of the model.
     */
    CmUtTest(const std::string& id) : Coupled(id) {
        auto driver1 = addComponent<driver::Driver>("DriverSatellite1");
        auto driver2 = addComponent<driver::Driver>("DriverSatellite2");
        auto ut = addComponent<Ut>("UT");

        addCoupling(driver1->test_out, ut->beam_in1);
        addCoupling(driver2->test_out, ut->beam_in2);
    }

};

#endif
