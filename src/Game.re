[%%debugger.chrome];

open Belt.Result;

type turnState =
  | NotStarted
  | OneCardFlipped(Card.t)
  | TwoCardsFlipped(Card.t, Card.t);

type t = {
  deck: Deck.t,
  turnState,
  paired: array(Animal.t),
};

type action =
  | SelectFirst(Card.t)
  | SelectSecond(Card.t)
  | Reset
  | ClaimPair;

let addPair = (paired, animal) =>
  Array.append(paired, Array.of_list([animal]));

let doAction = (a, {turnState, deck, paired} as game) =>
  switch (turnState, a) {
  | (NotStarted, SelectFirst(card)) =>
    Ok({
      ...game,
      deck: Deck.flipCard(deck, card),
      turnState: OneCardFlipped(Card.flip(card)),
    })
  | (OneCardFlipped(flipped), SelectSecond(card)) =>
    Ok({
      ...game,
      deck: Deck.flipCard(deck, card),
      turnState: TwoCardsFlipped(flipped, Card.flip(card)),
    })
  | (TwoCardsFlipped(a, b), ClaimPair) when Card.isMatch(a, b) =>
    Ok({
      paired: addPair(paired, a.Card.animal),
      deck: Deck.resetCard(Deck.resetCard(deck, a), b),
      turnState: NotStarted,
    })
  | (TwoCardsFlipped(a, b), Reset) when ! Card.isMatch(a, b) =>
    Ok({
      ...game,
      deck: Deck.resetCard(Deck.resetCard(deck, a), b),
      turnState: NotStarted,
    })
  | (_, _) =>
    Js.log("illegal transition");
    Error("I'm sorry Dave, I'm afraid I can't do that.");
  };

let initialize = () => {
  let deck = Deck.makeDeck(8);
  {deck, turnState: NotStarted, paired: Array.of_list([])};
};

let displayCard = ({paired}, {Card.animal}) =>
  ! Js.Array.includes(animal, paired);