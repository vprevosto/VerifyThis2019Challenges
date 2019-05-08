.PHONY: %-check

COMMONOPTS=-wp -wp-rte -wp-split $(EXTRAOPTS) \
           -wp-session $*-proofs -wp-script $*-script.v

%-check:
	frama-c $(COMMONOPTS) \
                -wp-prover script,alt-ergo,Z3,coq \
                -wp-par 1 \
                -wp-timeout 15 \
                $*.c
%-gui:
	frama-c-gui $(COMMONOPTS) \
                    -wp-prover alt-ergo,Z3,tip,coq \
                    -wp-par 8 \
                    $*.c

03-matrix-%: EXTRAOPTS=-no-warn-signed-overflow
