module Item: {
  type cardState =
    | FaceUp
    | FaceDown
    | Paired;

  type t = {
    card: Card.t,
    cardState,
  };

  let toString: t => string;

  let image: t => string;
  let isMatch: (t, t) => bool;
  let isSame: (t, t) => bool;
};

type t = list(Item.t);

let getItemState: (t, Item.t) => Item.cardState;

let pairsFound: t => int;

let flipCard: (t, Item.t) => t;

let resetCards: (t, list(Item.t)) => t;
let pairCards: (t, list(Item.t)) => t;

let makeTableau: (Deck.t, ~numPairs: int) => t;