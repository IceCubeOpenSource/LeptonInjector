# Benjamin Smithers
# benjamin.smithers@mavs.uta.edu

# this example script ...
#   + imports the Nuzooka libraries 
#   + creates a muon Nuzooka, and its operator 
#   + tells the operator to fire 

import pylepton_injector as LI

# define the injector 
final_type1 = LI.Particle.MuPlus
final_type2 = LI.Particle.Hadrons
n_events    = 100
diff_xs     = "/home/benito/software/cross_sections/dsdxdy_nubar_CC_iso.fits"
total_xs    = "/home/benito/software/cross_sections/sigma_nubar_CC_iso.fits"
is_ranged   = True # use the ranged mode injection
# because the final state had a charged muon and hadrons, the event is the result of an antimuon neutrino undergoing a charged current interaction

# create the injector list using the above parameters
the_injector = LI.injector( n_events, final_type1, final_type2, diff_xs, total_xs, is_ranged)

deg = 3.13159/180.

minE        = 1000.
maxE        = 100000.
gamma       = 2. #unitless
minZenith   = 80.*deg
maxZenith   = 180.*deg
minAzimuth  = 0.*deg
maxAzimuth  = 180.*deg

# construct the controller 
controller  = LI.Controller( the_injector, minE, maxE, gamma, minAzimuth, maxAzimuth, minZenith, maxZenith)  
# injection radius and endcap length are left as defaults

# specify the output
Controller.Output("./data_output.h5")

# run the simulation
Controller.Execute()