# SiLabs Libraries

# Naming rules (Directories/Files)
To do:

* All names must use camelCase standards

To avoid:
  
* Characters to avoid while naming files

      Exemples: : / \
* non alphabetical or numeric characters

      Exemples: ¢ ™ $ ®
* Ponctuation, parenthesis, quotation marks , square bracket or operators

# Usage
If you use a masterConfig depending Function you will need those files:
(masterConfig depending Functions are located in the "masterConfigFunctions" folder)

* masterConfig.h -> needed to configure all other functions with the correct hardware
* functionX.c    -> any function in this Git
* functionX.h    -> you always need the coresponding ".h"

      Then open the masterConfig.c and choose your microcontroller and any other important configs needed.
      Just include the masterConfig and any function you need, then you're ready to go.

If you are using a non-depending function just pick up the ".c" and ".h" and include them
