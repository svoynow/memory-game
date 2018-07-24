type state;

type group;

type t = {
  animal: Animal.t,
  group,
  state,
};

let makePair: Animal.t => list(t);
let cmp: (t, t) => int;
let key: t => string;
let imageUrl: t => string;
let isMatch: (t, t) => bool;
let flip: t => t;
let reset: t => t;