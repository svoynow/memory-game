type t = list(Card.t);

let makeDeck = () =>
  Animal.all |> List.map(Card.makePair) |> List.concat |> Belt.List.shuffle;