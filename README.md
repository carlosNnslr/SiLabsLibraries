# Libraries SiLabs

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

You will need those files:

* masterConfig.c -> needed to configure all other functions with the correct hardware
* masterConfig.h -> you always need the coresponding ".h"
* functionX.c    -> any function in this Git
* functionX.h    -> you always need the coresponding ".h"

      Then open the masterConfig.c and choose your microcontroller and any other important configs needed.
      Just include the masterConfig ".c" and ".h" and any function ".c" and ".h" you need and your ready to go
