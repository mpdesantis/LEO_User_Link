// std
#include <limits>

// Models
#include "leo_user_link.hpp"

// Cadmium V2
#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"

using namespace cadmium;

int main() {

    /**
     * TOP MODEL: LEO USER LINK
     */

    // Top model
    auto model = std::make_shared<LeoUserLink> ("LeoUserLink");
    double simulation_duration = 240.00;

    // Root coordinator
    auto rootCoordinator = RootCoordinator(model);

    // CSV file logging
    rootCoordinator.setLogger<CSVLogger>("output/leo_user_link.csv", ";");

    // Start the root coordinator
    rootCoordinator.start();
    // Begin simulation
    rootCoordinator.simulate(simulation_duration);
    // Stop simulation
    rootCoordinator.stop();

    return 0;
}


