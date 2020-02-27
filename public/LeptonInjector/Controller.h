#ifndef LI_CONTROLLER
#define LI_CONTROLLER

#include <LeptonInjector.h> 
#include <Constants.h> // pi, GeV, degrees, meters, ... 
#include <DataWriter.h> // adds DataWriter class 
#include <iostream> // cout 

// Ben Smithers
// benjamin.smithers@mavs.uta.edu

// This defines the 'Controller' object that manages the overall process
// I tried to mimic the UX of working with IceTrays 

namespace LeptonInjector{

class Controller{
    private:
        // a deque (basically an array) to hold all of the base injectors. Will be filled with volume
        //      and ranged mode injectors 
        std::deque<LeptonInjectorBase*> generators;
        // prototypes of the above generators. When an injector is added, it is placed here. These all are later
        //      built with the default configurations to make the generators 
        std::vector<MinimalInjectionConfiguration> configs; 

        // seeds the random number generator 
        uint seed = 100;


        // overall generation parameters
        double minimumEnergy, maximumEnergy, powerlawIndex,
                minimumAzimuth, maximumAzimuth, minimumZenith, maximumZenith;
        
        // parameters used by ranged mode
        double injectionRadius, endcapLength;
        // parameters used by volume mode
        double cylinderRadius, cylinderHeight;

        // Earth's name, left here for historical reasons 
        std::string earthmodelname = "Earth";

        // Shared pointer refering to the Earth model used. 
        const std::shared_ptr<earthmodel::EarthModelService> earthModel = std::make_shared<earthmodel::EarthModelService>();
        // Shared pointer refering to the random number generator.
        const std::shared_ptr<LI_random> random = std::make_shared<LI_random>();

        // data file
        std::string out_file="./outfile.h";
        // configuration file 
        std::string lic_file="./config.lic";

        // default ranged mode configuration
        BasicInjectionConfiguration rangedConfig = BasicInjectionConfiguration();
        // default volume mode configuration
		BasicInjectionConfiguration volumeConfig = BasicInjectionConfiguration();

        // shared pointer to the object charged with interacting with the OS
        std::shared_ptr<DataWriter> datawriter = std::make_shared<DataWriter>();

        // verify acceptable arguments
        void Verify();

    public:
        // default constructor will just use some default minimal injection setup 
        Controller();

        // sending one will make a single little list... 
        Controller(MinimalInjectionConfiguration configs_received );
        // multilepton injector equivalent 

        // The BEST constructor
        Controller(MinimalInjectionConfiguration configs_received, double minimumEnergy,
            double maximumEnergy, double powerlawIndex, double minimumAzimuth, 
            double maximumAzimuth, double minimumZenith, double maximumZenith,
            double injectionRadius=1200*Constants::m, double endcapLength=1200*Constants::m, 
            double cylinderRadius=1200*Constants::m, double cylinderHeight= 1200*Constants::m);
        
        // changes the name used for the Earth
        void SetEarthModel( std::string new_name );
        // adds a new injector to be used in the process 
        void AddInjector(MinimalInjectionConfiguration configs_received);
        // changes the name of the data file
        void NameOutfile( std::string out_file );
        // changes the name of the configuration file 
        void NameLicFile( std::string lic_file );
        void setSeed( uint seedno ){this->seed = seedno ;}
        // executes the injector process with the configurated parameters 
        void Execute(); 



};

} // end namespace LeptonInjector

#endif
