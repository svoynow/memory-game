open Belt.Result;

type gameCard = Tableau.Item.t;

type turnState =
  | NotStarted
  | OneCardFlipped(gameCard)
  | TwoCardsFlipped(gameCard, gameCard)
  | GameComplete;

type cardState =
  | FaceUp
  | FaceDown
  | Paired;

type t = {
  tableau: Tableau.t,
  turnState,
};

type action =
  | SelectCard(gameCard)
  | Continue
  | Reset;

let initialize = () => {
  let deck = Deck.makeDeck();
  {tableau: Tableau.makeTableau(deck, ~numPairs=8), turnState: NotStarted};
};

let hasMatch = state =>
  switch (state) {
  | TwoCardsFlipped(a, b) when Tableau.Item.isMatch(a, b) => true
  | _ => false
  };

let doAction = (action, {turnState, tableau}) =>
  switch (turnState, action) {
  | (NotStarted, SelectCard(card))
      when Tableau.getItemState(tableau, card) == Tableau.Item.FaceDown =>
    Ok({
      tableau: Tableau.flipCard(tableau, card),
      turnState: OneCardFlipped(card),
    })

  | (OneCardFlipped(flipped), SelectCard(card))
      when Tableau.getItemState(tableau, card) == Tableau.Item.FaceDown =>
    Ok({
      tableau: Tableau.flipCard(tableau, card),
      turnState: TwoCardsFlipped(flipped, card),
    })

  | (TwoCardsFlipped(a, b), Continue) when hasMatch(turnState) =>
    let tableau = Tableau.pairCards(tableau, [a, b]);
    Ok({
      tableau,
      turnState: Tableau.complete(tableau) ? GameComplete : NotStarted,
    });
  | (TwoCardsFlipped(a, b), Continue) when ! hasMatch(turnState) =>
    Ok({
      tableau: Tableau.resetCards(tableau, [a, b]),
      turnState: NotStarted,
    })
  | (_, Reset) => Ok(initialize())
  | (_, _) => Error("Nope")
  };