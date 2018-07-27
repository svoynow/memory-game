type state;

type group;

type t = {
  animal: Animal.t,
  group,
  state,
};

let makePair: Animal.t => list(t);
let key: t => string;
let imageUrl: t => string;
let isMatch: (t, t) => bool;
let isSameCard: (t, t) => bool;
let flip: t => t;
let reset: t => t;