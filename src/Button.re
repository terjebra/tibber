open Css;

let button =
  style([
    padding(em(0.8)),
    fontSize(rem(1.)),
    color(hex("FDFDF9")),
    backgroundColor(hsla(197, 93, 29, 1.)),
    border(em(0.0), none, white),
    textTransform(uppercase),
    boxShadow(
      ~x=em(0.),
      ~y=em(0.2),
      ~blur=em(0.2),
      ~spread=em(0.),
      rgba(0, 0, 0, 0.15),
    ),
  ]);

let component = ReasonReact.statelessComponent("Button");

let make = (~onClick, ~text, _children) => {
  ...component,
  render: _self =>
    <button className=button onClick> (ReasonReact.string(text)) </button>,
};