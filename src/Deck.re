type t = list(Card.t);

let makeDeck = () =>
  Animal.all |> Belt.List.shuffle |> List.map(Card.makePair) |> List.concat;