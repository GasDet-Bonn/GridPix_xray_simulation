#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Garfield/MediumMagboltz.hh>

int main(int argc, char* argv[]) {
    // Check if a gasfile was provided.
    if (argc != 2) {
        std::cerr << "No gasfile was provided." << std::endl;
        return 1;
    }

    // Get the filename of the gasfile from the arguments
    std::string filename = argv[1];

    // Create a Garfield medium based on the provided gasfile
    Garfield::MediumMagboltz* gas = new Garfield::MediumMagboltz();
    if (!gas->LoadGasFile(filename)) {
        std::cerr << "Error while reading the gasfile." << std::endl;
        return 1;
    }

    // Initialise variables to store the results from the gasfile
    std::vector<double> efields;
    std::vector<double> bfields;
    std::vector<double> angles;
    double driftVelocity = 0.0;
    double diffusionTransversal = 0.0;
    double diffusionLongitudinal = 0.0;
    
    // Get the parameters from the gasfile
    gas->GetFieldGrid(efields, bfields, angles);
    gas->GetElectronVelocityE(0, 0, 0, driftVelocity);
    gas->GetElectronTransverseDiffusion(0, 0, 0, diffusionTransversal);
    gas->GetElectronLongitudinalDiffusion(0, 0, 0, diffusionLongitudinal);

    // Print out the results
    std::cout << "Electric field: " << efields[0] << " V/cm" << std::endl;
    std::cout << "Drift velocity: " << driftVelocity*10000 << " µm/ns" << std::endl;
    std::cout << "Transversal diffusion coefficient: " << diffusionTransversal*10000 << " µm/sqrt(cm)" << std::endl;
    std::cout << "Longitudinal diffusion coefficient: " << diffusionLongitudinal*10000 << " µm/sqrt(cm)" << std::endl;

    delete gas;
    return 0;
}
