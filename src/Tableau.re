module Item = {
  type cardState =
    | FaceUp
    | FaceDown
    | Paired;

  type t = {
    card: Card.t,
    cardState,
  };

  let isMatch = ({card: a}, {card: b}) => Card.isMatch(a, b);
  let isSame = ({card: a}, {card: b}) => Card.isSameCard(a, b);

  let toString = ({card: {Card.animal}}) => Animal.toString(animal);

  let initialize = card => {card, cardState: FaceDown};

  let image = ({cardState, card}) =>
    switch (cardState) {
    | FaceUp => Card.imageUrl(card)
    | FaceDown => "blue.svg"
    | Paired => "x.png"
    };
};

type t = list(Item.t);

let getItemState = (tableau, item) =>
  List.filter(Item.isSame(item), tableau) |> List.hd |> (c => c.cardState);

let pairsFound = tableau =>
  (
    tableau
    |> List.filter(({Item.cardState}) => cardState == Paired)
    |> List.length
  )
  / 2;

let complete = tableau => pairsFound(tableau) * 2 == List.length(tableau);

let changeItemState = (tableau, item, newState) =>
  List.map(
    it => Item.isSame(item, it) ? {...item, cardState: newState} : it,
    tableau,
  );

let changePairState = (tableau, (a, b), fn) => fn(fn(tableau, a), b);

let changeItemsState = (tableau, cards, fn) =>
  List.fold_left((t, c) => fn(t, c), tableau, cards);

let flipCard = (tableau, gameCard) =>
  changeItemState(tableau, gameCard, FaceUp);
let resetCard = (tableau, gameCard) =>
  changeItemState(tableau, gameCard, FaceDown);
let pairCard = (tableau, gameCard) =>
  changeItemState(tableau, gameCard, Paired);

let resetCards = (tableau, cards) =>
  changeItemsState(tableau, cards, resetCard);
let pairCards = (tableau, cards) =>
  changeItemsState(tableau, cards, pairCard);

let makeTableau = (deck, ~numPairs) =>
  deck
  |. Belt.List.take(numPairs * 2)
  |. Belt.Option.getWithDefault(deck)
  |. Belt.List.shuffle
  |> List.map(Item.initialize);