#include <limits>
#include "include/top.hpp"
#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"

using namespace cadmium;

int main() {

    // Top model
	auto model = std::make_shared<top_coupled> ("top");

    // Root coordinator
	auto rootCoordinator = RootCoordinator(model);

    // `stdout` logging
	// rootCoordinator.setLogger<STDOUTLogger>(";");

    // CSV file logging
	rootCoordinator.setLogger<CSVLogger>("top_model_output.csv", ";");

    // Start the root coordinator
	rootCoordinator.start();
    // Begin simulation
	rootCoordinator.simulate(10.1);
    // Stop simulation
	rootCoordinator.stop();	

	return 0;
}

