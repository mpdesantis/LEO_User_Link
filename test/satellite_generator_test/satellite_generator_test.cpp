// std
#include <limits>

// Models
#include "cm_satellite_test.hpp"

// Cadmium V2
#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"

using namespace cadmium;

int main() {

    /**
     * TEST: ODU
     */

    // Top model
	auto model = std::make_shared<CmSatelliteTest> ("CmSatelliteTest");
    double simulation_duration = 60.00;

    // Root coordinator
	auto rootCoordinator = RootCoordinator(model);

    // `stdout` logging
	//rootCoordinator.setLogger<STDOUTLogger>(";");

    // CSV file logging
	rootCoordinator.setLogger<CSVLogger>("output/satellite_generator_test.csv", ";");

    // Start the root coordinator
	rootCoordinator.start();
    // Begin simulation
	rootCoordinator.simulate(simulation_duration);
    // Stop simulation
	rootCoordinator.stop();	

	return 0;
}

