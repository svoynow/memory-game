[%%debugger.chrome];

open Helpers;

type action = Game.action;
type state = Game.t;

let reducer = (action, state) =>
  Belt.Result.mapWithDefault(
    Game.doAction(action, state), ReasonReact.NoUpdate, a =>
    ReasonReact.Update(a)
  );

let component = ReasonReact.reducerComponent("App");

let initialState = () => Game.initialize();

let buttonAction = ({ReasonReact.state: {Game.turnState}} as self) =>
  switch (turnState) {
  | TwoCardsFlipped(_a, _b) when Game.hasMatch(turnState) => (
      _ => self.send(Game.ClaimPair)
    )
  | TwoCardsFlipped(_a, _b) => (_ => self.send(Game.Reset))
  | _ => noOp
  };

let cardAction = ({ReasonReact.state: {Game.turnState}} as self, card) =>
  switch (turnState) {
  | NotStarted => (_ => self.send(Game.SelectFirst(card)))
  | OneCardFlipped(_card) => (_ => self.send(Game.SelectSecond(card)))
  | _ => noOp
  };

let message = ({Game.turnState}) =>
  switch (turnState) {
  | NotStarted => "Choose a card"
  | OneCardFlipped(card) =>
    "Try to find the other " ++ Tableau.Item.toString(card)
  | TwoCardsFlipped(_, _) when Game.hasMatch(turnState) => "A match! Click to continue."
  | TwoCardsFlipped(_, _) => "No match. Reset and try again"
  };

let renderCard = (self, {Tableau.Item.cardState, Tableau.Item.card} as item) =>
  switch (cardState) {
  | FaceDown
  | FaceUp =>
    <CardIcon
      card=item
      key=(Card.key(card))
      onClick=(cardAction(self, item))
    />
  | Paired =>
    <img
      className="card-image"
      src=(Tableau.Item.image(item))
      key=(Card.key(card))
    />
  };

let make = _children => {
  ...component,
  initialState,
  reducer,
  render: ({ReasonReact.state: {Game.tableau} as state} as self) =>
    <div className="app">
      <div className="grid">
        (
          List.map(c => renderCard(self, c), tableau)
          |> Array.of_list
          |> ReasonReact.array
        )
      </div>
      <div className="message">
        (
          switch (state.turnState) {
          | NotStarted
          | OneCardFlipped(_) => str(message(state))
          | TwoCardsFlipped(_, _) =>
            <button onClick=(buttonAction(self))>
              (str(message(state)))
            </button>
          }
        )
      </div>
      <div className="result">
        (tableau |> Tableau.pairsFound |> string_of_int |> str)
      </div>
    </div>,
};