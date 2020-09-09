.PHONY: %-check

COMMONOPTS=-wp -wp-rte -wp-split $(EXTRAOPTS) \
           -wp-cache update \
           -wp-session $*-proofs -wp-coq-script $*-script.v

%-check:
	frama-c $(COMMONOPTS) \
                -wp-prover script,alt-ergo,native:coq \
                -wp-par 1 \
                -wp-timeout 15 \
                $*.c
%-gui:
	frama-c-gui $(COMMONOPTS) \
                    -wp-prover alt-ergo,tip \
                    -wp-par 8 \
                    $*.c

03-matrix-%: EXTRAOPTS=-no-warn-signed-overflow
