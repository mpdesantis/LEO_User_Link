// std
#include <limits>

// Models
// #include "include/top_odu.hpp"

// Cadmium V2
#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"

using namespace cadmium;

int main() {

    /**
     * TODO: Update when all atomic and coupled models are ready.
     */

    // Top model
	//auto model = std::make_shared<TopCoupledOduTest> ("leo_user_link");
    //double simulation_duration = 20.00;

    //// Root coordinator
	//auto rootCoordinator = RootCoordinator(model);

    //// `stdout` logging
	////rootCoordinator.setLogger<STDOUTLogger>(";");

    //// CSV file logging
	//rootCoordinator.setLogger<CSVLogger>("output/leo_user_link.csv", ";");

    //// Start the root coordinator
	//rootCoordinator.start();
    //// Begin simulation
	//rootCoordinator.simulate(simulation_duration);
    //// Stop simulation
	//rootCoordinator.stop();	

	return 0;
}

