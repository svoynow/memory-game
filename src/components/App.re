[%%debugger.chrome];

open Helpers;

type action = Game.action;
type state = Game.t;

let reducer = (action, state) =>
  ReasonReact.Update(Game.doAction(action, state));

let component = ReasonReact.reducerComponent("App");

let initialState = () => Game.initialize();

let buttonAction = ({ReasonReact.state: {Game.turnState}} as self) =>
  switch (turnState) {
  | TwoCardsFlipped(card1, card2) when Card.isMatch(card1, card2) => (
      _ => self.send(Game.ClaimPair)
    )
  | TwoCardsFlipped(_, _) => (_ => self.send(Game.Reset))
  | _ => noOp
  };

let cardAction = ({ReasonReact.state: {Game.turnState}} as self, card) =>
  switch (turnState) {
  | NotStarted => (_ => self.send(Game.SelectFirst(card)))
  | OneCardFlipped(_card) => (_ => self.send(Game.SelectSecond(card)))
  | _ => noOp
  };

let message = ({Game.turnState}) =>
  Card.(
    switch (turnState) {
    | NotStarted => "Choose a card"
    | OneCardFlipped({animal}) =>
      "Try to find the other " ++ Animal.toString(animal)
    | TwoCardsFlipped(card1, card2) when Card.isMatch(card1, card2) => "A match! Click to continue."
    | TwoCardsFlipped(_, _) => "Sorry, reset and try again"
    }
  );

let make = _children => {
  ...component,
  initialState,
  reducer,
  render:
    (
      {ReasonReact.state: {Game.turnState, Game.paired, Game.deck} as state} as self,
    ) =>
    <div className="app">
      <div className="grid">
        (
          List.map(
            card =>
              Game.displayCard(state, card) ?
                <CardIcon
                  card
                  key=(Card.key(card))
                  onClick=(cardAction(self, card))
                /> :
                <img
                  className="card-image"
                  src="x.png"
                  key=(Card.key(card))
                />,
            deck,
          )
          |> Array.of_list
          |> ReasonReact.array
        )
      </div>
      <div className="message">
        (
          switch (turnState) {
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
        (str("Pairs found: " ++ string_of_int(Array.length(paired))))
      </div>
    </div>,
};