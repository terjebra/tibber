open Css;

let component = ReasonReact.statelessComponent("Modal");

let backdrop =
  style([
    position(fixed),
    top(em(0.)),
    bottom(em(0.)),
    left(em(0.)),
    right(em(0.)),
    backgroundColor(rgba(0, 0, 0, 0.5)),
  ]);

let body =
  style([
    position(fixed),
    top(em(2.)),
    bottom(em(2.)),
    left(em(2.)),
    right(em(2.)),
    backgroundColor(rgba(47, 127, 160, 1.)),
    padding2(em(1.5), em(2.)),
  ]);

let make = children => {
  ...component,
  render: _self =>
    <div>
      <div className=backdrop />
      <div className=body> ...children </div>
    </div>,
};