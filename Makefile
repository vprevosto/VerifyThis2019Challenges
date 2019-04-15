.PHONY: 01-monotonic

01-monotonic:
	frama-c -wp -wp-rte \
                -wp-prover script,alt-ergo,Z3 \
                -wp-split \
                -wp-session 01-monotonic-proofs \
                -wp-par 1 \
                -wp-timeout 15 \
                01-monotonic.c
