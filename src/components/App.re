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

let message = ({Game.turnState}) =>
  switch (turnState) {
  | NotStarted => "Choose a card"
  | OneCardFlipped(card) =>
    "Try to find the other " ++ Tableau.Item.toString(card)
  | TwoCardsFlipped(_, _) when Game.hasMatch(turnState) => "A match! Click to continue."
  | TwoCardsFlipped(_, _) => "No match. Reset and try again"
  | GameComplete => "All done! Play again?"
  };

let renderCard = (self, {Tableau.Item.card} as item) =>
  <CardComponent
    card=item
    key=(Card.key(card))
    onClick=(_ => self.ReasonReact.send(Game.SelectCard(item)))
  />;

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
            <button onClick=(_ => self.send(Game.Continue))>
              (str(message(state)))
            </button>
          | GameComplete =>
            <button onClick=(_ => self.send(Game.Reset))>
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