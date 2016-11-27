.segment  "SBCSTART"

.import _init

.addr       _init ; Start address for loaded program 
                  ;  Put this at the top of the image
                  ;  so the loader can indirect jump
                  ;  to start
