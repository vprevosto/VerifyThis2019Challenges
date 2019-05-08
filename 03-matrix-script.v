(* Generated by Frama-C WP *)

Goal typed_lemma_assoc.
Hint assoc,property.
Proof.
intros a b c.
unfold to_sint32.
unfold to_range.
elim (Z.add_cancel_l ((a + (-2147483648 + (c + b - -2147483648) mod (2147483648 - -2147483648)) - -2147483648)
mod (2147483648 - -2147483648)) ((c + (-2147483648 + (b + a - -2147483648) mod (2147483648 - -2147483648)) - -2147483648)
mod (2147483648 - -2147483648)) (-2147483648)).
intros _ H1; apply H1; clear H1.
replace (a + (-2147483648 + (c + b - -2147483648) mod (2147483648 - -2147483648)) - -2147483648) with
(a + (c + b - -2147483648) mod (2147483648 - -2147483648)); auto with zarith.
replace (c + (-2147483648 + (b + a - -2147483648) mod (2147483648 - -2147483648)) - -2147483648) with
(c + (b+a - -2147483648) mod (2147483648 - - 2147483648)); auto with zarith.
rewrite (Zplus_mod_idemp_r (c + b - -2147483648) a (2147483648 - -2147483648)).
rewrite (Zplus_mod_idemp_r (b + a - -2147483648) c (2147483648 - -2147483648)).
replace (a + (c + b - -2147483648)) with (c + (b + a - -2147483648)); auto with zarith.
Qed.

