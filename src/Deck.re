module type CardValue = {
  type t;
  let all: unit => list(t);
  let toString: t => string;
  let url: t => string;
};

type t = list(Card.t);

let makeDeck = () =>
  Animal.all |> Belt.List.shuffle |> List.map(Card.makePair) |> List.concat;