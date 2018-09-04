open Helpers;

let component = ReasonReact.statelessComponent("CardComponent");

let make = (~card as {Tableau.Item.cardState} as card, ~onClick, _children) => {
  ...component,
  render: _self =>
    <img
      className="card-image"
      onClick=(cardState == Tableau.Item.Paired ? noOp : onClick)
      src=(Tableau.Item.image(card))
    />,
};