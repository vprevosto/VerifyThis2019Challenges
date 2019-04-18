.PHONY: %-check

%-check:
	frama-c -wp -wp-rte \
                -wp-prover script,alt-ergo,Z3 \
                -wp-split \
                -wp-session $*-proofs \
                -wp-par 1 \
                -wp-timeout 15 \
                $*.c
