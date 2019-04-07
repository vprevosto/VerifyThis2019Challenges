# Team YVeTTe

- Virgile Prevosto (non-student)
- Virgile Robles (PhD student)
- From academia
- Tool used: Frama-C/WP plugin + Alt-Ergo and CVC4
- Team members are tool developers

# Challenge 1

We addressed part A. Implementation includes all required
functionalities, as proposed in the pseudo-code. The prototype of
the function requires the caller to provide a vector where the
output will be stored (this allows avoiding a dynamic allocation in
the function itself and has been done in Challenges 2 and 3 as well).

Specification includes the four properties (non-empty, begin-to-end,
within bounds and monotonic), without the maximal monotonic property.
Basic correctness is obtained by generating the corresponding
assertions with the `-wp-rte` option of `frama-c`.

All properties were verified with the exception of monotonicity.
A simplifying assumption has been made in that the length of the
input sequence is required to not be `SIZE_MAX` (the maximal value
that a `size_t` integer can attain). In addition, some invariants
that would be needed for proving monotonicity are also unproved.

Completing the proof would likely require some manual guidance using
the interactive TIP of WP and/or performing some steps within Coq.
In particular, WP tend to generate proof obligations that are not
automatically provable in presence of user-defined predicates on C
memory states.

Most effort was dedicated to add assertions and an intermediate lemma
to overcome WP limitations, as well as inspecting the unproved
verification conditions to understand where the problems were lying
(mostly involving memory separation properties that were not always
taken into account properly by the tool). No script has been
developed during the challenge.

Completing the verification should require the better part of a day.

Frama-C was chosen as the tool developed within the lab. Its
GUI and the TIP are helpful in understanding the verification issues
when they crop up. Main limitation reside in the way WP deals with
C memory states, with many abstractions that quickly hinder the ability
to prove seemingly trivial properties. Thus, the main possible
improvement would be to have a more flexible memory model.

# Challenge 2

We addressed part B. Implementation includes all required
functionalities. Again, the stack and the output sequence are
supposed to be given by the caller.

Specification includes the three verification tasks, and safety is
again checked with `-wp-rte`.

Only the first verification task has been sucessfully done. There
are probably some invariants missing for both of the other tasks,
and possibly some manual work to do to complete some parts of the
proof. Estimated completion time is a couple of days, especially
for better designing the invariants.

# Challenge 3

We addressed the first task. In addition to the output vector,
the caller is also supposed to provide a full representation of
the matrix (this ought to be a ghost parameter, but those will
only be supported in the forthcoming Frama-C version and not the
currently available one), that is used to specify what the result
of the multiplication should be.

Safety verification is not complete, as assertions guarding
arithmetic overflows in the additions and multiplications are
not verified: specifying that all operations are safe would be
very complicated, as well as switching to an unbounded integer library.

Functional verification is incomplete as well. The specification is
probably currently at a too abstract level to be directly verified
by automated tools and some intermediate lemmas should be introduced
to bridge the gap with the code. Finishing this verification should
take 1 or 2 days.

We did not attempt to deal with parallelism, as Frama-C does not really
handle it at this point.
