[%%debugger.chrome];

type t = list(Card.t);

let makeDeck = () =>
  MyRandom.sample(Animal.all, 8)
  |> List.map(Card.makePair)
  |> List.concat
  |> Belt.List.shuffle;

let flipCard = (deck, card) =>
  List.map(c => c == card ? Card.flip(card) : c, deck);

let resetCard = (deck, card) =>
  List.map(c => c == card ? Card.reset(card) : c, deck);