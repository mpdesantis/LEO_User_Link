#include <limits>
#include "include/top_odu.hpp"
//#include "include/odu.hpp"
#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"

using namespace cadmium;

int main() {

    // Top model
	auto model = std::make_shared<TopCoupledOduTest> ("TOP");

    // Root coordinator
	auto rootCoordinator = RootCoordinator(model);

    // `stdout` logging
	// rootCoordinator.setLogger<STDOUTLogger>(";");

    // CSV file logging
	rootCoordinator.setLogger<CSVLogger>("output/top_coupled_odu_test.csv", ";");

    // Start the root coordinator
	rootCoordinator.start();
    // Begin simulation
	rootCoordinator.simulate(20.00);
    // Stop simulation
	rootCoordinator.stop();	

	return 0;
}

