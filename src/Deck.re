[%%debugger.chrome];

type t = list(Card.t);

let makeDeck = pairs =>
  MyRandom.sample(Animal.all, pairs)
  |> List.map(Card.makePair)
  |> List.concat
  |> Belt.List.shuffle;

let flipCard = (deck, card) =>
  List.map(c => Card.isSameCard(card, c) ? Card.flip(card) : c, deck);

let resetCard = (deck, card) =>
  List.map(c => Card.isSameCard(card, c) ? Card.reset(card) : c, deck);