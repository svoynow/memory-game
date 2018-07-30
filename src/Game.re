[%%debugger.chrome];

open Belt.Result;

type gameCard = Tableau.Item.t;

type turnState =
  | NotStarted
  | OneCardFlipped(gameCard)
  | TwoCardsFlipped(gameCard, gameCard);

type cardState =
  | FaceUp
  | FaceDown
  | Paired;

type t = {
  tableau: Tableau.t,
  turnState,
};

type action =
  | SelectFirst(gameCard)
  | SelectSecond(gameCard)
  | Reset
  | ClaimPair;

let hasMatch = state =>
  switch (state) {
  | TwoCardsFlipped(a, b) when Tableau.Item.isMatch(a, b) => true
  | _ => false
  };

let doAction = (action, {turnState, tableau}) =>
  switch (turnState, action) {
  | (NotStarted, SelectFirst(card))
      when Tableau.getItemState(tableau, card) == Tableau.Item.FaceDown =>
    Ok({
      tableau: Tableau.flipCard(tableau, card),
      turnState: OneCardFlipped(card),
    })

  | (OneCardFlipped(flipped), SelectSecond(card))
      when Tableau.getItemState(tableau, card) == Tableau.Item.FaceDown =>
    Ok({
      tableau: Tableau.flipCard(tableau, card),
      turnState: TwoCardsFlipped(flipped, card),
    })

  | (TwoCardsFlipped(a, b), ClaimPair) when hasMatch(turnState) =>
    Ok({tableau: Tableau.pairCards(tableau, [a, b]), turnState: NotStarted})

  | (TwoCardsFlipped(a, b), Reset) when ! hasMatch(turnState) =>
    Ok({
      tableau: Tableau.resetCards(tableau, [a, b]),
      turnState: NotStarted,
    })
  | (_, _) => Error("I'm sorry Dave, I'm afraid I can't do that.")
  };

let initialize = () => {
  let deck = Deck.makeDeck();
  {tableau: Tableau.makeTableau(deck, ~numPairs=8), turnState: NotStarted};
};