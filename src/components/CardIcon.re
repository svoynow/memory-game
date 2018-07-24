let component = ReasonReact.statelessComponent("CardIcon");

let make = (~card, ~onClick, _children) => {
  ...component,
  render: _self =>
    <img className="card-image" onClick src=(Card.imageUrl(card)) />,
};