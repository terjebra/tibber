open Css;

let header =
  style([padding(em(0.5)), backgroundColor(rgba(27, 115, 151, 1.))]);

let component = ReasonReact.statelessComponent("Header");

let make = (~title, _children) => {
  ...component,
  render: _self =>
    <div className=header> <h1> (ReasonReact.string(title)) </h1> </div>,
};