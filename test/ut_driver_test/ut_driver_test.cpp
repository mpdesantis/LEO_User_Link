// std
#include <limits>

// Models
#include "cm_ut_test.hpp"

// Cadmium V2
#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"

using namespace cadmium;

int main() {

    /**
     * TEST: UT
     */

    // Top model
	auto model = std::make_shared<CmIduTest> ("CmUtTest");
    double simulation_duration = 40.00;

    // Root coordinator
	auto rootCoordinator = RootCoordinator(model);

    // `stdout` logging
	//rootCoordinator.setLogger<STDOUTLogger>(";");

    // CSV file logging
	rootCoordinator.setLogger<CSVLogger>("output/ut_driver_test.csv", ";");

    // Start the root coordinator
	rootCoordinator.start();
    // Begin simulation
	rootCoordinator.simulate(simulation_duration);
    // Stop simulation
	rootCoordinator.stop();	

	return 0;
}

